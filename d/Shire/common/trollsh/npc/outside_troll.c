inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include <filter_funs.h>
#include "defs.h"

#define RLONG ({\
      "has dark eyes that blaze with hatred as they look at you.\n",\
      "looks at you with rage. A feeling of death radiates from "+\
        "his big black eyes. His hands are powerful looking, "+\
        "strong enough to crush you in one mighty blow!\n",\
      "has arms that are like timbers and the ground trembles "+\
        "when he walks.\n",\
      "looks ready to kill and eat you.\n",\
      "has blood around his mouth and guts hanging out, probaby " +\
        "from his most recent meal.\n" })

#define RWEIGHT ({400,350,450,300,403})
#define RHEIGHT ({320,200,190,300,201})

#define RADJ ({"red-eyed evil","grim looking","evil","hideous","menacing"})

//   Added more stats since there was only 2 here and there
//   you need 5 for the troll to load properly everytime.
//   Igneous Sept 17/96
#define RSTAT ({\
       ({150,200,240,75,90,140}), \
        ({150,200,240,90,99,140}), \
        ({150,200,240,99,100,140}), \
        ({150,200,240,90,89,140}), \
       ({160,190,220,90,90,160}) })

#define SKUCOM ({60,70,90,54,80})
#define SKUDEF ({60,90,50,40,60})

int time_next;

//  Prototype
void arm_me();

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
   set_name(({"troll", "troll soldier"}));
    add_name(({"troll", "soldier"}));
   set_pname(({"soldiers"}));
   set_short(RADJ[r] + " troll soldier");
   set_pshort(({" troll soldiers"}));
   set_adj(RADJ[r]);
   set_race_name("troll");
   set_long(
      "This is a half-trolls, one of the few left and created by " +
      "the Dark One. They are known for being leaders of large " +
      "orc armies, very ferocious and often guarded hordes of " +
      "treasure. Half-trolls are very large and their skin is " +
      "jet-black. This beast " + RLONG[r]);
   
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
   add_act("emote rumbles something terrible in his dark language.");
   add_act("emote shouts: You will die before me!");
   add_act("emote stares at you with hatred in his eyes.");
   add_act("emote challenges you to a fight.");
   
   set_cact_time(2);
   add_cact("emote fumes in anger!");
   add_cact("emote looks prepared to eat you after he finishes you off!!");
   add_cact("emote hisses: Is that the best you can do?");
   add_cact("hiss all");
   add_cact("emote attacks you with renewed strength.");
  
   set_alarm(1.0,0.0,arm_me);
   
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

void
arm_me()
{
   string wep = (({"trollmaul","trollclub","trollaxe"})[random(3)]);

   clone_object(TROLLSH_DIR + "weapon/"+wep)->move(TO);
   clone_object(TROLLSH_DIR + "arm/"+"troll_plate")->move(TO);
   clone_object(TROLLSH_DIR + "arm/"+"shield")->move(TO);
   command("wield weapon");
   command("wear armours");
}


