/* created by Arman 2017 */

#include "/d/Krynn/solamn/splains/local.h"
#include <ss_types.h>

inherit SIVAK;
inherit AUTO_TEAM

void
create_sivak()
{
   int i, j = 10;
   /* j is the level of the draconian */
   string str;
   
   set_pick_up_team(({"bozak","kapak","hobgoblin"}));
   set_max_team_size_auto_join(7);
   
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
   
   set_act_time(4);
   add_act("say The prisoners fled this way! Find their trail!");
   add_act("emote looks at the ground for tracks.");
   add_act("emote stares up at the mountains, looking for fleeing " +
       "slaves.");
   add_act("say Verminaard is furious the Disks of Mishakal have gone " +
       "missing!");
   add_act("say We must catch those prisoners before winter sets in!");
   add_act("say This trail wont be passable once the winter snows start.");
   set_cact_time(15);
   add_cact("say I don't have time for this!\n");
   add_cact("say Summon a dragon strike! Wait, where is my warhorn?\n");
   add_cact("grin");
   add_cact("emote shows you his claws.");
   add_cact("growl");   

   set_default_answer("The draconian patrol leader looks too busy to " +
         "answer your questions.\n");

   add_ask(({"prisoners","trails","slaves"}),"say The prisoners fled " +
        "into the mountains from the mines of Pax Tharkas! Verminaard " +
        "will be furious if they aren't caught!", 1);
   add_ask(({"disks","disks of mishakal","relics","items"}),
        "say No sooner did Verminaard get hold " +
        "of those relics of the forgotten gods did they get stolen!", 1);
   add_ask("verminaard","say Verminaard is furious items were stolen " +
        "from him by the fleeing prisoners. Word is Dragon Highlord " +
        "Ariakas isn't pleased with him either!", 1);
   add_ask(({"snow","winter snow"}),"say We need to find those " +
        "prisoners before winter arrives, or else the trail through the " +
        "mountains will fill with snow and be closed to us!", 1);

   set_color("red");

}


void
init_living()
{
   init_team_pickup();
   ::init_living();
}
