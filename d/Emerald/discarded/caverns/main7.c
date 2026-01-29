/*
 * MAIN7.c
 * Main Passage through the caverns.
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   set_short("Main Hall - North");
   set_long("   You are in what looks to be a central passage maneuvering "+
	    "through a vast network of smaller caves. Hundreds of little "+
	    "caves connect and join off from here, but most are about "+
	    "the size of small animals. The main passage continues "+
	    "to the southeast and to the north, while a smaller passage "+
	    "branches off to the west. The sound of water dripping "+
	    "echos throughout the cavern. The sound of the echo makes "+
	    "you feel very alone and isolated in these caverns.\n\n");

   
   add_prop(ROOM_I_INSIDE, 1);

   add_item( ({"caves", "little caves", "branches"}),
	     "Hundreds of caves no bigger than small animals branch off "+
	     "in all directions from this main passage.\n");

   add_exit(THIS_DIR + "main8","north");
   add_exit(THIS_DIR + "wturn5","west");
   add_exit(THIS_DIR + "main6","southeast");

   
}
