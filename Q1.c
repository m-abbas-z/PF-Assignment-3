#include <stdio.h>
#include <string.h>

double calculateRepaymentRecursive(double remainingLoan, double interestRate, int currentYear, int totalYears, double yearlyInstallment)
{
    if (currentYear > totalYears || remainingLoan <= 0)
    {
        return 0.0;
    }

    double interestThisYear = remainingLoan * interestRate;
    double yearlyPayment = yearlyInstallment + interestThisYear;
    double newRemainingLoan = remainingLoan + interestThisYear - yearlyInstallment;

    if (newRemainingLoan < 0)
    {
        newRemainingLoan = 0;
    }

    printf("Year %d: Remaining loan = %.2f\n", currentYear, newRemainingLoan);

    return yearlyPayment + calculateRepaymentRecursive(newRemainingLoan, interestRate, currentYear + 1, totalYears, yearlyInstallment);
}

double calculateRepayment(double loanAmount, double interestRate, int years)
{
    double yearlyInstallment = loanAmount / years;
    return calculateRepaymentRecursive(loanAmount, interestRate, 1, years, yearlyInstallment);
}

double calculateRepaymentWithExtraRecursive(double remainingLoan, double interestRate, int currentYear, int totalYears, double yearlyInstallment, double extraPayment)
{
    if (currentYear > totalYears || remainingLoan <= 0)
    {
        return 0.0;
    }

    double interestThisYear = remainingLoan * interestRate;
    double yearlyPayment = yearlyInstallment + extraPayment + interestThisYear;
    double newRemainingLoan = remainingLoan + interestThisYear - yearlyInstallment - extraPayment;

    if (newRemainingLoan < 0)
    {
        newRemainingLoan = 0;
    }

    printf("Year %d (with extra payment): Remaining loan = %.2f\n", currentYear, newRemainingLoan);

    return yearlyPayment + calculateRepaymentWithExtraRecursive(newRemainingLoan, interestRate, currentYear + 1, totalYears, yearlyInstallment, extraPayment);
}

int main()
{
    double loanAmount = 100000.0;
    double interestRate = 0.05;
    int years = 3;

    printf("Repayment schedule without extra payments:\n");
    double totalRepayment = calculateRepayment(loanAmount, interestRate, years);
    printf("Total repayment over %d years = %.2f\n\n", years, totalRepayment);

    double extraPayment = 5000.0;
    printf("Repayment schedule with extra yearly payment of %.2f:\n", extraPayment);
    double yearlyInstallment = loanAmount / years;
    double totalRepaymentWithExtra = calculateRepaymentWithExtraRecursive(loanAmount, interestRate, 1, years, yearlyInstallment, extraPayment);
    printf("Total repayment with extra payments over %d years = %.2f\n", years, totalRepaymentWithExtra);

    return 0;
}
