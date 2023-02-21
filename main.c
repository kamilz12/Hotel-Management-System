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

void centerWord (char specialWord []);
float * costPerPerson (Hotel room [], int hotelSize, float pricePerPerson[]);
void freeRooms (Hotel room[], int hotelSize);
float hotelGain (Hotel room[],int hotelSize, float hotelProfits);

int main()
{   
    float * averagePerPerson, allProfits;
    int hotelSize, roomSize, available = 1, unavailable = 0;

    /*Number of rooms in hotel structure*/
    printf ("How many rooms in your hotel do you have? ");
    scanf ("%d", &hotelSize); 
    
    Hotel hotelRoom [hotelSize];

    averagePerPerson = (float*) calloc (hotelSize, sizeof(float)); 
    
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

    /*Cost per 1 person*/
    averagePerPerson = costPerPerson (hotelRoom, hotelSize, averagePerPerson);
    centerWord ("Cost per person");
    for (int i = 0; i < hotelSize; i++)
    {
         printf ("Cost per one person in room number %d: %f\n", i+1, averagePerPerson[i]);
    }

    /*Show free rooms*/
    freeRooms (hotelRoom, hotelSize);
    
    /*Profit from occupied rooms*/
    allProfits = hotelGain (hotelRoom, hotelSize, allProfits);
    centerWord ("Total income from occupied rooms");
    printf ("Total income from occupied rooms: %f\n", allProfits);

    /*List of all rooms*/
    centerWord ("All rooms");
    for (int i = 0; i < hotelSize; i++) 
    {
        printf ("Room %d,\t Code: %s,\t Price: %f, \tStatus: %d\n",i+1,hotelRoom[i].code, hotelRoom[i].price, hotelRoom[i].status);
    }

    free (averagePerPerson);

    return 0;

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
void freeRooms (Hotel room[], int hotelSize)
{
    bool noFree = true;
    int available = 1;
    centerWord ("Free Rooms");
    for (int i = 0; i < hotelSize; i++)
    {
       if (room[i].status == available)
       {
            printf ("Room %d,\tkod: %s,\tcena: %f,\tstatus: %d\n", i+1, room[i].code, room[i].price, room[i].status);
            noFree = false;
       }
    }
    if (noFree == true)
    {
        printf ("All rooms are occupied, no income\n");
    }
}

/*Total money income*/
float hotelGain (Hotel room[], int hotelSize, float hotelProfits)
{   
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
