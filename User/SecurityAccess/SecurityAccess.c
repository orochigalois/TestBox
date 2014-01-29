#include "SecurityAccess.h"

uint8_t TXSecurityBuffer[8] = {0};

extern uint8_t CAN_MSGRXControlType;
extern uint16_t CAN_MSGRXControlID;
//==============================================================================
// DESCRIPTION : SecurityAccess_Request() Security Access 0x27 0x01
//
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================				
void  SecurityAccess_Request (void)
{
	TXSecurityBuffer[0] = 0x02;
	TXSecurityBuffer[1] = 0x27;
	TXSecurityBuffer[2] = 0x61;
	
	CAN_MSGRXControlType = TXSecurityBuffer[1]+0x40;
	CAN_MSGRXControlID = TXSecurityBuffer[2];
	
	SendService_CAN(TXSecurityBuffer);
}

//==============================================================================
// DESCRIPTION : SeedToKey()
//
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================				
uint8_t SeedToKey( uint8_t seed[], uint8_t seckey[], uint8_t AccessLevel)
{
  uint8_t i;	
	long seedlokal;
	
	uint32_t  mask = 0;

	if(AccessLevel == 0x01)
	{
			mask = 0xA0BDDFA0;
	}
	else if(AccessLevel == 0x61)
	{
			mask = 0xD124E456;
	}
	else
	{
			return 0;
	}
	if (seed[1] == 0 && seed[2] == 0)	
	{
		return 0;	
	}
	else	
	{	
		seedlokal = ((uint32_t )seed[0] << 24) + ((uint32_t )seed[1] << 16) +((uint32_t )seed[2] << 8) + (uint32_t )seed[3];	
		for (i=0; i<35; i++)	
		{	
			if (seedlokal & 0x80000000)	
			{	
				seedlokal = seedlokal << 1;	
				seedlokal = seedlokal ^ mask;	
			}	
			else	
			{	
				seedlokal = seedlokal << 1;	
			}	
		}	
		for (i=0; i<4; i++)	
		{	
			seckey[3-i] = (seedlokal >> (i*8)) & 0xFF;
		}
	}	
	return 1;	   
}
//==============================================================================
// DESCRIPTION : Get_security_Key() 0x27 0x02
//
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================				
uint8_t Get_security_Key(uint8_t l_data_0,uint8_t l_data_1, uint8_t l_data_2, uint8_t l_data_3, uint8_t l_data_4, uint8_t l_data_5)
{
  /* calculate the security code with Level-1 or Level-2 algorithm */
  /* if correct, return 1  */
	/* the level-1 SEED is C5, 41, A9 */
	/* the level-2 SEED is 5B, D2, 38 */
	
  uint8_t SecSeed[4],SecKey[4];
	uint8_t Level = l_data_0;
	

  SecSeed[0] = l_data_1;
  SecSeed[1] = l_data_2;
  SecSeed[2] = l_data_3;
  SecSeed[3] = l_data_4;

	//Check if the response means security access already done
	if(l_data_1 == 0 &&
	   l_data_2 == 0 &&
	   l_data_3 == 0 &&
     l_data_4 == 0)
	{
			//already in sucurity mode
			return 0;
  }

	if(Level == 0x61)
	{
		//Level-Man KEY computation algo :
		// compute the key according to the algorithm provided by FAW customer here.
		SeedToKey(SecSeed, SecKey, 0x61);
		
		TXSecurityBuffer[0] = 0x06;
		TXSecurityBuffer[1] = 0x27;
		TXSecurityBuffer[2] = 0x62;
		TXSecurityBuffer[3] = SecKey[0];
		TXSecurityBuffer[4] = SecKey[1];
		TXSecurityBuffer[5] = SecKey[2];
		TXSecurityBuffer[6] = SecKey[3];
	}
	else
	{
		return 0;
	}
	
	CAN_MSGRXControlType = TXSecurityBuffer[1]+0x40;
	CAN_MSGRXControlID = TXSecurityBuffer[2];
	SendService_CAN(TXSecurityBuffer);
  return 1;
}
//==============================================================================
// DESCRIPTION : positive_respone_SecurityAccess()
//
// PARAMETERS  : none
//
// RETURN VALUE : none
//==============================================================================				
uint8_t positive_respone_SecurityAccess (uint8_t *RX_Security_Buffer)
{
	uint8_t l_data_0 = RX_Security_Buffer[2];
	uint8_t l_data_1 = RX_Security_Buffer[3]; 
	uint8_t l_data_2 = RX_Security_Buffer[4]; 
	uint8_t l_data_3 = RX_Security_Buffer[5];
	uint8_t l_data_4 = RX_Security_Buffer[6]; 
	uint8_t l_data_5 = RX_Security_Buffer[7];
	if((l_data_1 == 0) && (l_data_2 == 0))
	{
		//write(">>>already in security mode Level-1");
		return 0;
	}
	
	if(Get_security_Key(l_data_0,l_data_1,l_data_2,l_data_3,l_data_4,l_data_5))
	{
		return 1;
	}
	else
	{
		return 0;
	}	
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
