/*
* /d/Genesis/mudlib/common.c
*
* This is the common board room. You will find the common board here.
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
   set_short("the temporary common board room");
   set_long("In this room the common board can be found. It contains " +
      "important announcements from the administration and on it " +
      "you will also find information with respect to the new " +
      "mudlib, like which changes there are that affect you and " +
      "when this probably will be over.\n");
   
   add_prop(ROOM_I_INSIDE,          1);
   add_prop(ROOM_I_NO_ATTACK,       1);
   add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
   add_prop(ROOM_M_NO_TELEPORT, 1);
   
   add_exit("/d/Genesis/mudlib/start", "lobby");
   
   setuid();
   seteuid(getuid());
   
   clone_object("/d/Genesis/obj/board")->move(this_object(), 1);
}
