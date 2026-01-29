inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"

#define RNDADJ ({"suspicious","haughty","glaring","treacherous","despicable"})
#define RNDLONG ({\
      "This suspicous-looking individual stares at you with eyes as red " + \
      "as the burning embers of a fire. The redness of his eyes seems to " + \
      "match well the coal-black color of his skin.\n", \
      "This arrogant-looking drow gazes at you as though you were but a " + \
      "lowly goblin in the slave pits of Undraeth.\n", \
      "This particular drow is continually glaring at everyone around " + \
      "him, as though suspecting an attack from anyone, at anytime.\n", \
      "A drow whose face exhibits the worst features of any race, a truly " + \
      "treacherous-looking individual.\n", \
      "A truly wretched individual, it appears as if he has been living on " + \
      "refuse for years, if not all of his life.\n"})

#define RNDSTAT ({\
      ({50,75,50,25,25,60}),\
      ({55,70,60,25,25,60}),\
      ({60,65,55,25,25,55}),\
      ({50,70,60,25,25,60}),\
      ({45,70,50,25,25,55})})

#define RNDWEP ({"dw_dagger","dw_dagger","dw_sword","dw_dagger","dw_dagger"})
#define RNDARM ({"dw_chain","dw_shield","dw_chain","dw_shield","dw_chain"})
#define SKILLCOM ({60,70,55,75,50})
#define SKILLDEF ({75,65,55,80,65})

/* by Antharanos */

create_monster()
{
   int ran;
   ran = random(5);
   set_name("drow");
   set_short(RNDADJ[ran] + " drow");
   set_pshort(RNDADJ[ran] + " drow");
   set_race_name("drow");
   set_adj(RNDADJ[ran]);
   set_alignment(-500 - ran);
   set_knight_prestige(500);
   set_long(RNDLONG[ran]);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_SEE_DARK,10);
   
   set_stats(RNDSTAT[ran]);
   
   set_skill(SS_UNARM_COMBAT, 10 + ran);
   set_skill(SS_WEP_SWORD, SKILLCOM[ran]);
   set_skill(SS_WEP_KNIFE, SKILLCOM[ran]);
   set_skill(SS_DEFENCE, SKILLDEF[ran]);
   set_skill(SS_PARRY, SKILLDEF[ran]);
   set_skill(SS_BLIND_COMBAT, SKILLDEF[ran]);
   set_skill(SS_AWARENESS, SKILLDEF[ran]);
   
   set_chat_time(16+ran);
   add_chat("Jal khaless zhah waela.");
   add_chat("Oloth zhah tuth abbil lueth ogglin.");
   add_chat("Lolth tlu malla; jal ultrinnan zhah xundus.");
   add_chat("Rivvin phuul iblith.");
   
   set_cchat_time(6);
   add_cchat("Waela iblith!");
   add_cchat("Lolth plynn dos!");
   add_cchat("Elghinn ulu ogglin del Lolth lueth Undraeth!");
   
   set_act_time(10+2*ran);
   add_act(({"grin","chuckle evil","smile evil","cackle evil","think the coming war."}));
   set_cact_time(5);
   add_cact(({"frown","laugh evil","snarl all","grin sadis"}));
   set_random_move(10);
   
}
void
arm_me()
{  
   int ran;
   object weap;
   object armo;
   seteuid(getuid(TO));
   ran = random(5);
   weap = clone_object("/d/Kalad/common/wild/pass/wep/" + RNDWEP[ran]);
   weap -> move(TO);
   command("wield all");
   ran = random(5);
   armo = clone_object("/d/Kalad/common/wild/pass/arm/" + RNDARM[ran]);
   armo -> move(TO);
   armo = clone_object(CPASS(arm/dw_helm));
   armo -> move(TO);
   armo = clone_object(CPASS(arm/dw_boots));
   armo -> move(TO);
   armo = clone_object(CPASS(arm/piwafwi));
   armo -> move(TO);
   command("wear all");
   MONEY_MAKE_SC(random(10))->move(TO,1);
}
