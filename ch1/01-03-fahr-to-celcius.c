#include <stdio.h>

main() 
{
    float fahr, celcius;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;
    
    fahr = lower;
    printf("%3c\t%6c\n", 'F', 'C');
    while (fahr <= upper) {
        celcius = 5 * (fahr-32) / 9;
        printf("%3.0f\t%6.1f\n", fahr, celcius);
        fahr = fahr + step;
    }

}