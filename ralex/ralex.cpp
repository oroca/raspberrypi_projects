//------------------------------------------------------------------------------
// @file   : ralex.cpp
// @brief  : raspberrypi + herkulex + tts
// @author : Yoonseok Pyo
// @version: Ver0.2 (since 2013.06.29)
// @date   : 2013.06.29
// @License: BSD
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <termios.h>
#include <fcntl.h>
#include <errno.h>

#include "herkulex.h"

#define LSB(data) ((unsigned char)(data))
#define MSB(data) ((unsigned char)((unsigned int)(data)>>8)&0xFF)

typedef struct
{
	unsigned char	ucHeader[2];
	unsigned char	ucPacketSize;
	unsigned char	ucChipID;
	unsigned char	ucCmd;
	unsigned char	ucCheckSum1;
	unsigned char	ucCheckSum2;
	unsigned char	ucData[MAX_DATA_SIZE-2];
}SendIJogPacket;

typedef struct
{
	unsigned char	ucHeader[2];
	unsigned char	ucPacketSize;
	unsigned char	ucChipID;
	unsigned char	ucCmd;
	unsigned char	ucCheckSum1;
	unsigned char	ucCheckSum2;
	unsigned char	ucAddress;
	unsigned char	ucLen;
	unsigned char	ucData[MAX_DATA_SIZE-2];
}SendRWPacket;

int fd;

bool setSerialOpen(void)
{
    struct termios newtio;

    fd = open( "/dev/ttyUSB0", O_RDWR|O_NOCTTY|O_NONBLOCK );
    if(fd == -1) {
        printf("connect failed...(%s)\n",strerror(errno));
        return false;
    }

    memset( &newtio, 0, sizeof(newtio) );

    newtio.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;
    newtio.c_lflag = 0;
    newtio.c_cc[VTIME] = 0;
    newtio.c_cc[VMIN]  = 0;

    tcflush (fd, TCIFLUSH );
    tcsetattr(fd, TCSANOW, &newtio );

    printf("setSerialOpen : OK\n");
    
    return true;
}

bool setHekulexInit(void)
{
	//--------------------------------------------------------------------------
	SendRWPacket stSendRWPacket;
	SendIJogPacket stSendIJOGPacket;

	unsigned int iPos = 0;

	//--------------------------------------------------------------------------
	stSendRWPacket.ucHeader[0] = HEADER;
	stSendRWPacket.ucHeader[1] = HEADER;
	stSendRWPacket.ucPacketSize = MIN_PACKET_SIZE + 3;
	stSendRWPacket.ucChipID = 0;
	stSendRWPacket.ucCmd = CMD_RAM_WRITE;
	stSendRWPacket.ucAddress = 52;
	stSendRWPacket.ucLen = 1;
	stSendRWPacket.ucData[0] = 0x60;

	//CheckSum
	stSendRWPacket.ucCheckSum1 = stSendRWPacket.ucPacketSize ^ stSendRWPacket.ucChipID ^ stSendRWPacket.ucCmd ^ stSendRWPacket.ucAddress ^ stSendRWPacket.ucLen;

	for(unsigned char i=0; i<stSendRWPacket.ucLen; i++ )
		stSendRWPacket.ucCheckSum1 ^= stSendRWPacket.ucData[i];

	stSendRWPacket.ucCheckSum2 = ~(stSendRWPacket.ucCheckSum1);
	stSendRWPacket.ucCheckSum1 &= CHKSUM_MASK;
	stSendRWPacket.ucCheckSum2 &= CHKSUM_MASK;

	write( fd, &stSendRWPacket.ucHeader[0], stSendRWPacket.ucPacketSize);

	//--------------------------------------------------------------------------
	stSendRWPacket.ucHeader[0] = HEADER;
	stSendRWPacket.ucHeader[1] = HEADER;
	stSendRWPacket.ucPacketSize = MIN_PACKET_SIZE + 3;
	stSendRWPacket.ucChipID = 1;
	stSendRWPacket.ucCmd = CMD_RAM_WRITE;
	stSendRWPacket.ucAddress = 52;
	stSendRWPacket.ucLen = 1;
	stSendRWPacket.ucData[0] = 0x60;

	//CheckSum
	stSendRWPacket.ucCheckSum1 = stSendRWPacket.ucPacketSize ^ stSendRWPacket.ucChipID ^ stSendRWPacket.ucCmd ^ stSendRWPacket.ucAddress ^ stSendRWPacket.ucLen;

	for(unsigned char i=0; i<stSendRWPacket.ucLen; i++ )
		stSendRWPacket.ucCheckSum1 ^= stSendRWPacket.ucData[i];

	stSendRWPacket.ucCheckSum2 = ~(stSendRWPacket.ucCheckSum1);
	stSendRWPacket.ucCheckSum1 &= CHKSUM_MASK;
	stSendRWPacket.ucCheckSum2 &= CHKSUM_MASK;

	write( fd, &stSendRWPacket.ucHeader[0], stSendRWPacket.ucPacketSize);

	//--------------------------------------------------------------------------
	stSendRWPacket.ucHeader[0] = HEADER;
	stSendRWPacket.ucHeader[1] = HEADER;
	stSendRWPacket.ucPacketSize = MIN_PACKET_SIZE + 3;
	stSendRWPacket.ucChipID = 2;
	stSendRWPacket.ucCmd = CMD_RAM_WRITE;
	stSendRWPacket.ucAddress = 52;
	stSendRWPacket.ucLen = 1;
	stSendRWPacket.ucData[0] = 0x60;

	//CheckSum
	stSendRWPacket.ucCheckSum1 = stSendRWPacket.ucPacketSize ^ stSendRWPacket.ucChipID ^ stSendRWPacket.ucCmd ^ stSendRWPacket.ucAddress ^ stSendRWPacket.ucLen;

	for(unsigned char i=0; i<stSendRWPacket.ucLen; i++ )
		stSendRWPacket.ucCheckSum1 ^= stSendRWPacket.ucData[i];

	stSendRWPacket.ucCheckSum2 = ~(stSendRWPacket.ucCheckSum1);
	stSendRWPacket.ucCheckSum1 &= CHKSUM_MASK;
	stSendRWPacket.ucCheckSum2 &= CHKSUM_MASK;

	write( fd, &stSendRWPacket.ucHeader[0], stSendRWPacket.ucPacketSize);

	//--------------------------------------------------------------------------
	stSendRWPacket.ucHeader[0] = HEADER;
	stSendRWPacket.ucHeader[1] = HEADER;
	stSendRWPacket.ucPacketSize = MIN_PACKET_SIZE + 3;
	stSendRWPacket.ucChipID = 3;
	stSendRWPacket.ucCmd = CMD_RAM_WRITE;
	stSendRWPacket.ucAddress = 52;
	stSendRWPacket.ucLen = 1;
	stSendRWPacket.ucData[0] = 0x60;

	//CheckSum
	stSendRWPacket.ucCheckSum1 = stSendRWPacket.ucPacketSize ^ stSendRWPacket.ucChipID ^ stSendRWPacket.ucCmd ^ stSendRWPacket.ucAddress ^ stSendRWPacket.ucLen;

	for(unsigned char i=0; i<stSendRWPacket.ucLen; i++ )
		stSendRWPacket.ucCheckSum1 ^= stSendRWPacket.ucData[i];

	stSendRWPacket.ucCheckSum2 = ~(stSendRWPacket.ucCheckSum1);
	stSendRWPacket.ucCheckSum1 &= CHKSUM_MASK;
	stSendRWPacket.ucCheckSum2 &= CHKSUM_MASK;

	write( fd, &stSendRWPacket.ucHeader[0], stSendRWPacket.ucPacketSize);
    
    printf("setHekulexInit : OK\n");

    return true;
}



bool move(unsigned int uiPos1,unsigned int uiPos2,unsigned int uiPos3)
{
    SendIJogPacket stSendIJOGPacket;

    unsigned char ucDOF = 3;

    stSendIJOGPacket.ucHeader[0] = HEADER;
    stSendIJOGPacket.ucHeader[1] = HEADER;

    stSendIJOGPacket.ucPacketSize = MIN_PACKET_SIZE + CMD_I_JOG_STRUCT_SIZE*ucDOF;
    stSendIJOGPacket.ucChipID = BROADCAST_ID;
    stSendIJOGPacket.ucCmd = CMD_I_JOG;

    stSendIJOGPacket.ucData[0] = LSB(uiPos1);
    stSendIJOGPacket.ucData[1] = MSB(uiPos1);
    stSendIJOGPacket.ucData[2] = 0;
    stSendIJOGPacket.ucData[3] = 1; //ID
    stSendIJOGPacket.ucData[4] = 100;

    stSendIJOGPacket.ucData[5] = LSB(uiPos2);
    stSendIJOGPacket.ucData[6] = MSB(uiPos2);
    stSendIJOGPacket.ucData[7] = 0;
    stSendIJOGPacket.ucData[8] = 2; //ID
    stSendIJOGPacket.ucData[9] = 100;

    stSendIJOGPacket.ucData[10] = LSB(uiPos3);
    stSendIJOGPacket.ucData[11] = MSB(uiPos3);
    stSendIJOGPacket.ucData[12] = 0;
    stSendIJOGPacket.ucData[13] = 3; //ID
    stSendIJOGPacket.ucData[14] = 100;

    //CheckSum
    stSendIJOGPacket.ucCheckSum1 = stSendIJOGPacket.ucPacketSize ^ stSendIJOGPacket.ucChipID ^ stSendIJOGPacket.ucCmd;
    for(unsigned char i=0; i<CMD_I_JOG_STRUCT_SIZE * ucDOF; i++ )
    stSendIJOGPacket.ucCheckSum1 ^= stSendIJOGPacket.ucData[i];

    stSendIJOGPacket.ucCheckSum2 = ~(stSendIJOGPacket.ucCheckSum1);
    stSendIJOGPacket.ucCheckSum1 &= CHKSUM_MASK;
    stSendIJOGPacket.ucCheckSum2 &= CHKSUM_MASK;

    write( fd, &stSendIJOGPacket.ucHeader[0], stSendIJOGPacket.ucPacketSize);

    printf( "Succeed to move!\n" );

    return true;
}

int main(void)
{
    if(setSerialOpen()  == false) return false;
    if(setHekulexInit() == false) return false;
    
    printf("Ready to Move\n");

    move(424,600,400);  sleep(2);
    move(544,480,500);  sleep(1);
    move(424,600,500);  sleep(2);
    move(424,600,400);  sleep(2);
    move(544,480,400);  sleep(1);
    move(424,600,400);  sleep(1);
    move(424,600,500);  sleep(1);
    move(544,480,400);  sleep(0.5);
    move(544,480,500);  sleep(0.5);
    move(544,480,400);  sleep(0.5);
    move(424,600,400);  sleep(0.5);

    printf("End\n");

    close(fd);

    return 0;
}



