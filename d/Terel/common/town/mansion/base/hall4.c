/*  A room in the Basement of the Mansion, Coded by Vader on 8/21/92  */
inherit "/std/room.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

create_room()
{
   set_short("A basement hallway");
   set_long(break_string(
    "You are walking through a dark, dank, dusty hallway.  The dust in the " +
    "air makes you feel like you want to sneeze.  The walls are made of " +
    "large stones, bonded together by dried up mud, which is crumbling in " +
    "some places.  The hallway continues to your north and east.\n", 70));



   add_item(({"wall", "walls"}), break_string(
    "Many old, gray stones of about the size of a human torso line the " +  
    "of this hallway.  They are bonded by mud, but alot of it has since " +
    "crumbled away.  Noone has bothered to repair the walls around here " +
    "for a very long time.\n", 70));

   add_prop(ROOM_I_LIGHT, 0);
   add_prop(ROOM_I_INSIDE, 1);

   add_exit(BASE + "hall1", "north", 0);
   add_exit(BASE + "hall5", "east", 0);
}
