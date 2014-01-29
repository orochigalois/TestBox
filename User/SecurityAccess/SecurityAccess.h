#ifndef _SECURITYACCESS_H_
#define _SECURITYACCESS_H_

#include "includes.h"
#include "can_handling.h"

void SecurityAccess_Request (void);
uint8_t SeedToKey( uint8_t seed[], uint8_t seckey[], uint8_t AccessLevel);
uint8_t Get_security_Key(uint8_t l_data_0,uint8_t l_data_1, uint8_t l_data_2, uint8_t l_data_3, uint8_t l_data_4, uint8_t l_data_5);

uint8_t positive_respone_SecurityAccess (uint8_t *RX_Security_Buffer);


#endif
