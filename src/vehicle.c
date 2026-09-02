#include <stdio.h>
#include <string.h>
#include "vehicle.h"

extern struct Vehicle *parking;
extern int slots[10];
extern int count;

struct BillingRecord{
    char number[20];
    char id[10];
    int slot;
    int duration;
    int charges;
    int entry_time;  
    int exit_time;    
};

struct BillingRecord billingLog[10];
int billingCount = 0;

void generateReport()
{
    FILE *fp = fopen("report.txt", "w");
    if (fp == NULL)
    {
        printf("Error generating report!\n");
        return;
    }

    fprintf(fp, "========== PARKING MANAGEMENT SYSTEM REPORT ==========\n\n");

    fprintf(fp, "Total Vehicles Currently Parked: %d\n\n", count);
    fprintf(fp, "%-15s %-15s %-5s %-10s\n", "Vehicle No", "Customer ID", "Slot", "Entry Time");
    fprintf(fp, "------------------------------------------------------\n");

    if (count == 0)
    {
        fprintf(fp, "No vehicles currently parked.\n");
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            int h = parking[i].entry_time / 60;
            int m = parking[i].entry_time % 60;
            fprintf(fp, "%-15s %-15s %-5d %02d:%02d\n",
                    parking[i].number,
                    parking[i].id,
                    parking[i].slot + 1,
                    h, m);
        }
    }

    fprintf(fp, "\n======================================================\n");

    fprintf(fp, "\n------------ BILLING / EXIT RECORDS ------------\n\n");
    fprintf(fp, "%-15s %-15s %-5s %-12s %-12s %-12s %-10s\n",
            "Vehicle No", "Customer ID", "Slot", "Entry Time", "Exit Time", "Duration(min)", "Charges");
    fprintf(fp, "--------------------------------------------------------------------------\n");

    if (billingCount == 0)
    {
        fprintf(fp, "No exit records yet.\n");
    }
    else
    {
        for (int i = 0; i < billingCount; i++)
        {
            int eh = billingLog[i].entry_time / 60;
            int em = billingLog[i].entry_time % 60;
            int xh = billingLog[i].exit_time / 60;
            int xm = billingLog[i].exit_time % 60;

            fprintf(fp, "%-15s %-15s %-5d %02d:%02d        %02d:%02d        %-12d %d rupees\n",
                    billingLog[i].number,billingLog[i].id,billingLog[i].slot + 1,eh, em,
                    xh,xm,billingLog[i].duration,billingLog[i].charges);
        }
    }

    fprintf(fp, "\n======================================================\n");
    fclose(fp);
    printf("Report saved to report.txt\n");
}

void addVehicle()
{
    if (count == 10)
    {
        printf("Parking Full\n");
        return;
    }

    char number[20], id[11];
    int hour, minute;

    printf("Enter Vehicle Number(eg.=UK07ABXXXX): ");
    scanf("%s", number);

    printf("Enter Customer ID (Phone Number): ");
    scanf("%s", id);

    printf("Enter Entry Time (HH MM): ");
    scanf("%d %d", &hour, &minute);

    int total_minutes = hour * 60 + minute;

    int slot = -1;

    for (int i = 0; i < 10; i++)
    {
        if (slots[i] == 0)
        {
            slot = i;
            break;
        }
    }
    if (slot == -1)
    {
        printf("No slot available\n");
        return;
    }

    strcpy(parking[count].number, number);
    strcpy(parking[count].id, id);
    parking[count].slot = slot;
    parking[count].entry_time = total_minutes;

    slots[slot] = 1;
    count++;

    printf("Vehicle Parked Successfully\n");
    printf("Slot Assigned: %d\n", slot + 1);

    generateReport();  
}

void removeVehicle()
{
    char number[20];
    printf("Enter Vehicle Number to Exit: ");
    scanf("%s", number);

    int found = -1;

    for (int i = 0; i < count; i++)
    {
        if (strcmp(parking[i].number, number) == 0)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        printf("Vehicle not found\n");
        return;
    }

    int hour, minute;

    printf("Enter Exit Time (HH MM): ");
    scanf("%d %d", &hour, &minute);

    int exit_time = hour * 60 + minute;

    int duration = exit_time - parking[found].entry_time;
    if (duration < 0)
    {
        printf("Invalid exit time\n");
        return;
    }

    int charges = duration;
    int slot = parking[found].slot;

    strcpy(billingLog[billingCount].number, parking[found].number);
    strcpy(billingLog[billingCount].id, parking[found].id);
    billingLog[billingCount].slot = slot;
    billingLog[billingCount].duration = duration;
    billingLog[billingCount].charges = charges;
    billingLog[billingCount].entry_time = parking[found].entry_time; 
    billingLog[billingCount].exit_time = exit_time;   
    billingCount++;

    slots[slot] = 0;

    for (int i = found; i < count - 1; i++)
    {
        parking[i] = parking[i + 1];
    }

    count--;

    printf("Vehicle Exited Successfully\n");
    printf("Total Time: %d minutes\n", duration);
    printf("Charges: %d rupees\n", charges);

    generateReport();  
}

void viewSlots()
{
    printf("Available Slots: ");
    for (int i = 0; i < 10; i++)
    {
        if (slots[i] == 0)
        {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
}

void searchVehicle()
{
    char number[20];
    printf("Enter the vehicle number: ");
    scanf("%s", number);
    int found = 0;

    for (int i = 0; i < count; i++)
    {
        if (strcmp(parking[i].number, number) == 0)
        {
            found = 1;
            printf("Vehicle Found\n");
            printf("Slot: %d\n", parking[i].slot + 1);

            int time = parking[i].entry_time;
            int h = time / 60;
            int m = time % 60;
            printf("Entry Time: %02d:%02d\n", h, m);
            break;
        }
    }
    if (!found)
    {
        printf("Vehicle not found\n");
    }
}

void viewReport()
{
    if (count == 0)
    {
        printf("No vehicles parked\n");
        return;
    }

    printf("\n\nParking Report\n");
    printf("Total Vehicles: %d\n\n", count);

    printf("%-15s %-15s %-5s %s\n", "Vehicle No", "ID", "Slot", "Time");
    printf("---------------------------------------------------\n");

    struct Vehicle *ptr;

    for (int i = 0; i < count; i++)
    {
        ptr = &parking[i];

        int time = ptr->entry_time;
        int h = time / 60;
        int m = time % 60;

        printf("%-15s %-15s %-5d %02d:%02d\n", ptr->number, ptr->id, ptr->slot + 1, h, m);
    }
}

void searchbyid()
{
    char id[11];
    printf("Enter your unique ID: ");
    scanf("%s", id);

    int flag = 0;

    for (int i = 0; i < count; i++)
    {
        if (strcmp(parking[i].id, id) == 0)
        {
            flag = 1;

            printf("Vehicle Found\n");
            printf("Vehicle Number: %s\n", parking[i].number);
            printf("Slot: %d\n", parking[i].slot + 1);

            int time = parking[i].entry_time;
            int h = time / 60;
            int m = time % 60;

            printf("Entry Time: %02d:%02d\n", h, m);
            break;
        }
    }

    if (flag == 0)
    {
        printf("No record found for this ID\n");
    }
}
