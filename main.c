#include <stdio.h>
#include <stdlib.h>
#include "auth.h"
#include "vehicle.h"

struct Vehicle *parking;
int slots[10] = {0};
int count = 0;
int main()
{
    parking = (struct Vehicle*) malloc(10 * sizeof(struct Vehicle));
    while(1){
    int choice;
    printf("------Main Menu------\n");
    printf("1. Admin\n2. Customer\n3. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1)
    {
        int result = login();

        if (result == 1)
        {
            printf("\n-----Login Successful------\nWelcome Admin\n");
            while (1)
            {
                int c;
                printf("\n1. Add Vehicle\n2. Remove Vehicle\n3. View Slots\n4. Search Vehicle\n5. Report\n6. Exit\n");
                printf("Enter choice: ");
                scanf("%d", &c);
                if (c == 1)
                {
                    addVehicle();
                }
                else if (c == 2)
                {
                    removeVehicle();
                }
                else if (c == 3)
                {
                    viewSlots();
                }
                else if (c == 4)
                {
                    searchVehicle();
                }
                else if (c == 5)
                {
                    viewReport();
                }
                else if (c == 6)
                {
                    printf("\n---------Exiting Admin mode---------\n");
                    break;
                }
                else
                {
                    printf("Invalid choice\n");
                }
            }
        }
        else
        {
            printf("\nInvalid Credentials! Access Denied\n");
        }
    }
    else if(choice==2)
    {
        printf("\n-------Customer Mode-------\n");

        while (1)
        {
            int c;
            printf("\n1. Search Vehicle\n2. View Slots\n3. Exit\n");
            printf("Enter choice: ");
            scanf("%d", &c);

            if (c == 1)
            {
                searchbyid();
            }
            else if (c == 2)
            {
                viewSlots();
            }
            else if (c == 3)
            {
                printf("-------Exiting Customer Mode-------\n");
                break;
            }
            else
            {
                printf("Invalid choice\n");
            }
        }
    }
    else if(choice==3)
    {
        printf("\n------ Thank You ------\n");
        break;
    }
}
    free(parking);
    return 0;
}
