/*
 * 2k4.c
 * Second Floor hallway of Castle Telberin
 *   - Alaron September 11, 1996
 */

#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();

    set_short("Hallway");
    set_long("   The hallway here is dimly illuminated by a flickering "+
	     "yellow-orange lamplight. The dim, soft light adds a feeling "+
	     "of solitude and serenity to the solemn hall. The amazing "+
	     "emerald green walls reflect the flickering glow, adding "+
	     "an additional soft light to the hall. The surfaces of the "+
	     "wall are so smooth and so expertly carved that you have to "+
	     "struggle to see where the stones have been joined. The "+
	     "amber glow dimly reveals the hallway continuing to the west, "+
	     "northeast and to the southeast where you can hear loud, "+
	     "boisterous voices echoing through the hall.\n\n");

    add_item( ({"surface", "surfaces"}),
	     "The surfaces of the walls are so smooth and so expertly "+
	     "carved that you have to struggle and squint to make out "+
	     "the nearly invisible line where the stones were joined.\n");
    
    add_prop(ROOM_I_INSIDE,1);

    add_exit(CASTLE_DIR + "2k10","northeast",0);
    add_exit(CASTLE_DIR + "2k3","west",0);
    add_exit(CASTLE_DIR + "2k5","southeast",0);
}
