#include "app_config.h"
#include "app_time.h"
#include "sys_eeprom.h"
#include "hwa_eeprom.h"
#include "drive_buzzer.h"
#include "drive_led.h"
#include "sys_delay.h"
#include "string.h"
#include "intrins.h"

code UINT8 SoftWareVersion = 0x01;
code UINT8 HardWareVersion = 0x01;

/*
typedef struct
{
UINT8 MGM_Card[6];
UINT8 Sector;                   //Ǯ��������
UINT8 Reserved[3];
UINT8 USER_Card[6];
UINT8 Function;
UINT8 Refund;
UINT8 IMaxValue;				//0~9	->0~4A
UINT8 OverCurrentMultiple;		//1~9    ->����ʱ�������ۼӻ��������ı���1~9��
UINT8 RecoveryOldCard;          //1->���ݾɿ�
UINT16 Money;                  //ˢ���۳�����λ��
UINT16 Time;		            //ˢ���ۿ�һ�μӵĵ���ʱ��
UINT16 BaseCurrent;				//�����������ã�ADֵС�ڵ��ڸ�ֵʱ����ֵ���㣬���ڸ�ֵʱ�ɱ�������
} SYSTEM_STRUCT;
*/
data SYSTEM_STRUCT s_System;
code SYSTEM_STRUCT s_FactorySystem =
{
    1,
};
void app_configInit(void)
{
	hwa_eepromInit();
	if (app_configRead(SYSTEM_SETTING_SECTOR) == FALSE)
	{
        s_System.Addr = 0x01;
        app_configWrite(SYSTEM_SETTING_SECTOR);
	}
    if(app_configRead(TIME_SAVE_SECTOR) == FALSE)
	{
        memset((UINT8*)&u16_DisplayTime, 0x00, sizeof(u16_DisplayTime));
        app_configWrite(TIME_SAVE_SECTOR);
	}
}

BOOL app_configRead(UINT8 Sector)
{
	BOOL b_errorFlag;
	if (Sector == SYSTEM_SETTING_SECTOR)
	{
		b_errorFlag = hwa_eepromReadSector((UINT8*)&s_System, SYSTEM_SETTING_SECTOR);
	}
    else if (Sector == TIME_SAVE_SECTOR)
	{
		b_errorFlag = hwa_eepromReadSector((UINT8*)&u16_DisplayTime, SYSTEM_SETTING_SECTOR);
	}
	return b_errorFlag;
}

void app_configWrite(UINT8 Sector)
{
	if (Sector == SYSTEM_SETTING_SECTOR)
	{
		hwa_eepromWriteSector((UINT8*)&s_System, SYSTEM_SETTING_SECTOR);
	}
    else if(Sector == TIME_SAVE_SECTOR)
    {
		hwa_eepromWriteSector((UINT8*)&u16_DisplayTime, TIME_SAVE_SECTOR);
    }
}

void app_configDisplay(void)
{
    sys_delayms(500);
    
    u8_ledDisBuff[0] = 19;
    u8_ledDisBuff[1] = s_System.Addr/100;
    u8_ledDisBuff[2] = s_System.Addr/10%10;
    u8_ledDisBuff[3] = s_System.Addr%10;
    sys_delayms(500);
    
    u8_ledDisBuff[0] = 19;
    u8_ledDisBuff[1] = 19;
    u8_ledDisBuff[2] = 19;
    u8_ledDisBuff[3] = 0;
}

