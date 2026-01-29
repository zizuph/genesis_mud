/*
   Pax Tharkas, Low level, womens prisons.

   w_prison1.c
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

object door, quest_npc_maritta;
int    maritta_found = 0; /* 0 = Maritta NOT found */

void
reset_pax_room()
{
   if(objectp(quest_npc_maritta))
      return;

   maritta_found = 0;
}


create_pax_room()
{
   reset_pax_room();

   set_short("Prison room");
   set_long("You are standing in a dimly lit room. The walls are " +
            "moist and fetid, and the air in here is very dank. Rude " +
            "straw mats cover most of the floor. Pieces of " +
            "clothing have been carefully placed beside some of the " +
            "mats. A wooden barrel is standing in the northeastern " +
            "corner. Some mugs and pots are standing next to the " +
            "barrel. The room is crowded with women, dressed in rags, " +
            "sitting on the rude mats. The only way out of here is " +
            "through the door.\n");

   INSIDE;
   add_prop(ROOM_I_LIGHT,1);

   add_item(({"mat", "mats"}), "The mats are nothing more than large " +
            "sacks filled with straw. They don't look as if they're " +
            "comfortable at all.\n");

   add_item(({"clothing", "clothings"}), "Some of the clothings looks " +
            "like the remaining belongings of the poor women. Others " +
            "are red pieces of clothing for different purposes.\n");     

   add_item(({"barrel", "wooden barrel"}), "The wooden barrel is " +
            "filled with water. You are not sure it looks particularly " +
            "fresh. It doesn't reek foul either.\n");

   add_item(({"mug", "mugs"}), "These are simple mugs made of different " +
            "material. Obviously used to drink water from the barrel.\n");

   add_item(({"pot", "pots"}), "Iron pots. most of them are filled with " +
            "water.\n"); 

   add_item(({"women", "prisoners"}), "@@women_descr");

   door = clone_object(POBJ + "prison_door1b");
   door->move(TO);
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


string
women_descr()
{
   write("The women are sitting on the mats sewing. You recognize " +
         "what they are sewing as clothings worn by the draconians " +
         "of the red dragon army. They all look miserable Their faces " +
         "pale and wan, their bodies thin and gaunt, from the lack of " + 
         "nourishing food.\n");

   if (!present("maritta",TO) && maritta_found == 0)
   {
      write("A woman stands up and approaches you.\n");
      say("A woman stands up and approaches " + QCTNAME(TP) + ".\n"); 
      quest_npc_maritta = clone_object(PMONSTER + "maritta");
      quest_npc_maritta->move(TO);
      maritta_found = 1;
   }
   return "";
}
