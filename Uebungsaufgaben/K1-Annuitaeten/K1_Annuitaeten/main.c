#include <stdio.h>
#include <stdlib.h>

int main()
{

    //creating input variables with enough size
    float credit = 0, amortizationrate = 0, interestrate = 0, monthly_rate = 0, monthly_amortization = 0, monthly_interest = 0;

    //getting inputs
    printf("Bitte geben sie den gewünschten Kredit ein: ");
    scanf("%f", &credit);

    printf("Bitte geben sie die gewünschte Tilgungsrate in Prozent ein: ");
    scanf("%f", &amortizationrate);

    printf("Bitte geben sie den geforderten Zinssatz in Prozent ein: ");
    scanf("%f", &interestrate);

    //calculate initial rates
    monthly_rate = (credit * ((amortizationrate + interestrate)/100))/12;
    monthly_amortization = (credit * (amortizationrate/100))/12;
    monthly_interest = (credit * (interestrate/100))/12;


    //print out headlines of table:
    printf("Monat   |   Kreditsumme |   Monatliche Tilgung  |   Monatliche Zinsen   |   Monatliche Rate \n");


    for (int i = 1; credit > 0 ; i++)
    {

        //print current row corresponding to month i
        printf("%d      |  %0.2f €      |   %0.2f €     |   %0.2f €     |   %0.2f €  \n", i, credit, monthly_amortization, monthly_interest, monthly_rate);

        //calculating new rates
        credit = credit- monthly_amortization;
        monthly_amortization = (monthly_rate-(((interestrate*credit)/100))/12);
        monthly_interest = (credit * (interestrate/100))/12;
    }
    return 0;
}
