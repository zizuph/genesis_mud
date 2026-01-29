inherit "/std/room";

#include "../ship.h"

void
create_room()
{
    set_short("Approaching the Rift of Sybarus");
    set_long("The ship is nearing the narrow channel of water " +
             "running into the Rift of Sybarus ahead.  A series of " +
             "islands can be seen off the starboard side, and " +
             "craggy mountain peaks are visible just beyond.  " +
             "Behind you are the boundless depths of the sea.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    AI(({"island","islands"}),
       "The islands are covered in greenery, they look quite pleasant.\n");
    AI("fissure", 
       "It looks like an a huge, deep crack into the mountain.\n"); 
    AI(({"mountain", "mountains"}), 
       "The mountains are craggy and snow-capped.\n");
   
}  
