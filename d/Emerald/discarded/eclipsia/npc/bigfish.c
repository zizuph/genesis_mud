
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

   species = ( ({ "barracuda", "moray eel", "lionfish", "anglerfish" }) );
   h = random(sizeof(adjs));
   i = random(sizeof(species));

   set_gender(2);

   add_adj(adjs[h]);
   set_race_name(species[i]);
   add_name("_eclipsia_large_fish_");
   add_name("fish");

   set_long("	This "+species[i]+" is one of the larger fish in these "+
	"waters. It preys on the smaller fish around here. It's "+
	"slowly swimming back and forth...eyeing every living thing "+
	"in the area as possible food...including you!.\n");

   add_prop("_coral_requiem_npc_", 1);
   add_prop(MAGIC_I_BREATH_WATER, 1);

   set_skill(SS_DEFENCE, 15 + random(10));
   set_skill(SS_SWIM, 100);
   set_skill(SS_BLIND_COMBAT, 30);
   set_skill(SS_AWARENESS, 30 + random(15));

   set_stats( ({ 30, 60, 50, 5, 5, 50 }) );
   
   set_hitloc_unarmed(1, 10, 75, "body");
   set_hitloc_unarmed(1, 10, 25, "head");

   set_attack_unarmed(1, 25, 25, W_IMPALE, 100, "bite");

   set_random_move(5);

   set_act_time(6);

   add_act("emote slowly swims around looking for smaller prey.");
   add_act("emote brushes against you, then swims away, apparantly "+
	"deciding you were too big to kill.");
   add_act("kill _eclipsia_small_fish_");

   set_cact_time(3);  

   add_cact("emote swims furiously around, trying to get an opening.");
   add_cact("emote opens it's jaws wide and charges in again.");
}
