/*  Standard guard patrol code in Gelan, inherited by some guards.

    coder(s):   Maniac

    history:   16.9.94          Created                          Maniac    

    purpose:   Guards will move around, patrolling, instead of being 
               static.  Inherits stdguard, and is inherited directly
               by apprentice_fighter, fighter and exp_fighter. 

    quests:     none

    to do:      none
    bug:        none known
*/

#include "specials.h"
#include <filter_funs.h>
#include <macros.h>

inherit STD_GUARD;

void
patrol()
{
  set_alarm(0.5, 0.0, "guard_step");
  set_alarm(itof(25 + random(10)), 0.0, "guard_react");
  set_alarm(itof(55 + random(10)), 0.0, "guard_step");
  set_alarm(itof(85 + random(10)), 0.0, "guard_react");
  set_alarm(itof(115 + random(10)), 0.0, "guard_step");
  set_alarm(itof(145 + random(10)), 0.0, "guard_react");
}



void
bad_react(string name)
{
  if (random(4)) return;

  if (random(2))
    command("scowl " + name);
  else
    command("glare " + name);
}


void
good_react(string name)
{
  if (random(4)) return;
 
  if (random(2))
    command("nod happily " + name);
  else
    command("smile " + name);
}


/* aimless wandering really, this can be improved */
void
guard_step()
{
  mixed exit;
  int i;
  
  exit = environment(this_object())->query_exit();
  i = (random(sizeof(exit) / 3));
  i = (i * 3) + 1;

  command(exit[i]);    
 
}



/* react to one of the livings in this room (if any) */
void
guard_react()
{
  object *pls;  
  int i;

  pls = FILTER_PLAYERS(all_inventory(environment(this_object())));

  if (!sizeof(pls))
    return;
  
  i = random(sizeof(pls));
  if (pls[i]->query_alignment() < 0) 
    bad_react(pls[i]->query_real_name());
  else
    good_react(pls[i]->query_real_name());
   
}


void
stop_patrol()
{
  mixed *al;
  int i;

  al = get_all_alarms();
  for (i = 0; i < sizeof(al); i++)  {
    if ((al[i][1] == "patrol") || 
        (al[i][1] == "guard_react") ||
        (al[i][1] == "guard_step"))
      remove_alarm(al[i][0]);
  }
  
}


void
start_patrol()
{
  stop_patrol();
  set_alarm(1.0, 181.0, "patrol");
}




/*
 * Function name: attacked_by
 * Description:   Masked, stop patrolling when attacked. 
         
 * Arguments:     attacker
 * Returns:       none
 */

void
attacked_by(object attacker)
{
    stop_patrol();
    ::attacked_by(attacker);
}


/*
 * Function name: help_other
 * Description:   react on a help call from the head guard, that means
                  here: go to the indicated room and attack the attacker
                  there. Stop patrolling before doing so.
 * Arguments:     destination room, attacker
 * Returns:       none
 */

void
help_other(int meeting, string room, object attacker)
{
  stop_patrol();
  ::help_other(meeting, room, attacker); 
}



/* Called when the enemy left the room. Guard returns to 
 * his/her post, then starts patrolling again.
 */
void
notify_enemy_gone(object attacked)
{
  ::notify_enemy_gone(attacked);
  start_patrol(); 
}



