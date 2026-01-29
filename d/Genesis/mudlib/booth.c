/*
* /d/Genesis/mudlib/booth.c
*
* The private booth'.
*
* /Mercade, May 16 1996
*/

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#define CORRIDOR "/d/Genesis/mudlib/private"

void
create_room()
{
   int index;
   
   set_short("the temporary private booth number " +
      this_object()->query_booth());
   set_long("This is booth number " + this_object()->query_booth() +
      " and you can use it to talk quietly with your friends. When " +
      "someone rings the bell, you can \"allow <name>\" to allow " +
      "that person to enter the booth.\n");
   
   add_prop(ROOM_I_INSIDE,          1);
   add_prop(ROOM_I_NO_ATTACK,       1);
   add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
   add_prop(ROOM_M_NO_TELEPORT,1);

   add_exit("/d/Genesis/mudlib/private", "out");
}

int
allow(string str)
{
   object player;
   
   if (!stringp(str))
      {
      notify_fail("Allow whom to the booth?\n");
      return 0;
   }
   
   str = lower_case(str);
   player = find_player(str);
   if (!objectp(player))
      {
      notify_fail("Player " + capitalize(str) + " is not in the game.\n");
      return 0;
   }
   
   if (player->query_wiz_level())
      {
      notify_fail("There is no reason to allow a wizard.\n");
      return 0;
   }
   
   say(QCTNAME(this_player()) + " allows " + QTNAME(player) +
      " to enter the booth.\n");
   tell_object(player, ("\n" + this_player()->query_The_name(player) +
         " allowed you to enter booth number " +
         this_object()->query_booth() + ".\n\n"));
   write("You allow " + capitalize(str) + " to enter the booth.\n");
   
   CORRIDOR->allow(str, this_object()->query_booth());
   
   return 1;
}

void
init()
{
   ::init();
   
   add_action(allow, "allow");
}
