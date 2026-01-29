inherit "/std/monster";
inherit "/std/combat/unarmed";

#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include "../edefs.h"
#include <tasks.h>

#define SPECIAL_RATIO	5

void test_vbfc();


void
create_monster()
{
   set_race_name("kraken");
   add_name("dragon");
   set_long("This ancient beast has lived in the dark waters of Emerald " +
	    "for eons. A distant realtive to the dragons it is, but the " +
	    "only resemblance appart from size is it's cold eyes gleaming " +
	    "with malice.\n");
   set_stats(({ 150, 50, 300, 50, 50, 150 }));
   set_hitloc_unarmed(1, 95, 50, "tentacle");
   set_hitloc_unarmed(2, 10, 3, "head");
   set_hitloc_unarmed(3, 60, 35, "side");
   set_hitloc_unarmed(4, 1, 2, "unprotected spot");
   set_hitloc_unarmed(5, 70, 10, "back");    
   
   set_attack_unarmed(1, 100, 40, W_BLUDGEON, 50, "nimble tentacle");
   set_attack_unarmed(2, 70, 100, W_BLUDGEON,  10, "huge tentacle");
   set_attack_unarmed(4, 80, 80, W_BLUDGEON, 10, "massive tentacle");
   set_attack_unarmed(8, 75, 50, W_BLUDGEON, 10, "gnarled tentacle");
   set_attack_unarmed(16, 100, 30, W_BLUDGEON, 10, "swift tentacle");
   set_attack_unarmed(32, 65, 60, W_BLUDGEON, 5, "really long tentacle");
   set_attack_unarmed(64, 35, 70, W_BLUDGEON, 5, "slimy tentacle");
   
   set_cact_time(2);
   add_cact("snarl");
   add_cact("snear");
   add_cact("glare maliciously");
   set_chat_time(1);
   add_act("@@test_vbfc");
}

void
test_vbfc()
{
    tell_room(ENV(TO), "The kraken lets out a shrill shrike that freeze you " +
	      "to the bone.\n");
}

do_die(object killer)
{
    tell_room(ENV(TO), "The " + short() + " lets out a final shrike of " +
	      "before it slumps to the ground and all is very still.\n");
    tell_room(TO, "There is a terrible shrike of agony and a heavy thud, " +
	      "before everything gets very still.\n");
    ::do_die(killer);
}
    
int
special_attack(object victim)
{
    object *enemies;
    int target;
    
    if (random(SPECIAL_RATIO))
	return 0;
    tell_room(ENV(TO), "The " + short() + " catch someone with a " +
	      "tentacle.\n");
    enemies = query_enemy(-1);
    target = member_array("magic", map(enemies, &->query_guild_style_occ()));
    if (target < 0)
	target = random(sizeof(enemies));
    if (TO->resolve_task(TASK_DIFFICULT, ({ TS_DEX }),
			 enemies[target], ({ TS_DEX, SS_DEFENCE })) < 0)
	{
	    write("You try to catch " + enemies[target]->query_name() +
		  "but miss.\n");
	    tell_object(enemies[target], "The " + short() + " tries to " +
			"grab you with one of " + TO->query_possessive() +
			" tentacles, but you deftly avoid being caught.\n");
	    tell_room(ENV(TO), "The " + short() + " tries to grab " +
		      QCNAME(enemies[target]) + " with one of " +
		      TO->query_possessive() + " tentacles, but " +
		      QCNAME(enemies[target]) + " deftly avoid beeing " +
		      "caugt.\n");
	    return 1;
	}
    tell_room(ENV(TO), QCTNAME(enemies[target]) + " is caught!\n");
    return 1;
}

