#include <stdio.h>

main() 
{
    float fahr, celcius;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;
    
    celcius = lower;
    printf("%3c\t%6c\n", 'C', 'F');
    while (celcius <= upper) {
        fahr = celcius * 9 / 5 + 32;
        printf("%3.0f\t%6.1f\n", celcius, fahr);
        celcius = celcius + step;
    }

}