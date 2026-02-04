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
    "some places.  The hallway intersects here, running to the north, " +
    "east and west, and there is a staircase running upwards to the " +
    "normal areas of the mansion.\n", 70));

   add_item(({"stairs", "staircase"}), break_string(
    "This old, wooden staircase has seen its better days.  You are " +
    "not even sure if it can hold your weight.\n", 70));

   add_item(({"wall", "walls"}), break_string(
    "Many old, gray stones of about the size of a human torso line the " +  
    "of this hallway.  They are bonded by mud, but alot of it has since " +
    "crumbled away.  Noone has bothered to repair the walls around here " +
    "for a very long time.\n", 70));

   add_prop(ROOM_I_LIGHT, 0);
   add_prop(ROOM_I_INSIDE, 0);

   add_exit(BASE + "hall2", "north", 0);
   add_exit(BASE + "hall4", "west", 0);
   add_exit(BASE + "hall6", "east", 0);
   add_exit(MANSION + "stairs", "up", "@@creak");
}

creak()
{
   write("You feel uneasy using these old stairs, but you continue " +
    "anyhow.\n");
   write("CREAK!!\n");
   write("CRACK!!\n");
   return 0;
}
