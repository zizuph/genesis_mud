/*
 * 1jail.c
 * This is a jail cell in the underground caverns (pirate guild)
 * There is a prisoner here cloned by the clone_handler.
 *   - Alaron September 15, 1996
 */

#include "defs.h"
#include <stdproperties.h>

inherit BASECAVE;

void
create_cave()
{
   object door;
   
   
   set_short("North Cell");
   set_long("   This is a small, cramped prison cell. The cell here "+
	    "appears to be unlike the rest of the cells in the prison. It "+
	    "is free of the wet, slimy fungus which has attached itself "+
	    "to virtually all rock in this section of the caverns. Even "+
	    "more startling is that the cell is neat, orderly and there "+
	    "is even a food tray here that has been recently eaten from. "+
	    "A bed rests neatly against the back wall of the cell.\n\n");

   add_item(({"tray", "food tray"}),
	    "The tray is rather large and judging from the hefty amount "+
	    "of uneaten food, it must have been filled to overflowing. The "+
	    "leftover food even smells good. You wonder why someone "+
	    "in this foul cavern jail would deserve such relatively "+
	    "luxurious treatment.\n");

   add_item( ({"wet fungus", "fungus", "slimy fungus", "wet slimy fungus"}),
	    "The slimy, wet green fungus has attached itself to most of "+
	    "the jail cells in the cavern ... except this one. It is clean "+
	    "and free of the foul-smelling green substance. It must take "+
	    "a daily clean-up effort to keep the cell this clean. You wonder "+
	    "why someone this deep into the caverns in this horrible "+
	    "jail would deserve such luxurious treatment.\n");

   add_item(({"bed", "back wall"}),
	    "It is clean and tidy. It is neatly made with tighly "+
	    "tucked sheets.\n");

   add_exit(THIS_DIR + "2jail","south");

   seteuid(geteuid());
   door = clone_object(THIS_DIR+"obj/pdoor6b");
   door ->move(TO);
  
  /*
   *  prisoner = clone_object(THIS_DIR+"npc/prisoner1");
   *  prisoner ->move_living("into a room",TO);
   */
}
