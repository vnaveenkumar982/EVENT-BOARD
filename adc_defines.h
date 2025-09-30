#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define ADCCLK 3000000
#define CLKDIV ((PCLK/ADCCLK)-1)
//defines for ADCs sfr
#define CLKDIV_BITS 8
#define PDN_BIT 21
#define ADC_START_BIT 24
//defines for ADDR sfr
#define RESULT_BITS 6
#define DONE_BIT 31
#define PIN_FUNC2 1
#define ANO_INPUT_PIN  PIN_FUNC2
