/*
* /d/Genesis/mudlib/private.c
*
* From this room, players may enter various booth' for private conversation.
*
* /Mercade, May 16 1996
*/

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

#define BOOTH "/d/Genesis/mudlib/booth_"
#define SIZE  (10)
#define SCREENWIDTH (77)

#define PLAYER_AI_ALLOWED "_player_ai_allowed"

void
create_room()
{
   int index;
   
   set_short("the temporary private booth corridor");
   set_long("From this corridor you can enter either of " + SIZE +
      " private booth'. Since only a few rooms are open to players, " +
      "it is not possible to go far away to talk quietly. Therefore " +
      "these booth' have been created for you to talk with your " +
      "friends without being disturbed all the time.\n" +
      "With the command \"enter booth <num>\" you will be able to " +
      "enter a booth that is free. If there are already people in " +
      "the booth, you will have to \"ring booth <num>\" first to " +
      "call the attention of those in the booth already.\n");
   
   add_item( ({ "booth" }), "@@booth_description@@");
   
   add_prop(ROOM_I_INSIDE,          1);
   add_prop(ROOM_I_NO_ATTACK,       1);
   add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
   add_prop(ROOM_M_NO_TELEPORT, 1);
   
   add_exit("/d/Genesis/mudlib/start", "lobby");
   
   index = (SIZE + 1);
   while(--index > 0)
   {
      (BOOTH + index)->teleledningsanka();
   }
}

string
print_tabulated(string to_print)
{
   string *tmp;
   
   if (strlen(to_print) <= SCREENWIDTH)
      {
      return (to_print + "\n");
   }
   
   tmp = explode(break_string(to_print, SCREENWIDTH), "\n");
   return (implode( ({ tmp[0] }) +
         (explode(break_string(implode(tmp[1..], " "),
                  (SCREENWIDTH - (12))), "\n")), ("\n          ")) + "\n");
}

string
booth_description()
{
   int index = 0;
   string str = "";
   object *oblist;
   
   while(++index <= SIZE)
   {
      oblist = FILTER_PLAYERS(all_inventory(find_object(BOOTH + index)));
      str += print_tabulated(sprintf("Booth %2d: %s", index,
            (sizeof(oblist) ?
               COMPOSITE_LIVE(oblist) : "Empty")));
   }
   
   return str;
}

int
enter(string str)
{
   int booth;
   object *oblist;
   int *allowed;
   
   if (!stringp(str))
      {
      notify_fail("Enter which booth?\n");
      return 0;
   }
   
   if (sscanf(str, "booth %d", booth) != 1)
      {
      notify_fail("Enter which booth?\n");
      return 0;
   }
   
   if ((booth < 1) ||
         (booth > SIZE))
   {
      notify_fail("There is no booth number " + booth + ".\n");
      return 0;
   }
   
   oblist = all_inventory(find_object(BOOTH + booth));
   oblist = FILTER_PLAYERS(oblist);
   if (sizeof(oblist) &&
         !this_player()->query_wiz_level())
   {
      allowed = this_player()->query_prop(PLAYER_AI_ALLOWED);
      if (!pointerp(allowed) ||
            (member_array(booth, allowed) == -1))
      {
         notify_fail("You have not been invited to booth number " +
               booth + ".\n");
         return 0;
       }
      
      allowed -= ({ booth });
      this_player()->add_prop(PLAYER_AI_ALLOWED);
   }
   
   say(QCTNAME(this_player()) + " leaves for booth " + booth + ".\n");
   this_player()->move_living("M", (BOOTH + booth), 1);
   say(QCTNAME(this_player()) + " enters the booth.\n");
   
   return 1;
}

int
ring(string str)
{
   int booth;
   object *oblist;
   int *allowed;
   
   if (this_player()->query_wiz_level())
      {
      notify_fail("Wizards can always enter the booth'. No need to ring.\n");
      return 0;
   }
   
   if (!stringp(str))
      {
      notify_fail("Ring which booth?\n");
      return 0;
   }
   
   if (sscanf(str, "booth %d", booth) != 1)
      {
      notify_fail("Ring which booth?\n");
      return 0;
   }
   
   if ((booth < 1) ||
         (booth > SIZE))
   {
      notify_fail("There is no booth number " + booth + ".\n");
      return 0;
   }
   
   allowed = this_player()->query_prop(PLAYER_AI_ALLOWED);
   if (pointerp(allowed) &&
         (member_array(booth, allowed) != -1))
   {
      notify_fail("You have already been invited to booth number " +
            booth + ".\n");
      return 0;
   }
   
   oblist = all_inventory(find_object(BOOTH + booth));
   oblist = FILTER_PLAYERS(oblist);
   if (!sizeof(oblist))
      {
      notify_fail("There is no one in booth number " + booth + ".\n");
      return 0;
   }
   
   say(QCTNAME(this_player()) + " ring the bell for booth number " +
      booth + ".\n");
   oblist->catch_msg("\n" + QCTNAME(this_player()) +
      " rings the bell to be admitted to the booth.\n\n");
   write("You ring the bell on booth number " + booth + ".\n");
   
   return 1;
}

void
init()
{
   ::init();
   
   add_action(enter, "enter");
   add_action(ring , "ring");
}

void
allow(string name, int booth)
{
   object player = find_player(name);
   int *allowed = player->query_prop(PLAYER_AI_ALLOWED);
   
   if (!pointerp(allowed))
      {
      allowed = ({ booth });
   }
   else
      {
      allowed += ({ booth });
   }
   
   player->add_prop(PLAYER_AI_ALLOWED, allowed);
}
