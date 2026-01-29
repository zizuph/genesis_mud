
/* smaller fish for coral requiem */
/* Karath 01/97 */

inherit "/d/Emerald/std/emerald_creature";

#include "/d/Emerald/eclipsia/edefs.h"
#include <wa_types.h>

void
create_emerald_creature()
{
   string *adjs, *species;

   int h, i;

   add_prop(LIVE_I_NEVERKNOWN, 1);

   add_prop(MAGIC_I_BREATH_WATER, 1);

   adjs = ( ({ "long", "sleek", "tiny", "lazy", "quick",
	       "fat", "bloated", "small", "large" }) );

   species = ( ({ "smelt", "clownfish", "tang", "parrotfish",
		"damsel"}) );
   h = random(sizeof(adjs));
   i = random(sizeof(species));

   set_gender(2);

   set_long("	This "+species[i]+" is one of the smaller fish of "+
	"these waters. It spends most of it's time grabbing bits "+
	"of food floating in the water while trying to avoid "+
	"food itself. It eyes you carefully, not knowing "+
	"whether or not you are a danger.\n");

   add_adj(adjs[h]);
   set_race_name(species[i]);
   add_name("_eclipsia_small_fish_");
   add_name("fish");

   add_prop("_coral_requiem_npc_", 1);
   add_prop(MAGIC_I_BREATH_WATER, 1);

   set_skill(SS_DEFENCE, 5 + random(10));
   set_skill(SS_SWIM, 100);
   set_skill(SS_BLIND_COMBAT, 30);
   set_skill(SS_AWARENESS, 20 + random(15));

   set_stats( ({ 2, 6, 5, 2, 2, 5 }) );
   
   set_hitloc_unarmed(1, 5, 100, "body");

   set_attack_unarmed(1, 5, 5, W_IMPALE, 100, "bite");

   set_random_move(5);

   set_act_time(6);

   add_act("emote darts around searching for bits of food.");
   add_act("emote brushes against you, then darts away.");

   set_cact_time(3);  

   add_cact("emote darts furiously around, looking for an escape.");
   add_cact("emote bumps against you and tries to bounce away.");
}
