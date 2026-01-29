/*
 * confusion spell routine
 * TAPAKAH, 09/2005
 */

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

#include "/d/Khalakhor/sys/defs.h"

#include "../../daenbraigh.h"
#include "../../village/village.h"
#include "magi.h"

void cold_spell(object caster, object enemy);

void
cold_spell(object caster, object enemy)
{
  int damage;
  if(caster->query_mana() < COLD_MANA)
    return;

  caster->tell_watcher("You see a icy ray striking from the elder.\n",enemy);
  enemy->catch_tell("You see an icy ray striking from the elder towards "+
		    "you.\n");
  if(random(enemy->query_magic_res(MAGIC_I_RES_DEATH) +
	    enemy->query_stat(SS_WIS)) < COLD_RESIST_LEVEL) {
    damage = COLD_DAMAGE_BASE + random(COLD_DAMAGE_EXTRA);
    if(enemy->query_race() == "elf" ||
       enemy->query_race() == "human")
      damage += random(COLD_DAMAGE_BASE);
    enemy->hit_me(damage,MAGIC_DT,TO,-1);
    enemy->catch_tell("You feel the ice piercing your body causing an "+
		      "extreme pain.\n");
    if(enemy->query_hp() <= 0)
      enemy->do_die(TO);
  }
  else
    caster->tell_watcher("The icy ray dissolves in the air.\n",enemy);
  caster->add_mana(-1*COLD_MANA);
}
