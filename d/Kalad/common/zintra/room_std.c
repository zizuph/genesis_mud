//
//   This will be a standard room to be inherited by all rooms
//   dealing with the BlackHands Assassins Guild.
//				
//					~Rico  10.04.96
//

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"
/*
#include "/d/Kalad/common/zintra/defs.h"
*/
#include <stdproperties.h>

create_room()
{
   ::create_room();

   add_prop(ROOM_I_INSIDE, 1);
}
