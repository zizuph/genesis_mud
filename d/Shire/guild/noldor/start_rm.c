/*
 * Start Room for Noldor Guild
 * By Finwe, August 2000
 */
 
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/guild/noldor/noldor.h"
#include <std.h>
 
inherit BUILDING_BASE;

int okay_to_start;
void create_guild_room()
{
    set_short("A quiet room");

    set_long("This is where elves come to rest their minds " +
        "when they need to leave the realms for a time. " +
        "Spread around the room are various chairs, settes, " +
        "divans and a few simple cots. Free standing lamps are " +
        "scattered about filling the room with a soft light to " +
        "create a relaxed atmosphere. Some elves are already  " +
        "resting here and look peaceful in their relaxed state. A " +
        "silver plaque is attached to a wall.\n");

    add_item(({"cot", "cots"}),
        "The cots are made of mats resting inside of a simple " +
        "wooden frame. They provide a place for elves to lie " +
        "down and rest.\n");
    add_item(({"wooden frame", "wooden frames", "frame", "frame"}),
        "They are carved from dark wood and sit low to the " +
        "ground. They hold a mat for elves to lie down on.\n");
    add_item("plaque",
        "The place is attached to a wall next to the east door. " +
        "It is made of silver and on it is something written " +
        "in fine elvish lettering.\n");
    add_cmd_item("plaque","read","@@read_sign@@");

    
    
    add_cmd_item("plaque","read",
        "After a long and difficult journey, you may relax here " +
        "and awake here. Be warned, if you relax to long and " +
        "don't return, you may awake and no longer be " +
        "recognized as a Noldor.\n");

    set_extra_wall("Large windows are set in the east wall and " +
        "the south walls. They let in lots of @@daylight_desc@@.\n");
    set_extra_window("The windows are set into the south and east walls.");

    add_item(({"south window", "southern window"}),
         "A beautiful garden is laid out in front of the " +
         "building, with a large tree in its center.\n");
    add_item(({"east window", "eastern window"}),
         "The valley spreads to the east and up to the mountains.\n");
   
    add_exit(NOLGLD_DIR + "rest_rm","north");
    add_exit(NOLGLD_DIR + "foyer","west");
}

init()
{
  ::init();

    add_action("start", "relax");

}

int
start(string str)
{
    if(str == "here")
    {
        TP->set_default_start_location(NOLGLD_DIR + "start_rm");
        write("You will awaken here when you return.\n");
        return 1;

    }

    write("Do what?\n");
    return 1;
}


string
read_sign()
{
    return "\n\n"+
    "       +---------------------------------------------------+\n"+
    "       |                                                   |\n"+
    "       |   O                                           O   |\n"+
    "       |                                                   |\n"+
    "       |   After a long and difficult journey, you may     |\n"+
    "       |   <relax here> awake here. Be warned, if you      |\n"+
    "       |   relax to long and don't return, you may awake   |\n"+
    "       |   and no longer be recognized as a Noldo.         |\n"+
    "       |                                                   |\n"+
    "       |   O                                           O   |\n"+
    "       |                                                   |\n"+
    "       +---------------------------------------------------+\n\n";
}
