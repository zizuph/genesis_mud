/* created by Aridor 04/19/94 
 *
 * 
 * Carnak September 2016, Altered the code to allow for the scale-plated chain
 *                        mail to spawn on this aurak by removing reduntant
 *                        arming functions.
 */ 
#include "/d/Krynn/common/defs.h"
#include <money.h>
#include <ss_types.h>

inherit "/d/Krynn/std/aurak";
inherit AUTO_TEAM

void
create_aurak()
{
   set_pick_up_team(({"aurak","sivak","bozak","kapak"}));
   set_max_team_size_auto_join(6);
   
   set_stats(({140,140,200,160,160,140}));

   int i = 30 + random(40);

   set_skill(SS_DEFENCE,     i);
   set_skill(SS_PARRY,       i);
   set_skill(SS_WEP_SWORD,   i);  
   set_skill(SS_2H_COMBAT,   i);
   set_skill(SS_WEP_KNIFE,   i);
   set_skill(SS_WEP_CLUB,    i);
   set_skill(SS_WEP_POLEARM, i);
   set_skill(SS_WEP_AXE,     i);
   set_skill(SS_AWARENESS, 100);
   
   set_all_hitloc_unarmed(20);
   
   set_act_time(3);
   add_act("emote looks at you suspiciously.");
   add_act("emote snarls: What have we here?");
   add_act("emote hisses: How did you find us?");
   
   set_cact_time(10);
   add_cact("shout DIE THEN SCUM!");
   add_cact("shout Soldiers! To me!");
   
   set_color("blue");
}


void
init_living()
{
   init_team_pickup();
   ::init_living();
}