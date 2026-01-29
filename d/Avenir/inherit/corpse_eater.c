// -*-C++-*-
// corpse_eater.c
// Made by Boriska@Genesis, May 1994. 
// This monster while fighting scans its environment for corpses
// and corpses for leftovers. Upon finding one it tears leftover
// off corpse and stops fighting for some time.
// Good for hungry and stupid monsters like ogres etc

inherit "/std/monster";

#include </sys/macros.h>

/* delays in seconds */
#define SCAN_DELAY 10.0     
#define ATTACK_DELAY 15.0 

void stop_corpse_scan(); 

static int scan_id = 0;  
static object to = this_object();

void
create_monster()
{
  set_name("eater");
  set_short ("corpse eater");
  set_long("Corpse eater\n");
  default_config_npc(20);
}

void
attack_object (object ob)
{
  ::attack_object(ob);
  if ( !scan_id)
    scan_id = set_alarm (SCAN_DELAY, SCAN_DELAY, "corpse_scan");
}

  // Start looking for corpses upon being attacked
void
attacked_by (object ob)
{
  ::attacked_by (ob);
  if ( !scan_id)
    scan_id = set_alarm (SCAN_DELAY, SCAN_DELAY, "corpse_scan");
}

 // called by set_alarm
void
corpse_scan()
{
  object *corpses;
  mixed leftovers;
  string organ;
  int i;
  
  if (query_attack())
    {
      // look for corpses in environment
      corpses = filter(all_inventory(environment()), "is_corpse",
		       this_object());

      // look for leftovers in corpses
      for ( i=0; i< sizeof(corpses); i++ )
	{
	  leftovers = corpses[i]->query_leftover();
	  if ( sizeof(leftovers) > 0 )
	    {
	      organ = leftovers[0][1];
	      corpses[i]->remove_leftover (organ);
	      stop_corpse_scan();
	      add_stun();
	      // the prop will be removed after ATTACK_DELAY sec
	      set_alarm (ATTACK_DELAY, 0.0, "resume_attack");
	      tell_room (environment(),"Ogre tears " +
			 "/sys/global/language"->add_article(organ) +
			 " from corpse and starts chewing on it!\n");
	      break;
	    }
	}
    }
  else
    stop_corpse_scan ();
}

stop_corpse_scan ()
{
  remove_alarm (scan_id);
  scan_id = 0;
}

 // used in filter
int
is_corpse (object ob)
{
  return ob->query_name() == "corpse" ;
}

void
resume_attack ()
{
  remove_stun();
  if (!scan_id)
    scan_id = set_alarm (SCAN_DELAY, SCAN_DELAY, "corpse_scan");
}



