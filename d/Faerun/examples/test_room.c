/*
 * Clock room to demonstrate how the clock functions work and look
 * -- Finwe, June 2016
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>

// this is a base file for outdoor rooms in Faerun
inherit FAERUN_OUTDOOR_BASE;

#define DELAY (random(1) + 3)

string test_tell();
void no_caravan(int step);

void
create_faerun_room()
{
    setuid(); 
    seteuid(getuid());
    
    ::create_faerun_room();
    set_short("Outside the north gate of Waterdeep");
    set_extraline("The gate is closed to travellers from the North.\n");

    set_room_tell_time(45);
    add_room_tell("@@test_tell@@");

    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}

void
init()
{
    ::init();
}

string test_tell()
{
    string str = one_of_list(({no_caravan(0),
                "Frogs ribbt.",
                "birds sing.",
                "Bunnies hop.", 
                "Deer graze."}));
    return(str);
}

void no_caravan(int step)
{
    switch(step)
    {
        case 0:
            write("A caravan comes up to the North Gate and knocks on it.\n");
            set_alarm(itof(DELAY),0.0,&no_caravan(1));
            break;
        case 1:
            write("The gate opens and a guard steps out.\n");
            set_alarm(itof(DELAY),0.0,&no_caravan(2));
            break;
        case 2:
            write("The caravan leader says, We have come to trade with your great city!\n");
            set_alarm(itof(DELAY),0.0,&no_caravan(3));
            break;
        case 3:
            write("The guard says, The city is closed from this gate by orders of the Lords of Waterdeep You cannot enter here.\n");
            set_alarm(itof(DELAY),0.0,&no_caravan(4));
            break;
        case 4:
            write("But we have traveled far to your fair city, states the caravan leader.\n");
            set_alarm(itof(DELAY),0.0,&no_caravan(5));
            break;
        case 5:
            write("Begone, lest I throw you all in jail!\n");
            set_alarm(itof(DELAY),0.0,&no_caravan(6));
            break;
        case 6:
            write("The caravan turns around, and heads north, and disappearing in the distance\n");
            set_alarm(itof(DELAY),0.0,&no_caravan(7));
            break;
        case 7:
            write("The guard goes back in the city and the gate closes.\n");
            break;
    }
}        