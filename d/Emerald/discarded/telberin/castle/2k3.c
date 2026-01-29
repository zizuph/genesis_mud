/*
 * 2k3.c
 * This is part of the long hallway on the second floor of
 * Castle Telberin.
 * by Alaron August 30, 1996
 */

#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Hallway");
    set_long("   The hallway here is dimly lit with a yellow-orange "+
	     "flickering lamplight. The dim glow lends a feeling of "+
	     "solemnity and calmness to the hall. The emerald green "+
	     "walls only add to the somber feeling of the hallway "+
	     "by reflecting the glow off of surfaces so finely carved "+
	     "that it is nearly impossible to tell where the stones "+
	     "were joined. The long hallway continues off into the amber "+
	     "glow to the east and west.\n\n");

    add_item(({"light", "lamplight"}),
	     "The lamplight is all around you. It flickers gently back "+
	     "and forth, causing soft shadows to sway against the emerald "+
	     "green wall background.\n");

    add_prop(ROOM_I_INSIDE, 1);
    
    add_exit(CASTLE_DIR + "2k4","east",0);
    add_exit(CASTLE_DIR + "2k2","west",0);
}

