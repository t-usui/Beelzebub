#ifndef __SETUP_H__
#define __SETUP_H__

#include "common.h"
#define BUFFERSIZE 1000000

void DrawLogo(void);
int IsNumberOfCommandlineValRight(int num);
int SetupMalwareFile(unsigned char *name, FILE *fp, unsigned char *buf);
void SetupBeelzebub(int num, unsigned char *name, FILE *fp, unsigned char *buf);


#endif /* __SETUP_H__ */
