/*
* Created by: Luther
* Date: Dec 2001
*
* File: /d/Cirath/guilds/militia/room/startroom.c
* Comments: Militia Startroom
*/

inherit "/std/room";
#include "defs.h"
#define RACK MILITIA_OBJ+"rack.c"

object rack;
/*
void
reset_room()
{
    if(!rack)
    {
        rack = clone_object(RACK);
        rack->move(this_object());
    }
}
*/

void
create_room()
{
    set_short("Barracks");
    set_long("Narrow cots line the walls here.  Some are occupied by "
    	+"sleeping Militia members, others are empty.  Any member of "
    	+"the Tyrian Militia may rest here when need be.  All that "
    	+"has to be done is for the member to request to <start here>.\n");
    add_item("cots","They look to be more comfortable that the hard "
    	+"floor.\n");
   INSIDE

  add_exit(MILITIA_ROOM + "store", "east", 0, 1);
   add_exit(MILITIA_ROOM + "m11","north");
    reset_room();
}

int
start(string str)
{
    NF("Start where?\n");
    if (str != "here") return 0;

    NF("Only the Tyrian Militia may sleep here.\n");
    if (!IS_TYR_MILITIA(TP)) return 0;

    TP->set_default_start_location(MILITIA_ROOM+"startroom");
    write("This shall be the place to rest your weary head.\n");
    return 1;
}

void
init()
{
  ::init();
  add_action("start" ,"start");
}

