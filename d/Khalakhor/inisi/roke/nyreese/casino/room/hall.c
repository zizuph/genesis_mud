 /*
  * Great hall in the new Cadu Casino
  */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"
      
inherit "/std/room";
  
void
create_room()
{
    set_short("casino hall");
    set_long("You're standing in the great hall of the Cadu casino. "+
             "Grand stairs stand both to the northeast and southeast, " +
             "arching towards the center of the room into a big balcony.\n");

    // Have the manager here, greeting players and handling the quests

    add_exit(CASINO + "room/entrace", "west");
    add_exit(CASINO + "room/blackjack-room", "north");
    add_exit(CASINO + "room/roulette-room", "south");
    add_exit(CASINO + "room/stairs-n", "northeast"); 
    add_exit(CASINO + "room/stairs-s", "southeast");
    add_exit(CASINO + "room/cashier", "east");
}