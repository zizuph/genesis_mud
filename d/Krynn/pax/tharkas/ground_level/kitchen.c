/*
   Pax Tharkas, Ground level, Kitchen.

   kitchen.c
   ---------

   Coded ........: 95/01/25
   By ...........: Jeremiah

   Latest update : 95/07/27
   By ...........: Jeremiah


   Navarre: Feb 16th 2008.
     Changed presense check in reset room to objectp instead of present.
     With the increased uptimes the rooms spawn too many dwarves.
*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

object gully1, gully2, gully3;


reset_pax_room()
{
   object gully;

   if(!objectp(gully1))
   {
      gully1 = clone_object(PMONSTER + "gully");
      gully1->arm_me();
      gully1->move(TO);
   }

   if(!objectp(gully2))
   {
      gully2 = clone_object(PMONSTER + "gully");
      gully2->arm_me();
      gully2->move(TO);
   }

   if(!objectp(gully3))
   {
      gully3 = clone_object(PMONSTER + "gully");
      gully3->arm_me();
      gully3->move(TO);
   }
}

void
create_pax_room()
{
   set_short("kitchen");
   set_long("You are standing in the fortress kitchen. A wooden table " + 
            "runs along the entire north wall. Several cupboards and " +
            "shelves are hanging on the wall above the table. A rack of " +
            "shelves line the south wall, right next to the door. " +
            "Four large ovens are standing in the east end of the " +
            "kitchen. This place looks a bit messy. There's a smell " +
            "of burned food coming from the ovens.\n");
	
   INSIDE;

   add_item("door", "The door to the kitchen is made of a sturdy wood, " +
            "most likely to keep out late night kitchen-raiders!\n");

   add_item("table", "The long table is made of wood. The wood has been " +
            "gently planed and treated with great care. Little carvings " +
            "decorate the edge and the corners of the table. This is a " +
            "fine piece of craftsmanship.\n");

   add_item(({"cupboard", "cupboards"}),"These are cupboards made of " +
            "some sort of dark wood. Everything is nicely assembled, " +
            "they must have been made by someone who really cares about " +
            "woodwork.\n");

   add_item(({"rack", "shelves", "rack of shelves"}), "The rack and the " +
            "shelves are made of a sort of darkish wood. The shelves " +
            "can be placed in different positions, making it possible " +
            "to adjust the shelves to fit different needs for shelf " +
            "space.\n");

   add_item(({"oven", "ovens"}), "The Ovens are large iron cast ovens. " +
            "Each of them can be heated by lighting a fire in the lower " +
            "part of it. The upper part is for preparing food. " +
            "The ovens are empty, but you discover that the burned " +
            "smell comes from streaks of burned fat running down the oven " +
            "surface.\n");

   add_exit(GROUND_LEVEL + "corridor4", "south",0);

   reset_pax_room();
}



