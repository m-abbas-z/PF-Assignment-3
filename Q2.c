#include <stdio.h>
#include <string.h>

int calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets)
{
    if (fuel <= 0 || planet > totalPlanets)
    {
        return fuel > 0;
    }

    fuel = fuel - consumption;
    if (fuel <= 0)
    {
        printf("Planet %d: Fuel Remaining = 0\n", planet);
        return 0;
    }

    fuel = fuel + recharge;

    if (planet % 4 == 0)
    {
        fuel = fuel + solarBonus;
    }

    printf("Planet %d: Fuel Remaining = %d\n", planet, fuel);

    return calculateFuel(fuel, consumption, recharge, solarBonus, planet + 1, totalPlanets);
}

int main()
{
    int initialFuel;
    int fuelConsumption;
    int gravitationalRecharge;
    int solarRechargeBonus;
    int totalPlanets;

    printf("Enter initial fuel: ");
    scanf("%d", &initialFuel);
    printf("Enter fuel consumption per planet: ");
    scanf("%d", &fuelConsumption);
    printf("Enter gravitational recharge amount: ");
    scanf("%d", &gravitationalRecharge);
    printf("Enter solar recharge bonus (every 4th planet): ");
    scanf("%d", &solarRechargeBonus);
    printf("Enter total number of planets: ");
    scanf("%d", &totalPlanets);

    printf("\nFuel simulation:\n");
    int canComplete = calculateFuel(initialFuel, fuelConsumption, gravitationalRecharge, solarRechargeBonus, 1, totalPlanets);

    if (canComplete)
    {
        printf("\nSpacecraft completed the journey.\n");
    }
    else
    {
        printf("\nSpacecraft could not complete the journey.\n");
    }

    return 0;
}
