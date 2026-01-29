inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
/* by mhyrkhaan */

void
create_monster()
{
   ::create_monster();
   set_name("dezzin");
   add_name("rider");
   set_race_name("dark-elf");
   set_adj("lean");
   add_adj("shadowy");
   set_long("This is the founder and store owner of the Dark Alliance. He looks lean and powerfull "+
   "and very compitent at his abilities.\n");
   set_stats(({150,150,150,150,150,200}));
   set_title("Dra'keth, Founder of the Dark Alliance");
   set_skill(SS_WEP_SWORD,50);
   set_skill(SS_DEFENCE,90);
   set_skill(SS_PARRY,90);
   add_prop(LIVE_I_SEE_DARK,5);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   add_prop(CONT_I_WEIGHT,10000);
   add_prop(CONT_I_VOLUME,1000);
   set_act_time(10);
   add_act("emote practices a sword attack.");
   add_act("emote spits on the ground in hatred of all humans.");
   add_act("say This is not just a guild, this is a family, if one of our "+
   "brothers or sisters should fall in battle, their death must be avenged!");
   set_act_time(5);
   add_act("say I used to love braveing the Forest of Shadows, and "+
   "killing all the human scum in Drakmere...man those days where fun.");
   add_act("say You must remember, a true Rider has both the ability, and "+
   "the disipline to control their warwolf in combat.");
   add_act("say I think my thanar count is up to 120, god I love killing "+
   "those damned human bastards.");
}