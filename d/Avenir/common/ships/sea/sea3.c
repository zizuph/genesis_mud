inherit "/std/room";

#include "../ship.h"

void
create_room()
{
    set_short("Leaving the Rift of Sybarus");
    set_long("The ship has cleared the narrow channel of water " +
             "running into the Rift of Sybarus behind you.  A "+
             "series of " +
             "islands can be seen off the starboard side, and " +
             "craggy mountain peaks are visible just beyond.  " +
             "Ahead are the boundless depths of the sea.\n"); 

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    AI(({"island","islands"}),
       "The islands are covered in greenery, they look quite pleasant.\n");
    AI(({"fissure", "rift"}),
       "It looks like a huge, deep crack into the mountain.\n"); 
    AI(({"mountain", "mountains"}), 
       "The mountains are craggy and snow-capped, they form a ring"+
       " of sorts around the islands.\n");
   
}  
