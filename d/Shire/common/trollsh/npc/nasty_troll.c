inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include <filter_funs.h>
#include "defs.h"

#define RLONG ({\
      "has got some dark stirring eyes, it looks like he cannot focus on "+\
      "anything. They are just rolling aaround and round.\n",\
      "looks at you with rage. Death radiates from his big black eyes, and "+\
      "his hands...they could crush you in one mighty blow!!!\n",\
      "must be the most powerful chalf-troll ever seen. Arms like timber, and "+\
      "the ground trembles when he walks.\n",\
      "looks ready to kill you, better not make him angry....\n",\
      "has blood around his mouth and guts hanging out...looks like he enjoys "+\
      "eating raw flesh!!!\n" })

#define RWEIGHT ({400,350,450,300,403})
#define RHEIGHT ({320,200,190,300,201})

#define RADJ ({"red-eyed evil","grim looking","evil","hideous","laging"})

#define RSTAT ({\
      ({180,30,200,9,40,90}), \
      ({200,50,120,20,7,100}), \
     ({180,30,120,10,4,90}), \
      ({185,40,200,6,4,76}),  \
      ({165,47,190,10,14,80}) })

#define SKUCOM ({60,70,90,54,80})
#define SKUDEF ({60,90,50,40,60})

int time_next;
int alarm_id;

create_monster()
{
   seteuid(geteuid());
   create_nasty_troll(random(5));
}

int trollrand(int val)
{
   return val-val/4+random(val/2)+2;
}

void
setup_skills();

create_nasty_troll(int r)
{
   set_name(({"cave troll","troll soldier", "_troll_soldier"}));
   set_pname(({"soldiers"}));
   set_short(RADJ[r] + "troll soldier");
   set_pshort(({"troll soldiers"}));
   set_adj(RADJ[r]);
   set_race_name("half-troll");
   set_long(
      "This is one of the half-trolls Sauron created. One of "
      +"the last known half-troll that is left. They are "
      +"known for being leader of big orc armies, so they "
      +"might have something hidden here. They are very large, "
      +"and their skin is jet-black, and a red hissing thung "
      +"is hanging out of his mouth. This beast " + RLONG[r]);
   
   add_prop(CONT_I_WEIGHT, RWEIGHT[r] * 1000);
   add_prop(CONT_I_HEIGHT, RHEIGHT[r]);
   
   set_stats(RSTAT[r]);
   
   setup_skills();
   
   set_skill(SS_UNARM_COMBAT, trollrand(SKUCOM[r]));
   set_skill(SS_WEP_CLUB,     trollrand(SKUCOM[r]));
   set_skill(SS_WEP_AXE,   trollrand(SKUCOM[r]));
   set_skill(SS_PARRY,        trollrand(SKUDEF[r]));
   set_skill(SS_DEFENCE,   trollrand(SKUDEF[r]));
   set_pick_up(80);
   
   set_aggressive(50); set_attack_chance(80);
   set_alignment(-600 - random(100));
   
   set_act_time(4);
   add_act("emote inspects his nasty weapon.");
   add_act("says: Olog SNAGA pertog, nibo peck!!");
   add_act(({"shout SSSSStiiiiiiik hefra PECK!!!!","explode"}));
   add_act("sniff");
   add_act("emote picks his nose skillfully.");
   
   set_cact_time(2);
   add_cact("emote fumes in anger!");
   add_cact("emote looks prepared to eat you after he finishes you off!!");
   add_cact("emote hisses: D e lur nu eh hae?");
   add_cact("hiss all");
   add_cact("confused");
   add_cact(({"shout HEY PECK, INTRO!!!","laugh"}));
   
   
   alarm_id = set_alarm(1.0, 0.0, "arm_me");
   
}
void
setup_skills()
{
   mapping allskills = SS_SKILL_DESC;
   int *skills = m_indexes(allskills);
   int i;
   
   for(i=0;i<sizeof(skills);i++)
   set_skill(skills[i], trollrand(query_stat(allskills[skills[i]][2]))/2);
   
}

arm_me()
{
   string wep = (({"trollmaul","trollclub","trollaxe"})[random(3)]);
   remove_alarm(alarm_id);
   clone_object(TROLLSH_DIR + "weapon/"+wep)->move(TO);
   /*clone_object(TROLLSH_DIR + "armour/"+"trollplate")->move(TO);
   clone_object(TROLLSH_DIR + "armour/"+"spikedshield")->move(TO);*/
   command("wield weapon");
   command("wear armours");
}


