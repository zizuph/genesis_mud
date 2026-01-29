/* created by Aridor 04/19/94 */

#include "/d/Krynn/solamn/splains/local.h"
#include <ss_types.h>

inherit SIVAK;
inherit AUTO_TEAM

void
create_sivak()
{
   int i, j = random(6) + 3;
   /* j is the level of the draconian */
   string str;
   
   set_pick_up_team(({"ogre","baaz","goblin","hobgoblin"}));
   
   for(i=0; i<6; i++)
     set_base_stat(i, j * 10 + random(10) + 30);
   set_skill(SS_DEFENCE,     j * 5 + random(4) + 65);
   set_skill(SS_PARRY,       j * 4 + random(4) + 65);
   set_skill(SS_WEP_SWORD,   j * 4 + random(4) + 65);
   set_skill(SS_2H_COMBAT,   j * 4 + random(4) + 65);
   set_skill(SS_WEP_KNIFE,   j * 4 + random(4) + 65);
   set_skill(SS_WEP_CLUB,    j * 4 + random(4) + 65);
   set_skill(SS_WEP_POLEARM, j * 4 + random(4) + 65);
   set_skill(SS_WEP_JAVELIN, j * 4 + random(4) + 65);
   set_skill(SS_WEP_AXE,     j * 4 + random(4) + 65);
   
   set_act_time(3);
   add_act("scream");
   add_act("stare");
   add_act("emote shows you his claws.");
   add_act("say What are you doing here?");
   add_act(({"say Get lost!", "laugh"}));
   add_act("emote shows you the finger, or rather, his middle claw.");
   add_act("frown");
   add_act("grin");
   add_act("giggle");
   add_act("twiddle");
   set_cact_time(10);
   add_cact("say You really think you can defeat me?\n");
   add_cact("say Ahhh, now I can test my battle skill.\n");
   add_cact("say I didn't even feel that!\n");
   add_cact("say Is that all you can do?\n");
   add_cact("say Don't take it personally but I'll kill you.\n");
   add_cact("grin");
   
   set_color("blue");
   
   start_patrol();
   set_patrol_time(30);
   set_patrol_path(({"n","e","s","e","e","s","w","w","n","w"}));
}


void
init_living()
{
   init_team_pickup();
   ::init_living();
}
