inherit "/d/Shire/room";
#include "defs.h"

void
create_room()
{
   set_short("A warm hot place, deep in the mines");
   set_long("The air here is hot enough to cook raw meat, "+
	    "and the steam rising from the ground obscures "+
	    "all hope of clear vision. It would be quite difficult "+
	    "to make anything out if not for an eerie red glow that "+
	    "seems to come from no place in particular.\n");


   add_item(({"steam","ground","air"}),
   "The steam rises from the ground, heating the air in this place. "+
   "You wonder what could make so much heat. The steam is so thick "+
   "the ground is but a blur under (or is it over) your feet.\n");

   add_item(({"red glow","glow","eerie red glow","vision"}),
   "The glow seems to echo off the steam like sound, bouncing across "+
   "your field of vision. It is obviously not natural.\n");


   add_prop(ROOM_I_INSIDE, 1);

   add_exit(MINES_DIR + "lair/lair2","east",0,3);
   add_exit(MINES_DIR + "lair/lair3","west",0,3);
   add_exit(MINES_DIR + "lair/lair4","northeast",0,3);
   add_exit(MINES_DIR + "lair/stair2", "up", 0, 12);
   set_noshow_obvious(1);

}
