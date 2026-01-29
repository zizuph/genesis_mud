/*
 * confusion spell routine
 * TAPAKAH, 09/2005
 */

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Khalakhor/sys/defs.h"

#include "../../daenbraigh.h"
#include "../../village/village.h"
#include "magi.h"

void confuse_spell(object caster, object enemy);

void
confuse_spell(object caster, object enemy)
{
  object *people;
  int who;
  string target;
  
  if(caster->query_mana() < CONFUSION_MANA)
    return;
  
  tell_room(ENV(caster),
	    "You see " + QCTNAME(caster) + "'s hands performing strange "+
	    "movements.\n",
	    caster);
  enemy->catch_tell("You feel hypnotized by the movements of " +
		    QCTNAME(caster) + "'s hands.\n");
  if(random(enemy->query_magic_res(MAGIC_I_RES_ILLUSION) +
	    enemy->query_stat(SS_WIS)) < CONFUSION_RESIST_LEVEL) {
    people = caster->query_enemy(-1) & all_inventory(ENV(caster));
    enemy->catch_tell("You feel completely lost and surrounded by enemies!\n");
    tell_room(ENV(caster),
	      QCTNAME(enemy) + " looks around in total confusion.\n",
	      caster);
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
    enemy->catch_tell("You shake your head and regain your senses "+
		      "completely.\n");
}

     
