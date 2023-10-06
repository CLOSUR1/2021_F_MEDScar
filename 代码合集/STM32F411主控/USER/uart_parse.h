#ifndef  _UART_PARSE_H
#define  _UART_PARSE_H

#include "sys.h"

void printarray(float* array,int n);
void printfloat(float data);
void printstr(char* str);

char* sbz_format(float *data,int size);
void sbz_parse_new(char *data, float *output);

void VL53L0_parse(char *data, float *output);
void arraycopy(float a[],float b[],int len);
int sbz_parse(char *data, float *output,int STA,int len);
extern char datatrans[50];

#endif
