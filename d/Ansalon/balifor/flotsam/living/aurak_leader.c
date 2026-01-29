/* created by Aridor 04/19/94
 *
 * 
 * Carnak September 2016, Altered the code to allow for the scale-plated chain
 *                        mail to spawn on this aurak by removing reduntant
 *                        arming functions.
 */
#include "/d/Krynn/common/defs.h"
#include <ss_types.h>

inherit "/d/Krynn/std/aurak";
inherit AUTO_TEAM

void
create_aurak()
{
   int i, j = random(4) + 5;
   /* j is the level of the draconian */
   string str;
   
   set_pick_up_team(({"aurak","sivak","bozak","kapak"}));
   set_max_team_size_auto_join(6);
   
   for(i=0; i<6; i++)
   set_base_stat(i, j * 12 + random(24) + 40);
   set_skill(SS_DEFENCE,     100);
   set_skill(SS_PARRY,       100);
   set_skill(SS_WEP_SWORD,   100);  
   set_skill(SS_2H_COMBAT,   100);
   set_skill(SS_WEP_KNIFE,   j * 4 + random(4) + 65);
   set_skill(SS_WEP_CLUB,    j * 4 + random(4) + 65);
   set_skill(SS_WEP_POLEARM, j * 4 + random(4) + 65);
   set_skill(SS_WEP_JAVELIN, j * 4 + random(4) + 65);
   set_skill(SS_WEP_AXE,     j * 4 + random(4) + 65);
   
   set_all_hitloc_unarmed(20);
   
   set_act_time(3);
   add_act("emote looks at you suspiciously.");
   add_act("emote snarls: What have we here?");
   add_act("emote hisses: Have you seen anyone with " +
      "a gemstone embedded in their chest? The Everman?");
   
   set_cact_time(10);
   add_cact("shout DIE THEN SCUM!");
   add_cact("shout Soldiers! To me!");
   
   set_color("blue");
   
   start_patrol();
   set_patrol_time(30);
   set_patrol_path(({"e","e","w","w","s","s",
		     "n","n","w","w","e","e"}));
   
}

void
init_living()
{
   init_team_pickup();
   ::init_living();
}