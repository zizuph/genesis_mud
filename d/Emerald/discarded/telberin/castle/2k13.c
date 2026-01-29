/*
 * 2k13.c
 * Second Floor Hallway, Castle Telberin.
 *  - Alaron January 5, 1997
 */

#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Hallway");
    set_long("You are in a long hallway. The hallway extends to the "+
	     "northeast and southwest from here. To the southwest, you "+
	     "notice an enormous, intricately carved archway as the hallway "+
	     "forks off in another direction. The hallway to the northeast "+
	     "makes a sharp turn around a dimly lit corner. Every so often "+
	     "you manage to hear the sound of people debating or shouting "+
	     "coming from the dim corridors to the southwest.\n\n");

    add_item(({"arch", "intricately carved arch", "archway", "room",
	       "southwest"}),
	     "You can't make out much detail of the arch from here. It looks "+
	     "quite beautiful, though.\n");
    
   add_exit(CASTLE_DIR + "2k5","northeast",0);
   add_exit(CASTLE_DIR + "2k6","southwest",0);
}
