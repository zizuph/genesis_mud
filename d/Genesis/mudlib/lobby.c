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
   set_short("the lobby board room");
   set_long("The board in this room is the board that is normally found in " +
      "the lobby of the Tower or Realms. You can use it to discuss almost " +
      "any topic, but profane language or insults are not accepted. Also, " +
      "please refrain from guild-wars and personal attacks on this board. " +
      "This is the only board you can post on while the mud is down, so " +
       "treat it with some respect.\n");
   
   add_prop(ROOM_I_INSIDE,          1);
   add_prop(ROOM_I_NO_ATTACK,       1);
   add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
   add_prop(ROOM_M_NO_TELEPORT, 1);
   
   add_exit("/d/Genesis/mudlib/start", "lobby");
   
   setuid();
   seteuid(getuid());
   
   clone_object("/d/Genesis/mudlib/board")->move(this_object(), 1);
}
