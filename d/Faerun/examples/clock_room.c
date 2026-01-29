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

void
create_faerun_room()
{
    setuid(); 
    seteuid(getuid());
    
    ::create_faerun_room();
    set_short("A green lawn next to babbling brook");
    set_extraline("This room shows you how the time functions work and look. " + CAP(LIGHT_DESC) + " bathes the lawn.\n\n" +
    "LIGHT_DESC - will show: " + LIGHT_DESC + "\n\n" +
    "TIME_DESC - will show: " + TIME_DESC + "\n\n" +
    "TIME_DESC_LONG - will show: " + TIME_DESC_LONG + "\n\n" + 
    "TIME_DESC_ROOM - will show: " + TIME_DESC_ROOM + "\n\n" +
    "IS_NIGHT - " + IS_NIGHT + ", 0 isnt night, 1 is night\n\n" + 
    "IS_DAY - " + IS_DAY + ", 0 isn't daytime, 1 is daytime\n\n" +
    "DAY_PART - " + DAY_PART + "\n\n" +
    "HORIZION_DESC - will show: " + HORIZION_DESC + "\n\n");

    set_room_tell_time(60);
    add_room_tell("Fish jump in the brook.");
    add_room_tell("The brook babbles along.");
    add_room_tell("Water sprays up from the brook.");

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