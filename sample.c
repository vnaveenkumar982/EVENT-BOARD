
/*#include <LPC21xx.h>

#define SW1  4 // Switch @ P0.4

#define SW2  5  //Switch  @ P0.5

#define LED   8 

main()

{

      IODIR0 = 1 << LED;

     while ( 1 )

     {

        ! ( ( ( IOPIN0 >> SW1 ) & 1 )  &  ( ( IOPIN0 >> SW2 ) & 1 ) )  ?  ( IOCLR0 = 1 << LED ) :  ( IOSET0 = 1 << LED ) ;

    }

}

#include <LPC21xx.h>

#define SW1  4 // Switch @ P0.4

#define SW2  5  //Switch  @ P0.5

#define LED   8 

main()

{

      IODIR0 = 1 << LED;

     while ( 1 )

     {

         if ( ( ( ( IOPIN0 >> SW1 ) & 1 ) == 0 )  ||   ( ( ( IOPIN0 >> SW2 ) & 1 ) == 0 ) )

                   IOCLR0 = 1 << LED;

        else

                  IOSET0 = 1 << LED;

    }

}

#include <LPC21xx.h>

#define SW1  4 // Switch @ P0.4

#define SW2  5  //Switch  @ P0.5

#define LED   8 

main()

{

      IODIR0 = 1 << LED;

     while ( 1 )

     {

         if  ( ( ( IOPIN0 >> SW1 ) & 1 ) == 0 ) 

                   IOCLR0 = 1 << LED;

        else if  ( ( ( IOPIN0 >> SW2 ) & 1 ) == 0 ) 

                   IOCLR0 = 1 << LED;

        else

                  IOSET0 = 1 << LED;

    }

}

#include <LPC21xx.h>

#define SW1_AH 4

#define SW2_AH 5

#define LED_AH 8

main()

{

	IODIR0|=1<<LED_AH;


	while(1)

	{

		IOPIN0=( ((IOPIN0>>SW1_AH)&1) | ((IOPIN0>>SW2_AH)&1) )<<LED_AH;

	}

}*/

#include <LPC21xx.h>

#define SW1_AH 4

#define SW2_AH 5

#define LED_AH 8

main()

{

IODIR0|=1<<LED_AH;

while(1)

{

IOPIN0=( ((IOPIN0>>SW1_AH)&1) & ((IOPIN0>>SW2_AH)&1) )<<LED_AH;

}

}