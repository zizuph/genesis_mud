/* villager (herman) */
inherit "/std/monster";
#include <macros.h>

#include "/sys/ss_types.h"
create_monster()
{
  set_living_name("herman");
  set_name(({"villager","herman"}));
  set_race_name("human");
  set_short("poor villager");
  set_long("The villerager looks very say and seems to be in deep sorrow.\n");
  set_adj("sad");
  set_stats(({20,34,65,17,20,30}));
  set_alignment(150);

  set_act_time(15);
  add_act(({"say Why won't anyone rescue our princess?",
  "say Are you brave enough to rescue our princess?","cry","grovel all",
  "say A creature came and took our princess away!!!",
  "say Our brave men tried to kill the creature but never returned!!",
  "say I alone remain on this island.","say I can't give up hope for her.",
  "say Please help her!!!"}));

  set_cact_time(15);
  add_cact(({"scream","say Nooooo!","shout Why?! Why??!!"}));
  set_skill(SS_DEFENCE,0);
  set_skill(SS_PARRY,50);
}
