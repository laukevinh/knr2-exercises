#include <stdio.h>

float convert(float fahr);

main() 
{
    float fahr;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;
    
    fahr = lower;
    printf("%3c\t%6c\n", 'F', 'C');
    while (fahr <= upper) {
        printf("%3.0f\t%6.1f\n", fahr, convert(fahr));
        fahr = fahr + step;
    }

}

float convert(float fahr)
{
    return 5 * (fahr-32) / 9;
}