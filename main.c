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

void saveRoomData (Hotel hotelRoom[], int hotelSize);
int typeMenuOption ();
Hotel enterRoom (Hotel hotelRoom [],int hotelSize);
void mainMenu (Hotel hotelRoom[], int hotelSize);
void centerWord (char specialWord []);
float * costPerPerson (Hotel room [], int hotelSize, float pricePerPerson[]);
void freeHotelRooms (Hotel room[], int hotelSize);
float totalHotelGain (Hotel room[],int hotelSize);


int main()
{   
    int hotelSize;
    /*Number of rooms in hotel structure*/
    printf ("How many rooms in your hotel do you have? ");
    scanf ("%d", &hotelSize);
    
    Hotel hotelRoom [hotelSize];
    /*Input information about rooms*/
    hotelRoom [hotelSize] = enterRoom (hotelRoom, hotelSize);
    saveRoomData (hotelRoom, hotelSize);
    mainMenu (hotelRoom, hotelSize);

    return 0;

}

void saveRoomData (Hotel hotelRoom[], int hotelSize)
{
    FILE *roomData = fopen("roomdata.txt", "a");
    if (roomData == NULL) {
        printf("Failed to open file\n");
        exit(0);
    }
    for (int i = 0; i < hotelSize; i++) {
        fprintf(roomData, "%s %f %d\n", hotelRoom[i].code,hotelRoom[i].price,hotelRoom[i].status);
    }
    fclose (roomData);
}

Hotel enterRoom(Hotel hotelRoom [], int hotelSize)
{
    int available = 1, unavailable = 0, roomSize;
    for (int i = 0; i < hotelSize; i++) 
    {  
        /*Enter room size*/
        do
        {
            printf ("Enter %d room size, maximum room size is 3: ", i+1);
            scanf ("%d", &roomSize);
            switch (roomSize)
            {
                case 1:
                    strcpy (hotelRoom[i].code, "p1");
                    break;
                case 2:
                    strcpy (hotelRoom[i].code, "p2");
                    break;
                case 3:
                    strcpy (hotelRoom[i].code, "p3");
                    break;
            }

        }while ((strcmp(hotelRoom[i].code, "p1") != 0) && (strcmp(hotelRoom[i].code, "p2") != 0) && (strcmp(hotelRoom[i].code, "p3") != 0));

        /*Enter price room*/    
        printf ("Enter the price of your room %d :", i+1);
        scanf ("%f", &hotelRoom[i].price);


        /*Status of the room */   
        do
        {
            printf ("Room number %d is:\n0. Unavailable\n1. Available\nEnter number: ", i+1 );
            scanf ("%d", &hotelRoom[i].status);

        } while ((hotelRoom[i].status != available) && (hotelRoom[i].status != unavailable));
        printf ("\n");
    }
    return hotelRoom[hotelSize];
}

int typeMenuOption ()
{
    int menuID;
    printf ("\n1. Cost per person\n2. Show free rooms\n3. Show all hotel profits\n4. Show all rooms in hotel\n5. Exit\nEnter number of function withone you want to choose: ");
    scanf ("%d", &menuID);
    return menuID;
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
            printf ("Exit");
            exit(0);
            break;

        default: 
            printf ("Wrong choice");
            break;

    }
    }
    while (menuOption != 5);
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
