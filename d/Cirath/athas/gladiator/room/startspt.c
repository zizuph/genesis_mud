/* startspt.c: Gladiator start room: Serpine, 4-24-95. */
#pragma save_binary

inherit "/std/room";
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "defs.h"

#define DEBUG

void create_room()
{
    set_short("sleeping chamber");
    set_long("The din from the north is drowned out by the sounds of " +
      "snoring gladiators. Their sleeping arrangements range from "+
      "the floor to actual beds, but all are too tired to care "+
      "what is beneath them.\n"+
      "You may <start here>.\n");

    add_cmd_item("gladiator", "wake", "You have a deathwish?\n");

    add_item("floor", "Its filthy, hard, and cold. Not all that unlike the "+
      "gladiators sleeping upon it.\n");

    add_item(({"bed", "beds"}), "Only the high ranking warriors get this "+
      "luxury. Victory isn't its own reward.\n");

    INSIDE

    add_exit(GLAD_ROOM+"gldboard.c", "north", 0, 1);
    add_exit("post", "west", 0, 1);
//    add_exit("rack_room", "south", 0, 1);
    add_exit("cboard", "east", 0, 1);
    
}

int
start(string str)
{
    NF("Start where?\n");
    if (str != "here") return 0;

    NF("Only the Gladiators of Athas may sleep here.\n");
    if (!IS_MEMBER(TP)) return 0;

    TP->set_default_start_location(GLAD_ROOM+"startspt");
    write("This shall be the place to rest your weary head.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action("start" ,"start");
}
