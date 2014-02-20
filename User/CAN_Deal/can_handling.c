/***************************************************************************************************
This file is for CAN dealing.

*****************************************************************************************************/
#include "can_handling.h"

extern uint8_t u8LEDControl_Data;


CAN_MSG_Type	TXMsg, RXMsg;
uint8_t bCAN_SendMSGING = 0;
uint8_t bCAN_ReceiveMSGING = 0;

uint8_t CAN_MSGRXControlType = 0;
uint16_t CAN_MSGRXControlID = 0;

uint8_t PositiveRes_Flag = 0;
uint8_t RXDataBuffer[21] = {0x00};
uint8_t u8ControlType = 0;
uint16_t u16ControlID = 0;


uint8_t LEDControlTXMSGBuffer[6][8] = {{0x21,0x10,0x00,0xbf,0x0a,0x00,0x00,0x00},
    {0x21,0x40,0x00,0x00,0x00,0x00,0x00,0x00},
    {0x21,0xab,0x77,0x40,0x01,0x00,0x00,0x00},
    {0x21,0x04,0x88,0x00,0x04,0x00,0x00,0x00},
    {0x21,0xff,0xff,0xff,0xff,0x00,0x00,0x00},
    {0x21,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
};




uint8_t seed[4] = {0x0};
uint8_t key[4] = {0x0};

uint8_t isSmileRunning = 0;
uint8_t SmileStep=0;

uint8_t readNand2048[2048]= {0x0};
uint16_t pageIndex=0;


uint32_t PC=0;
uint32_t PC_last=0xffffffff;
uint8_t Tx8[8]= {0x0};


uint8_t Tx8_SecurityAccess1[8] = {0x02,0x27,0x01};
uint8_t Tx8_SecurityAccess2[8] = {0x06,0x27,0x02};

uint8_t Tx8_CheckProgrammingDependencies[8]= {0x04,0x31,0x01,0xFF,0x01};
uint8_t Tx8_reset_ECU[8]= {0x02,0x11,0x01};



//==============================================================================
// DESCRIPTION : vCAN_Init() Init CAN mode
//
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================
void vCAN_Init()
{
    PINSEL_ConfigPin(0, 0, 1);
    PINSEL_ConfigPin(0, 1, 1);
    //PINSEL_ConfigPin(0, 4, 2);
    //PINSEL_ConfigPin(0, 5, 2);
    CAN_Init(CAN_ID_1, 500000);
    CAN_ModeConfig (CAN_ID_1, CAN_OPERATING_MODE, ENABLE);
    //CAN_SetAFMode(CAN_ACC_BP);
    CAN_Init(CAN_ID_2, 500000);
    CAN_ModeConfig (CAN_ID_2, CAN_OPERATING_MODE, ENABLE);
    CAN_SetAFMode(CAN_ACC_BP);
    CAN_IRQCmd (CAN_ID_1, CANINT_RIE, ENABLE);
    //CAN_IRQCmd (CAN_ID_2, CANINT_RIE, ENABLE);
    NVIC_EnableIRQ(CAN_IRQn);

}


void SeedToKeyAlex()
{
    uint32_t i;
    uint32_t seedlokal;

    uint32_t u32SeedToKeyMask=0xB0DCDFB0;
    seedlokal = ((uint32_t)seed[0] << 24) + ((U32)seed[1] << 16) +((U32)seed[2] << 8) + (U32)seed[3];
    for (i=0; i<35; i++)
    {
        if (seedlokal & 0x80000000)
        {
            seedlokal = seedlokal << 1;
            seedlokal = seedlokal ^ u32SeedToKeyMask;
        }
        else
        {
            seedlokal = seedlokal << 1;
        }
    }
    key[0] = (U8)(seedlokal >> 24);
    key[1] = (U8)(seedlokal >> 16);
    key[2] = (U8)(seedlokal >> 8);
    key[3] = (U8)(seedlokal);




}/*SeedToKey*/


void get_one_instruction()
{

	uint8_t t;
    if(PC%256==0&&PC!=PC_last)
    {
		EMC_NAND_ReadSinglePage((void*)readNand2048,pageIndex);
    	pageIndex++;
    }
    memcpy(Tx8,readNand2048+(PC%256)*8,8);

	PC_last=PC;
	if(PC==0x2400)
		t++;

}



//==============================================================================
// DESCRIPTION : CAN_IRQHandler() CAN Receiver interrupt function
//
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================
void CAN_IRQHandler(void)
{
    uint8_t 				ucIntStatus;
    uint8_t  index15;
	uint32_t wait_i=0;
    ucIntStatus = CAN_IntGetStatus(CAN_ID_1);

    if (ucIntStatus & 0x01)
    {
        CAN_ReceiveMsg(CAN_ID_1, &RXMsg);
        if(RXMsg.id == 0x738)
        {


            bCAN_ReceiveMSGING = 1;
            switch(RXMsg.dataA[1])
            {
            case 0x50://Open Session OK
                if(SmileStep==0)
                {
					isSmileRunning=1;
                    SendService_CAN(Tx8_SecurityAccess1);
                    SmileStep++;
                }
                break;
            case 0x67:
                if(RXMsg.dataA[2]==0x01)//SecurityAccess1 OK
                {
                    if(SmileStep==1)
                    {
                        seed[0]=RXMsg.dataA[3];
                        seed[1]=RXMsg.dataB[0];
                        seed[2]=RXMsg.dataB[1];
                        seed[3]=RXMsg.dataB[2];
                        SeedToKeyAlex();
                        Tx8_SecurityAccess2[3]=key[0];
                        Tx8_SecurityAccess2[4]=key[1];
                        Tx8_SecurityAccess2[5]=key[2];
                        Tx8_SecurityAccess2[6]=key[3];
                        SendService_CAN(Tx8_SecurityAccess2);
						
                        SmileStep++;
                    }

                }
                else if(RXMsg.dataA[2]==0x02)//SecurityAccess2 OK
                {
                    if(SmileStep==2)
                    {
                        get_one_instruction();
						PC++;
                        SendService_CAN(Tx8);
                        SmileStep++;
                    }
                }
                break;
            case 0x71:
                if(SmileStep==3)//Erase Zone OK
                {
                    get_one_instruction();
					PC++;
                    SendService_CAN(Tx8);
                    SmileStep++;
                }

                else if(SmileStep==7)//cRoutineSelfCheck OK
                {
                    get_one_instruction();
					PC++;
                    if(Tx8[0]==0xAB&&
                            Tx8[1]==0xAB&&
                            Tx8[2]==0xAB&&
                            Tx8[3]==0xAB&&
                            Tx8[4]==0xAB&&
                            Tx8[5]==0xAB&&
                            Tx8[6]==0xAB&&
                            Tx8[7]==0xAB)
                    {

                        SendService_CAN(Tx8_CheckProgrammingDependencies);
                        SmileStep=8;

                    }
					else
					{
	                    SendService_CAN(Tx8);
	                    SmileStep=3;
					}
                }

				else if(SmileStep==8)//CheckProgrammingDependencies OK
				{
					SendService_CAN(Tx8_reset_ECU);//Reset ECU
					SmileStep++;
				}
				else
				{
					//do nothing
				}
                break;

            case 0x0F:
                if(RXMsg.dataA[0]==0x30)//Flow control
                {
                    if(SmileStep==4)
                    {
                        get_one_instruction();
						PC++;
                        SendService_CAN(Tx8);
                        SmileStep++;
                    }
                    else if(SmileStep==6)
                    {
						index15=0;
                        while(index15<15)
                        {
                            get_one_instruction();
					
                            
                            if(Tx8[0]<0x20||Tx8[0]>0x2F)
                            {
                                break;
                            }
							PC++;
                            SendService_CAN(Tx8);
							for( wait_i=0; wait_i < 20000; wait_i++ );

							index15++;
                        }



                    }
					else
					{
						//do nothing
					}
                }
                break;
            case 0x74://request download OK
                if(SmileStep==5)
                {
                    get_one_instruction();
					PC++;
                    SendService_CAN(Tx8);
                    SmileStep++;
                }
                break;

            case 0x76:// download OK
                if(SmileStep==6)
                {
					
                    get_one_instruction();
					PC++;
                    SendService_CAN(Tx8);

                }
                break;

            case 0x77:// cDiagMasterCodeTransferExit_OK
                if(SmileStep==6)
                {
                    get_one_instruction();
					PC++;
                    if(Tx8[1]==0x31&&Tx8[2]==0x01)//cRoutineSelfCheck
                    {
                        SendService_CAN(Tx8);
                        SmileStep++;
                    }
                    else//
                    {
                        SendService_CAN(Tx8);
                        SmileStep=4;
                    }

                }
                break;

			case 0x51:// cDiagMasterCodeTransferExit_OK
                if(SmileStep==9)
                {
                    isSmileRunning=0;
                }
                break;



            default:
                break;
            }
        }

#if 0
        if(RXMsg.id == 0x77e)
        {
            bCAN_ReceiveMSGING = 1;
            switch(RXMsg.dataA[0])
            {
            case 0x10:
                u8ControlType = RXMsg.dataA[2];
                if(u8ControlType == RXRoutineType)
                {
                    u16ControlID = ((uint16_t)RXMsg.dataB[0] << 8) + RXMsg.dataB[1];
                }
                else if(u8ControlType == RXReadDTCStatusType)
                {
                    u16ControlID = RXMsg.dataA[3];
                }
                else
                {
                    u16ControlID = ((uint16_t)RXMsg.dataA[3] << 8) + RXMsg.dataB[0];
                }
                memcpy(RXDataBuffer,&RXMsg.dataA[1],3);
                memcpy(RXDataBuffer+3,RXMsg.dataB,4);
                SendService_CAN(Tx8_SecurityAccess1);
                break;
            case 0x21:
                if(RXDataBuffer[0] <= 0x0D)//Two CAN Frame
                {
                    if((u8ControlType == CAN_MSGRXControlType)&&(u16ControlID == CAN_MSGRXControlID))
                    {
                        PositiveRes_Flag = 1;
                    }
                }
                memcpy(RXDataBuffer+7,&RXMsg.dataA[1],3);
                memcpy(RXDataBuffer+10,RXMsg.dataB,4);
                break;
            case 0x22:
                if(RXDataBuffer[0] <= 0x14)//Two CAN Frame
                {
                    if((u8ControlType == CAN_MSGRXControlType)&&(u16ControlID == CAN_MSGRXControlID))
                    {
                        PositiveRes_Flag = 1;
                    }
                }
                memcpy(RXDataBuffer+14,&RXMsg.dataA[1],3);
                memcpy(RXDataBuffer+17,RXMsg.dataB,4);
                break;
            case 0x23:
                break;
            case 0x30://LED Control
                SendService_CAN(LEDControlTXMSGBuffer[u8LEDControl_Data]);
                break;
            default:
                u8ControlType = RXMsg.dataA[1];
                if(u8ControlType == 0x7f)
                {
                    PositiveRes_Flag = RXMsg.dataA[3];
                    memcpy(RXDataBuffer,RXMsg.dataA,4);
                    memcpy(RXDataBuffer+4,RXMsg.dataB,4);
                }
                else
                {
                    if((u8ControlType == RXSessionType)||(u8ControlType == RXSecutityType)||(u8ControlType == RXResetType)||(u8ControlType == RXReadDTCStatusType))
                    {
                        u16ControlID = RXMsg.dataA[2];
                    }
                    else if((u8ControlType == RXIOControlType)||(u8ControlType == RXReadDataByIDType)||(u8ControlType == RXWriteDataByIDType))
                    {
                        u16ControlID = ((uint16_t)RXMsg.dataA[2] << 8) + RXMsg.dataA[3];
                    }
                    else if(u8ControlType == RXRoutineType)
                    {
                        u16ControlID = ((uint16_t)RXMsg.dataA[3] << 8) + RXMsg.dataB[0];
                    }
                    if((u8ControlType == CAN_MSGRXControlType)&&(u16ControlID == CAN_MSGRXControlID))
                    {
                        PositiveRes_Flag = 1;
                        memcpy(RXDataBuffer,RXMsg.dataA,4);
                        memcpy(RXDataBuffer+4,RXMsg.dataB,4);
                    }
                }
                break;
            }
        }
#endif
    }
}

//==============================================================================
// DESCRIPTION : SendService_CAN() CAN Send MSG function
//
// PARAMETERS  : uint8_t *TXDataBuffer
//
// RETURN VALUE : none
//==============================================================================
void SendService_CAN(uint8_t *TXDataBuffer)
{
    bCAN_SendMSGING = 1;
    TXMsg.format = STD_ID_FORMAT;
    TXMsg.id = 0x728;
    TXMsg.len = 8;
    TXMsg.type = DATA_FRAME;

    memcpy(TXMsg.dataA,TXDataBuffer,4);
    memcpy(TXMsg.dataB,TXDataBuffer+4,4);

    CAN_SendMsg(CAN_ID_1, &TXMsg);
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
