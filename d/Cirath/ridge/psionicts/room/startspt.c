/* startspt.c: Gladiator start room: Serpine, 4-24-95. */
#pragma save_binary

inherit "/d/Cirath/std/room";
#include "defs.h"

#define DEBUG

void create_room()
{
  set_short("sleepy cavern");
  set_long("The din from the north is drowned out by the sounds of "+
           "snoring gladiators. Their sleeping arrangements range from "+
           "the floor to actual beds, but all are too tired to care "+
           "what is beneath them.\n"+
           "You may <start here>.\n");

  

  INSIDE

  add_exit(PSION_ROOM+"hallway3.c", "southwest", 0, 1);
}

int
start(string str)
{
    NF("Start where?\n");
    if (str != "here") return 0;

    NF("Only the Gladiators of Athas may sleep here.\n");
   // if (!IS_MEMBER(TP)) return 0;

    TP->set_default_start_location(PSION_ROOM+"startspt");
    write("This shall be the place to rest your weary head.\n");
    return 1;
}

void
init()
{
  ::init();
  add_action("start" ,"start");
}
