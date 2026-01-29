/* Flowchart for the Dragon highlord Kitiara.

EVENTS                       PERIOD following event
--------------------------------------------------------
attack on vkeep              run attack on vkeep
return home unsuccessfully   wait till next attack
flee home                    wait till next attack
return home victoriously     wait till next attack
patrol vkeep                 short wait till next attack
kitiara died                 wait till next attack

PERIOD                       Default EVENT following period          List of PERIODS which could follow after an INTERRUPT
--------------------------------------------------------------------------------------------------------------------------
run attack on vkeep          return home unsuccessfully              kitiara died,flee home,return home victoriously
wait till next attack        attack on vkeep                         kitiara died,attack on vkeep,patrol vkeep
short wait till next attack  attack on vkeep                         kitiara died,attack on vkeep,patrol vkeep

INTERRUPTS                   EVENT triggered by interrupt   
-------------------------------------------------------------
solve disk quest             patrol vkeep
capture gunthar              return home victoriously
all troops dead              flee home

 */

#include "/d/Krynn/common/defs.h"
#include TIME_FLOW
#define   DEBUG(x)    find_living("boron")->catch_msg(x)
#define  KIT_FILE   "/d/Krynn/solamn/splains/living/highlord"
#define  LAIR       "/d/Krynn/solamn/splains/room/lair"

object kit;

/* This is the actual flowchart. It's a bipartite graph consisting of
 * events and periods. It should be complete!
 */
void
create_flow()
{
    ADD_EVENT("attack on vkeep","run attack on vkeep", "start_attack");
    ADD_PERIOD("run attack on vkeep", 30000,
	       "return home unsuccessfully", ({"flee home","kitiara died"}));
    ADD_EVENT("return home unsuccessfully","wait till next attack",
	      "flee_home");
    ADD_EVENT("flee home","wait till next attack","flee_home");
    ADD_EVENT("return home victoriously","wait till next attack","return_home");
    ADD_PERIOD("wait till next attack", ({226800,432000}),
	       "attack on vkeep",
	       ({"kitiara died","attack on vkeep","patrol vkeep"}));
    ADD_EVENT("patrol vkeep","short wait till next attack","patrol_keep");
    ADD_PERIOD("short wait till next attack", ({22680,43200}),
	       "attack on vkeep",
	       ({"kitiara died","attack on vkeep","patrol vkeep"}));
    ADD_EVENT("kitiara died","wait till next attack","resurrect_me");
    INIT_THIS_THREAD("kitiara died");    
}

/* Below follow the actual functions that perform the actions on the npc.
 * Note: Usually, a way to get access to the npc object is necessary to
 *       make these functions work.
 */

/* Access functions to the npc! Ideally, the npc should be cloned from 
 * this object and then moved to the correct place in Krynn via an event.
 */

/* This function reinstalls Kitiara to where she was before armie */
void
reboot_setup()
{
    string current = CURRENT_PERIOD("kitiara");

    seteuid(getuid(TO));
    (LAIR)->load_me();
    kit = clone_object(KIT_FILE);
    /*if (current == "wait till next attack" ||
      current == "short wait till next attack")*/
    kit->move_living("xxx",LAIR);
    /*else if (current == "run attack on vkeep")
     *kit->move_living("xxx",LAIR);
     */
    
}

void
set_kitiara(object who)
{
    kit = who;
}

object
get_kitiara()
{
    return kit;
}

void
interrupt_on_death()
{
    INTERRUPT_PERIOD("kitiara","kitiara died");
}

void
short_delay_till_next_attack()
{
    INTERRUPT_PERIOD("kitiara","patrol vkeep");
}

/* Below follow the events */
void
start_attack()
{
    if (!kit || !kit->my_strategy())
      {
	  set_alarm(1.0,0.0,"short_delay_till_next_attack");
	  return;
      }
    DEBUG("*TIME* Kitiara starts attack on vkeep.\n");
}

void
flee_home()
{
    if (!kit)
      {
	  set_alarm(1.0,0.0,"interrupt_on_death");
	  return;
      }
    DEBUG("*TIME* Kitiara flees home.\n");
    kit->flee_troops_gone();
}

void
return_home()
{
    if (!kit)
      {
	  set_alarm(1.0,0.0,"interrupt_on_death");
	  return;
      }
    DEBUG("*TIME* Kitiara returns home victoriously.\n");
    kit->flee_troops_gone(); /* same as fleeing, but we have captured Gunthar ;-) */
}

void
resurrect_me()
{
    if (kit)
      return;
    DEBUG("*TIME* Resurrecting Kitiara.\n");
    seteuid(getuid(TO));
    kit = clone_object(KIT_FILE);
    (LAIR)->load_me();
    kit->move_living("xxx",LAIR);
}

patrol_keep()
{
    if (!kit)
      {
	  set_alarm(1.0,0.0,"interrupt_on_death");
	  return;
      }
    DEBUG("*TIME* Kitiara patrols vkeep.\n");
    kit->patrol_vkeep();
}
