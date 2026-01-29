/*
 * Path in the Mere of Dead Men
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_MERE;

//string extraline = "A stone building stands here.";
string extraline = "";

void
create_mere()
{

    set_short("Deep in the mere");
    set_extraline(mere_descr4(extraline));
    
    add_std_herbs("mere");

    reset_faerun_room();
/*
    add_item(({"building", "stone building"}),
        "The building is made of stones that have been hauled here. It is squat and round, and looks diseased. Still, the building looks serviceable. Above the door is a logo.\n");
    add_item(({"emblem"}),
        "The emblem is round and hangs above the door. Magically etched onto it is a white human skull against a black field.\n");
    add_item(({"blocks", "stone blocks"}),
        "They are rounded and stacked to form the temple. The blocks look to be of granite and were brought to this place.\n");
    add_item(({"logo"}),
        "It is made of stone and weathered from countless years. The logo is in the likeness of a jawless skull on a weathered sunburst.\n");
*/    
    
    add_exit(ROOM_DIR + "me22", "northeast");
    add_exit(ROOM_DIR + "me21", "northwest");
    add_exit(ROOM_DIR + "me30", "southeast");
    add_exit(ROOM_DIR + "me29", "southwest");
//    add_exit(TEMPLE_DIR + "myrkul/mere_temple", "in");
}

public void
init()
{
    ::init();
//    add_action("do_enter","enter");
}

void
reset_faerun_room()
{
    set_searched(0);
}

int
do_enter(string str)
{
    if (!str)
    return 0;
 
    if ((str == "temple") || (str == "building") || (str == "stone building"))
    {
        write("You enter the stone building.\n");
        say(QCTNAME(TP)+ " leaves into the stone building.\n");
        TP->move_living("M",TEMPLE_DIR + "cyric/mere_temple",1);
        say(QCTNAME(TP)+" arrives.\n");
        return 1;
    }

    write("Enter what ? A "+str+" ? You must be kidding!\n");
    return 1;
}