inherit"/std/paralyze.c";
#include "defs.h"
#define ALLOWED ({ "bug", "commune", "help", "idea", "praise", "quit", "reply", "sysbug", "typo" })
#define MAX_CLAMS 5

object room;

void set_room(object x)
{
  room = x;
}
  
void
create_paralyze()
{
  set_name("dig_paralyze");
  ::create_paralyze();
  set_stop_verb("stop");
  set_stop_object(this_object());
  set_stop_fun("stop_paralyze");
  set_stop_message("You stop digging and rise.\n");
  set_fail_message("You are busy digging right now. You must " +
		   "'stop' to do something else.\n");
  set_remove_time(15);
}

int
stop(string str)
{
  object player = environment();

  /* Only paralyze our environment */
  if (player != this_player())
    {
      return 0;
    }
  
  /* Some commands may always be issued. */
  if (member_array(query_verb(), ALLOWED) != -1)
    {
      return 0;
    }
  
    /* If there is a verb stopping the paralyze, check it. */
  if (stringp(stop_verb) &&
      (query_verb() == stop_verb))
    {
      player->catch_msg("You stop digging and rise.\n");
      tell_room(room, QCTNAME(this_player()) + " stops digging " +
	  "and rises.\n", player);
      
      remove_object();
    
      return 1;
    }
  
  /* We allow VBFC, so here we may use catch_msg(). */
  if (stringp(fail_message))
    {
      player->catch_msg(fail_message);
    }
  /* Only paralyze mortals. */
  if (!player->query_wiz_level())
    {
      return 1;
    }
  
  write("Since you are a wizard this paralyze won't affect you.\n");
  return 0;
}

void
stop_paralyze()
{
  object player = environment();
  object clam;
  object hole;

  if (!objectp(environment()))
    {
      remove_object();
      return;
    }

  if (room->query_clams_dug() < MAX_CLAMS &&
      (random(3) + 1 > TIDE->query_tide_level()))
    {
      clam = clone_object(NPC_DIR + "clam.c");
      player->catch_msg("You find a " + clam->query_short() +
			" in the sand.\n");
      tell_room(room, QCTNAME(player) + " finds something in the sand.\n",
		player);
      player->catch_msg("You quickly pick it up.\n");
      tell_room(room, QCTNAME(player) +
		" quickly picks it up.\n", 
		player);
      if (clam->move(player) != 0)
	{
	  clam->move(room);
	  player->catch_msg("You cannot carry the clam. " +
			    "You drop it on the sand.\n");
	  tell_room(room, QCTNAME(player) + " drops a " +
		    clam->query_short() + ".\n", player);
	}
      room->set_clams_dug(room->query_clams_dug() + 1);
    }
  else
    {
      player->catch_msg("You cannot find a clam.\n");
    }

  hole = clone_object(OBJ_DIR + "hole.c");
  hole->move(room);
  player->catch_msg(stop_message); 

  remove_object();
}
