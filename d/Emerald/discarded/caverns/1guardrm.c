/*
 * 1GUARDRM.c
 * This is the southern guard room in the caverns.
 * caverns_clone_handler.c takes care of keeping this room populated
 * w/ npcs.
 * - Alaron September 13, 1996
 */

#include "defs.h"
#include <stdproperties.h>

inherit BASECAVE;

void
create_cave()
{
   object door1, door2;
   
   set_short("Guardroom");
   set_long("   This is a large, rounded chamber which seems to have "+
	    "been carved out of the rock. At one point it may have "+
	    "been a natural chamber, but it is now carved and "+
	    "hollowed to give the impression of a room. In fact, it "+
	    "looks a lot like a guard's station. Fighting against the "+
	    "foul stench that invades the area, you notice a "+
	    "prison cell to the southeast and an iron door leading "+
	    "out to the northeast. The hollowed-out room opens into "+
	    "natural cave and darkness to the west. Several lamps "+
	    "hang on the walls here, providing dim illumination.\n\n");

    add_item( ({"cell", "prison cell"}),
         "The prison cell is dirty and covered with a foul, green fungus "+
         "and black, thick stains from running water over the "+
         "metal door.\n");

   add_item(({"lamps","pitons", "iron pitons"}),
	    "The lamps hang on the walls from iron pitons which have "+
	    "been hammered into the rock.\n");
   
   add_exit(THIS_DIR + "main9", "west");
   add_exit(THIS_DIR + "7jail", "northeast");
   add_exit(THIS_DIR + "9jail", "southeast");
   
   seteuid(geteuid());
   door1 = clone_object(THIS_DIR+"obj/pdoor1a");
   door1 ->move(TO);
   door2 = clone_object(THIS_DIR+"obj/pdoor2a");
   door2 ->move(TO);

}
