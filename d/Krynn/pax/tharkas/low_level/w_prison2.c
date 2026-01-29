/*
   Pax Tharkas, Low level, womens prisons.

   w_prison2.c
   -----------

   Coded ........: 95/01/08
   By ...........: Jeremiah

   Latest update : 95/07/27
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
   set_short("Prison room");
   set_long("You are standing in a dimly lit room. The walls in here are " +
            "moist and fetid. The air feels heavy and dank. The " +
            "floor is covered with straw mats. Small piles of red coloured " +
            "clothings have been carefully placed along the western wall. " +
            "Next to some of the mats lies small bundles of clothings. " +
            "A wooden barrel has been placed in the southeastern corner. " +
            "Some old mugs and pots stands next to the wooden " +
            "barrel. The room is crowded with poorly dressed women, " +
            "sitting on the rude mats. The only way out of here is " +
            "through the door.\n");

   INSIDE;
   add_prop(ROOM_I_LIGHT,1);

   add_item(({"mat", "mats"}), "The mats are nothing more than large " +
            "sacks filled with straw. They don't look as if they're " +
            "comfortable at all.\n");

   add_item(({"clothing", "clothings"}), "The clothings next to the mats " +
            "looks like the remaining belongings of these poor women. " +
            "The clothings in the piles along the wall, are red pieces " +
            "of clothing for different purposes.\n");     

   add_item(({"barrel", "wooden barrel"}), "The wooden barrel is " +
            "filled with water. You are not sure it looks particularly " +
            "fresh. It doesn't reek foul either.\n");

   add_item(({"mug", "mugs"}), "These are simple mugs made of different " +
            "material. Obviously used to drink water from the barrel.\n");

   add_item(({"pot", "pots"}), "Iron pots. Some of them are filled with " +
            "water.\n"); 

   add_item("women", "The women are sitting on the mats sewing. You " +
            "recognize what they are sewing as clothings worn by the " +
            "draconians of the red dragon army. They all look miserable. " +
            "Their faces pale and wan, their bodies thin and gaunt " +
            "from the lack of nourishing food.\n");

   set_alarm(30.0,360.0,"do_scurry");

   door = clone_object(POBJ + "prison_door2b");
   door->move(TO);
}


void
init()
{
   ::init();
   add_action("drink_water", "drink");
}


void
do_scurry()
{
   tell_room(TO, "A rat scurries across the floor.\n");
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


