/*
 * /d/Kalad/common/guilds/sh_walkers/std/room_std.c
 * Created By : Rico 23.05.96
 * First Modif:
 */

#include "../defs.h"

inherit "/std/room.c";

void
create_room()
{
   set_short("\nShadow Walker standard room");
   set_long ("\n"+
      "This is the room which should be inherited by all other "+
      "rooms having to do with the Shadow Walkers of Kabal.  "+
      "There will be few exceptions.\n\n");

   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_HIDE, 0); /* Easy to hide around */
}

