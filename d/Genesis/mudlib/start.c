/*
* /d/Genesis/mudlib/start.c
*
* This is the temporary start location for all mortal players while the game
* is out of order during the introduction of the new mudlib.
*
* /Mercade, May 16 1996
*/

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

void
create_room()
{
   set_short("the temporary start room");
   set_long("While the new mudlib is being installed most of the rooms " +
      "are tested to see whether they function properly, we have " +
      "to offer you only a very limited playground that will enable " +
      "to stay in touch with your friends. Go \"post\" to go to the " +
      "post office, \"common\" to read the common board or " +
      "\"private\" to enter a room with some private booth'. Go " +
      "\"board\" to enter the room that contains the board that is " +
      "normally found in the lobby of the Tower or Realms.\n");
   
   add_prop(ROOM_I_INSIDE,          1);
   add_prop(ROOM_I_NO_ATTACK,       1);
   add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
   add_prop(ROOM_M_NO_TELEPORT, 1);
   
   add_exit("/d/Genesis/mudlib/post"   , "post");
   add_exit("/d/Genesis/mudlib/common" , "common");
   add_exit("/d/Genesis/mudlib/private", "private");
   add_exit("/d/Genesis/mudlib/lobby",   "board");
}
