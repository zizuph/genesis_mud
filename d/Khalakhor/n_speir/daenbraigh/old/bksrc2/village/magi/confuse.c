/*
 * confusion spell routine
 * TAPAKAH, 09/2005
 */

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "../../nspeir.h"
#include "../../village/village.h"
#include "/d/Khalakhor/sys/defs.h"

//inherit "/std/combat/cbase";

void confuse_spell(object enemy,
		   object performer);

void
confuse_spell(object enemy,
	      object performer)
{
  object *people;
  int who;
  string target;
  
  if(performer->query_mana() < CONFUSION_MANA)
    return;
  
  tell_room(ENV(performer),
	    "You see " + QCTNAME(performer) + "'s hands performing strange movements.\n",
	    performer);
  enemy->catch_tell("You feel hypnotized by the movements of" + QCTNAME(performer) + "'s hands.\n");
  if(random(enemy->query_magic_res(MAGIC_I_RES_ILLUSION) + enemy->query_stat(SS_WIS)) < RESIST_LEVEL) {
    people = performer->query_enemy(-1) & all_inventory(ENV(performer));
    enemy->catch_tell("You feel completely lost and surrounded by enemies!\n");
    tell_room(ENV(performer),
	      QCTNAME(enemy) + " looks around in total confusion.\n",
	      performer);
    who = random(sizeof(people));
    if(people[who] == enemy) {
      write("You feel panic creeping into you.\n");
      enemy->add_panic(CONFUSION_DAMAGE);
    }
    else {
      write("You think... Who, who am I fighting?\n");
      target = people[who]->query_the_name(enemy);
      enemy->command("$kill " + target);
      enemy->command("$kill " + target);
    }
  }
  else 
    enemy->catch_tell("You shake your head and regain your senses completely.\n");
}

     
