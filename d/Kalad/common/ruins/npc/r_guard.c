inherit "/d/Kalad/std/monster";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#include "/sys/language.h"
#include "/d/Kalad/common/zhent/defs.h"

/* These are random guards descriptions */
#define RNDADJ ({"strong","swift","young","scowling","tough"})
#define RNDLONG ({\
      "He looks very annoyed to be on duty today. \n", \
      "This guard looks like he is a skilled warrior. \n", \
      "He looks like he could kill you with but a glance. \n", \
      "This is a guard with broad shoulders. He looks strong. \n", \
      "He is adjusting his armour as if preparing for battle.\n"})
/* These are random stats for the guards */
#define RNDSTAT ({\
      ({95,75,85,30,27,65}),\
      ({72,85,79,30,30,55}),\
      ({76,90,87,25,25,70}),\
      ({73,72,91,33,33,65}),\
      ({87,80,99,30,30,70})})

/* These is random equipment for guards */
#define RNDWEP ({"g_sword","g_axe","g_halb","g_spear","g_flail"})
#define RNDARM ({"g_plate","g_shield","g_robe","g_mail","g_jerkin"})
/* These are random combat and defence skills for guards */
#define SKILLCOM ({75,84,70,91,79})
#define SKILLDEF ({94,85,73,95,86})

create_monster() {
   int ran;
   
   if (!IS_CLONE)
      return;
   
   ran = random(5);
   set_name("guard");
   add_name(({"city guard","guard","_city_guard_"}));
   set_pname("guards");
   set_short(RNDADJ[ran] + " guard");
   set_race_name("human");
   set_adj(RNDADJ[ran]);
   set_alignment(150 - ran);
   set_long(RNDLONG[ran]);
   add_prop(CONT_I_WEIGHT,30000);
   add_prop(CONT_I_HEIGHT,500);
   add_prop(LIVE_I_NEVERKNOWN,1);
   
   set_stats(RNDSTAT[ran]);
   
   set_skill(SS_UNARM_COMBAT, 10 + ran);
   set_skill(SS_WEP_SWORD, SKILLCOM[ran]);
   set_skill(SS_WEP_AXE, SKILLCOM[ran]);
   set_skill(SS_WEP_POLEARM, SKILLCOM[ran]);
   set_skill(SS_WEP_CLUB, SKILLCOM[ran]);
   set_skill(SS_DEFENCE, SKILLDEF[ran]);
   set_skill(SS_PARRY, SKILLDEF[ran]);
   
   set_chat_time(16+ran);
   add_chat("What is your name, stranger?");
   add_chat("You look strange...hmm.");
   add_chat("Zhentil Keep is not a place for the despicable paladins.");
   add_chat("Cyric will allow us to control everything!");
   add_chat("The people of Zhentil Keep are not weaklings!");
   add_chat("This area looks quite enough for you to travel.");
   add_chat("Be carefull, sometimes people like you can get hurt!");
   add_chat("Behave when within our city traveller, or you may have problems.");
   
   set_cchat_time(6);
   add_cchat("Hey, this idiot wants to fight!");
   add_cchat("Guards! This fool needs to be taught a lesson!");
   add_cchat("I bet your mother will cry when i tell her how i killed you!");
   add_cchat("Bring it on scumbag, I'll split your head like a melon!");
   add_cchat("Your death will be mourned only by your fleas!.");
   set_act_time(10+2*ran);
   add_act(({"grin","sigh","smile evi","yawn","chuckle"}));
   set_cact_time(5);
   add_cact(({"frown","chuckle","kick all","grin sadis"}));
   set_random_move(10);
   set_alarm(1.0,0.0,"arm_me");
}
/* Here I equip my militia with weapons and armours */
arm_me()
{  int ran;
   object weap;
   object armo;
   ran = random(5);
   weap = clone_object(ZHENT +"wep/" +RNDWEP[ran]);
   weap->move(this_object());
   this_object()->command("wield all");
   ran = random(5);
   armo = clone_object(ZHENT +"arm/" +RNDARM[ran]);
   armo->move(this_object());
   armo = clone_object(ZHENT +"arm/g_boots");
   armo->move(this_object());
   armo = clone_object(ZHENT +"arm/g_helm");
   armo->move(this_object());
   armo = clone_object(ZHENT +"arm/g_cloak");
   armo->move(this_object());
   this_object()->command("wear all");
}
