/*
 * FOODHALL.c
 * Food Hall in the Caverns
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   object door;
   
   set_short("Food Hall");
   set_long("   You are standing in a passageway off of the main "+
	    "hall. The sounds of banging dishes and pots clang up "+
	    "out of the kitchen area to the south, while loud "+
	    "and boisterous singing and shouting booms out of the "+
	    "eating area to the east. There are rotting bits and "+
	    "piece of food everywhere, the smell of which mingles "+
	    "with the smells of fresh food, causing an overload "+
	    "of the senses. Huge piles of dishes are stacked "+
	    "haphazardly on every table.\n\n");
   
   add_item(({"piles","piles of dishes","dishes","dish","pile"}),
	    "The dishes are piled high on every table. "+
	    "Some are broken some are not, but "+
	    "all of them have plenty of rotten food on "+
	    "them.\n");

   add_item(({"tables","table"}),
	    "There are several tables here, all piled "+
	    "high with dirty dishes.\n");
   
   add_item(({"food","pieces of food","rotting food",
		"pieces of rotting food"}),
	    "This stuff can hardly be called food. It is so decomposed "+
	    "that you cannot tell what it once was.\n");

   add_exit(THIS_DIR + "main4.c", "west");
   add_exit(THIS_DIR + "kitchen.c", "south");
   add_exit(THIS_DIR + "banquet1.c", "east");

   door=clone_object(THIS_DIR+"obj/kitchen_door.c");
   door->move(this_object());
}

void
enter_inv(object from, object ob)
{
   ::enter_inv();
   /*
   if(ob->query_average_stat()<<70)
      {
      write(BS("A massive burly cook steps in front of you and "+
            "grabs you by the ear. He screams at you: Get in that "+
            "kitchen and start peeling those potatoes...NOW!\n"+
            "You scurry into the kitchen and to the pantry as you "+
            "feel the eyes of the cook boring into the back of your head.\n"));
      (ob->move_living(" scurries into the kitchen away from the cook", THIS_DIR+"kitchen"));
   }
   else
      write("The cook walks out of the kitchen and stares at you.\n"+
      "He says: I wouldn't go further if I were you...\n"+
      "         But it's your funeral not mine.\n"+
      "He then walks south through the kitchen door and locks it.\n");
   */
}
