#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct roomsInHotel
{
    char code[3];    //Code of room: available names p1,p2,p3
    float price;
    int status;     //room is available(1) or unavailable (0)
}Hotel;

int readRoomData (Hotel hotelRoom[]);
void saveRoomData (Hotel hotelRoom[], int hotelSize);
void enterCodeOfTheRoom (Hotel hotelRoom[], int workedRoom);
void enterRoomPrice (Hotel hotelRoom[], int workedRoom);
void enterRoomStatus (Hotel hotelRoom[], int workedRoom);
int typeMenuOption ();
int enterRoom (Hotel hotelRoom [],int hotelSize);
void mainMenu (Hotel hotelRoom[], int hotelSize);
void centerWord (char specialWord []);
float * costPerPerson (Hotel room [], int hotelSize, float pricePerPerson[]);
void freeHotelRooms (Hotel room[], int hotelSize);
float totalHotelGain (Hotel room[],int hotelSize);
void changeRoomData (Hotel room[], int hotelSize);

int main()
{
    int hotelSize = 1000; //maximum number of rooms in hotel

    Hotel hotelRoom [hotelSize];
    hotelSize = readRoomData(hotelRoom);
    mainMenu (hotelRoom, hotelSize);
    return 0;

}

int readRoomData (Hotel hotelRoom[])
{
    int numberRoomsInFile = 0;
    FILE * roomReadFile;
    roomReadFile = fopen("roomdata.dat", "rb");

    if (!roomReadFile) {
        printf("Failed to open file.\n");
    }

    while (fscanf(roomReadFile, "%2s,%f,%d\n", hotelRoom[numberRoomsInFile].code, &hotelRoom[numberRoomsInFile].price, &hotelRoom[numberRoomsInFile].status) == 3) {
        numberRoomsInFile++;
    }
    return numberRoomsInFile;
}

void saveRoomData (Hotel hotelRoom[], int hotelSize)
{
    FILE *roomDataFile = fopen ("roomdata.dat", "w");
    if (!roomDataFile) {
        printf ("Failed to open file\n");
        exit (EXIT_SUCCESS);
    }

    for (int i = 0; i < hotelSize; i++) {
        fprintf (roomDataFile, "%s,%.2f,%d\n", hotelRoom[i].code, hotelRoom[i].price, hotelRoom[i].status);
    }

    fclose (roomDataFile);
}

void enterCodeOfTheRoom (Hotel hotelRoom[], int workedRoom)
{
    int roomSize;
    do
    {
        printf ("Enter %d room size, maximum room size is 3: ", workedRoom+1);
        scanf ("%d", &roomSize);
        switch (roomSize)
        {
            case 1:
                strcpy (hotelRoom[workedRoom].code, "p1");
                break;
            case 2:
                strcpy (hotelRoom[workedRoom].code, "p2");
                break;
            case 3:
                strcpy (hotelRoom[workedRoom].code, "p3");
                break;
            case 4:
                strcpy (hotelRoom[workedRoom].code, "p4");
                break;
        }

    }while ((strcmp(hotelRoom[workedRoom].code, "p1") != 0) && (strcmp(hotelRoom[workedRoom].code, "p2") != 0) && (strcmp(hotelRoom[workedRoom].code, "p3") != 0) &&  (strcmp(hotelRoom[workedRoom].code, "p4") != 0));
}

void enterRoomPrice (Hotel hotelRoom[], int workedRoom)
{
    printf ("Enter price of room: ");
    scanf ("%f", &hotelRoom[workedRoom].price);
}

void setRoomStatus (Hotel hotelRoom[], int workedRoom)
{
    int available = 1, unavailable = 0;
    do
    {
        printf ("Room number %d is:\n0. Unavailable\n1. Available\nEnter number: ", workedRoom+1 );
        scanf ("%d", &hotelRoom[workedRoom].status);

    } while ((hotelRoom[workedRoom].status != available) && (hotelRoom[workedRoom].status != unavailable));
}

int typeMenuOption ()
{
    int menuID;
    printf("\n1. Cost per person\n2. Show free rooms\n3. Show all hotel profits\n4. Show all rooms in hotel\n5. Enter new room to your hotel\n6. Change data\n7. Save changes and exit\n8. Exit\nEnter number of function withone you want to choose: ");
    scanf ("%d", &menuID);
    return menuID;
}

int enterRoom(Hotel hotelRoom [], int hotelSize)
{
    int newRoomsNumber;
    printf ("How many rooms do you want to add to your hotel? ");
    scanf ("%d", &newRoomsNumber);
    for (int i = hotelSize; i < hotelSize + newRoomsNumber; i++)
    {
        /*Enter code of the room size*/
        enterCodeOfTheRoom (hotelRoom, i);
        /*Enter price of the room*/
        enterRoomPrice (hotelRoom, i);
        /*Status of the room */
        setRoomStatus (hotelRoom, i);
        printf ("\n");
    }
    return hotelSize + newRoomsNumber;
}

void mainMenu (Hotel hotelRoom[], int hotelSize)
{
    int menuOption;
    float * averagePerPerson, allProfits;
    averagePerPerson = (float*) calloc (hotelSize, sizeof(float));

    do
    {
        menuOption = typeMenuOption();
        switch (menuOption)
        {
            /*Cost per 1 person*/
            case 1:
                averagePerPerson = costPerPerson (hotelRoom, hotelSize, averagePerPerson);
                centerWord ("Cost per person");
                for (int i = 0; i < hotelSize; i++)
                {
                    printf ("Cost per one person in room number %d: %f\n", i+1, averagePerPerson[i]);
                }
                break;

                /*Show free rooms*/
            case 2:
                freeHotelRooms (hotelRoom, hotelSize);
                break;

                /*Profit from occupied rooms*/
            case 3:
                allProfits = totalHotelGain (hotelRoom, hotelSize);
                centerWord ("Total income from occupied rooms");
                printf ("Total income from occupied rooms: %f\n", allProfits);
                break;

                /*List of all rooms*/
            case 4:
                centerWord ("All rooms");
                for (int i = 0; i < hotelSize; i++)
                {
                    printf ("Room %d,\t Code: %s,\t Price: %f, \tStatus: %d\n",i+1,hotelRoom[i].code, hotelRoom[i].price, hotelRoom[i].status);
                }
                break;

            case 5:
                hotelSize = enterRoom (hotelRoom, hotelSize);
                break;

            case 6:
                changeRoomData (hotelRoom, hotelSize);
                break;

            case 7:
                printf ("Saved changes, bye bye :)");
                saveRoomData (hotelRoom, hotelSize);
                exit (0);

            case 8:
                printf ("Bye bye :)");
                exit(0);

            default:
                printf ("Wrong choice");
                break;

        }
    }
    while (menuOption>7 || menuOption<9);
    free (averagePerPerson);
}

/*headline function*/
void centerWord (char specialWord [])
{
    int pad = (45 - strlen (specialWord))/2;
    printf ("\n%*s%s%*s\n", pad, " ", specialWord, pad, " ");
}

/*Calculating a room price for one person*/
float * costPerPerson (Hotel room [], int hotelSize, float pricePerPerson[])
{
    for (int i = 0; i < hotelSize; i++)
    {
        if(strcmp(room[i].code, "p1") == 0)
        {
            pricePerPerson[i] = room[i].price;
        }

        else if(strcmp(room[i].code, "p2") == 0)
        {
            pricePerPerson[i] = room[i].price / 2;
        }

        else if(strcmp(room[i].code, "p3") == 0)
        {
            pricePerPerson[i] = room[i].price / 3;
        }
    }
    return pricePerPerson;
}

/*Printing all free rooms*/
void freeHotelRooms (Hotel room[], int hotelSize)
{
    bool noFreeRoom = true;
    int available = 1;
    centerWord ("Free Rooms");
    for (int i = 0; i < hotelSize; i++)
    {
        if (room[i].status == available)
        {
            printf ("Room %d,\tkod: %s,\tcena: %f,\tstatus: %d\n", i+1, room[i].code, room[i].price, room[i].status);
            noFreeRoom = false;
        }
    }
    if (noFreeRoom == true)
    {
        printf ("All rooms are occupied, no income\n");
    }
}

/*Total money income*/
float totalHotelGain (Hotel room[], int hotelSize)
{
    float hotelProfits = 0;
    int unavailable = 0;
    for (int i = 0; i < hotelSize; i++)
    {
        if (room[i].status == unavailable)
        {
            hotelProfits += room[i].price;
        }
    }
    return hotelProfits;
}

void changeRoomData (Hotel hotelRoom[], int hotelSize)
{
    int roomBeingChanged;
    printf ("Choose room which one you want to change: ");
    scanf ("%d", &roomBeingChanged);

    /*Enter code of the room*/
    enterCodeOfTheRoom (hotelRoom, roomBeingChanged-1);
    /*Enter price of the room*/
    enterRoomPrice (hotelRoom, roomBeingChanged-1);
    /*Status of the room */
    setRoomStatus (hotelRoom, roomBeingChanged-1);
}
