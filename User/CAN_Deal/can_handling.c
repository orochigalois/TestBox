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
uint8_t ReadInforFCBuffer[8] = {0x30,0x03,0x00};

uint8_t LEDControlTXMSGBuffer[6][8] = {{0x21,0x10,0x00,0xbf,0x0a,0x00,0x00,0x00},
    {0x21,0x40,0x00,0x00,0x00,0x00,0x00,0x00},
    {0x21,0xab,0x77,0x40,0x01,0x00,0x00,0x00},
    {0x21,0x04,0x88,0x00,0x04,0x00,0x00,0x00},
    {0x21,0xff,0xff,0xff,0xff,0x00,0x00,0x00},
    {0x21,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
};

uint8_t PositiveRes_FlagAlex = 0;
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

    ucIntStatus = CAN_IntGetStatus(CAN_ID_1);

    if (ucIntStatus & 0x01)
    {
        CAN_ReceiveMsg(CAN_ID_1, &RXMsg);
        if(RXMsg.id == 0x738)
        {
            bCAN_ReceiveMSGING = 1;
            switch(RXMsg.dataA[0])
            {
			case 0x10:
                
                memcpy(RXDataBuffer,&RXMsg.dataA[1],3);
                memcpy(RXDataBuffer+3,RXMsg.dataB,4);
                SendService_CAN(ReadInforFCBuffer);
                break;
            case 0x21:
                
                memcpy(RXDataBuffer+7,&RXMsg.dataA[1],3);
                memcpy(RXDataBuffer+10,RXMsg.dataB,4);
				PositiveRes_FlagAlex=1;
                break;
			default:
				break;
            }
        }

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
                SendService_CAN(ReadInforFCBuffer);
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
