#pragma save_binary

inherit "/d/Genesis/ship/ship";

#include "/d/Roke/common/defs.h"
#include <macros.h>

check_captain();
object cap;

void
create_ship()
{
    if (!IS_CLONE) return;

  seteuid(getuid());
  set_cabin(SHIPS+"gontsparkle/cabin");
  set_deck(SHIPS+"gontsparkle/deck");
  cap=clone_object(SHIPS+"gontsparkle/captain");
  set_captain(cap);
  set_places_to_go(({REDIR+"b2",
		       SHIPS+"gontsparkle/sea1",
		       SHIPS+"gontsparkle/sea2",
		       SHIPS+"gontsparkle/sea3",
		       SHIPS+"gontsparkle/sea4",
		       SHIPS+"gontsparkle/sea5",
		       SHIPS+"gontsparkle/sea6",
		       SHIPS+"gontsparkle/sea7",
		       SHIPS+"gontsparkle/sea8",
		       "/d/Genesis/start/human/town/pier1",
		       SHIPS+"gontsparkle/sea8",
		       SHIPS+"gontsparkle/sea7",
		       SHIPS+"gontsparkle/sea6",
		       SHIPS+"gontsparkle/sea5",
		       SHIPS+"gontsparkle/sea4",
		       SHIPS+"gontsparkle/sea3",
		       SHIPS+"gontsparkle/sea2",
		       SHIPS+"gontsparkle/sea1"}));
  set_time_between_stops(({24,3,3,3,3,3,3,3,3,
			     24,3,3,3,3,3,3,3,3}));
  set_ticket_id("GontSparkle"); 
  set_name("ship");
  add_name("boat");
  add_name("warship");
  add_adj("huge");
  set_long("A huge warship that travels between Sparkle and Gont to\n"+
	   "protect the waters from the fierce warriors from Nor-at-hur.\n");


/*
  set_alarm(600.0, 0.0, check_captain);
*/

}
check_captain()
{
  if(!cap)
    {
      cap = clone_object(SHIPS + "gontsparkle/captain");
      set_captain(cap);
      cap->move_living("X",E(TO));
    }

  set_alarm(600.0, 0.0, check_captain);

}
enter_env(object dest,object from)
{
  object *obs;
  int i;

  ::enter_env(dest,from);

  if(!(dest->query_prop(ROOM_I_TYPE)==1))
    return;

  obs = all_inventory(dest);

  for(i=0;i<sizeof(obs);i++)
    {
      if(living(obs[i]))
	{
	  obs[i]->catch_msg("Krell pulls you out of the sea.\n");
	  tell_room(SHIPS+"gontsparkle/deck","Krell rescues "+QCTNAME(obs[i])+".\n");
	  obs[i]->move_living("M",SHIPS+"gontsparkle/deck");
	}
      else
	if(obs[i]!=TO)
	  {
	    if(member_array("ship",obs[i]->query_names())<0)
	      obs[i]->remove_object(); /* remove corpses */
	  }
    }
}
