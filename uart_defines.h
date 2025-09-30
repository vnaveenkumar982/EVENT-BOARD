#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define BAUD_RATE 9600
#define DIVISOR (PCLK/(16*BAUD_RATE))

///defines for UOLCR///
#define WORD_LEN_8BITS 3
#define DLAB_BIT 7

///defines for UOLSR///
#define RDR 0
#define TEMT_BIT 6
