/*
   Pax Tharkas, Low level, maidens prison.

   m_prison.c
   ----------

   Coded ........: 95/01/09
   By ...........: Jeremiah

   Latest update : 95/02/03
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

object door;

create_pax_room()
{
   set_short("prison room");
   set_long("You are in a large room. The air feels dank and unpleasant. " +
            "The walls are dirty and humid. Straw mats have been placed " +
            "along the walls of the room, and a few have been placed near " +
            "the center. A barrel is standing near the door. A few " +
            "ladles are hanging from the barrel, and a few old mugs lies " +
            "next to it. A stack of tin plates and an iron pot stands " +
            "near the barrel.\n");

   INSIDE;
   add_prop(ROOM_I_LIGHT,1);


   add_item(({"mats", "straw mats"}), "The mats are made of rude linen " +
            "filled with straw.\n");

   add_item("barrel", "It's a wooden barrel half filled with water.\n");

   add_item(({"mug", "mugs"}), "Crude mugs. They might be used for " +
            "drinking water from the barrel.\n");

   add_item(({"pot", "iron pot"}), "An old iron pot filled with dirty " +
            "water. There's a piece of old cloth in the water. It " +
            "looks as if someone has been cleaning the plates.\n");

   add_item(({"plate", "plates", "tin plates"}), "Old tin plates. " +
            "They all look rather clean.\n");

   add_item(({"ladle", "ladles"}), "Ladles hanging on the barrel. " +
            "They could be used to pour water from the barrel " +
            "and into other beholders.\n"); 


   door = clone_object(POBJ + "prison_door3b");
   door->move (TO);
}


void
init()
{
   ::init();
   add_action("drink_water", "drink");
}


int
drink_water(string what)
{
   if (what == "water" || what == "water from barrel")
   {
      write("Nahh... Better leave it.\n");
      return 1;
   }
   else
   {
      NF("Drink what?\n");
      return 0;
   }
}


