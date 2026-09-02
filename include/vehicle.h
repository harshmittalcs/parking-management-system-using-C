#ifndef VEHICLE_H
#define VEHICLE_H

struct Vehicle
{
    char number[20];
    char id[10];
    int slot;
    int entry_time;
};

void addVehicle();
void removeVehicle();
void viewSlots();
void searchVehicle();
void viewReport();
void searchbyid();
void generateReport();

#endif
