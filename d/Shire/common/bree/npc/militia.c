/* This file generates a random hobbit guard.  */
/* File .../common/monster/random_orc.c was used as an example */
 
inherit "/std/monster";
 
#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/d/Shire/common/monster/tobacco.h"
#include "/sys/language.h"
#include "/d/Shire/common/make_money.h";
 
/* These are random guards descriptions */
#define RNDADJ ({"plump","swift","young","merry","hungry"})
#define RNDLONG ({\
   "This is a plump hobbit. Even for hobbits. \n" + \
   "He looks like guarding his native land from intruders. \n", \
   "This hobbit is very skillful and quick. \n" + \
   "He is a member of local militia force. \n", \
   "This is a young hobbit. He is obviously 30 - 40 years old. \n" + \
   "He is very proud of being a member of local militia force. \n", \
   "This hobbit looks very funny and joyful. \n" + \
   "He likes his job - guarding his village. \n", \
   "This hobbit looks bored with guard duty. Its not really his cup of tea. \n" + \
   "He thinks that it is time to have a meal. \n"})
 
/* These are random stats for the guards */
#define RNDSTAT ({\
                   ({35,55,35,30,27,35}),\
                   ({32,65,29,30,30,35}),\
                   ({26,60,27,25,25,30}),\
                   ({33,62,31,33,33,35}),\
                   ({27,70,29,30,30,30})})
 
/* These is random equipment for guards */
#define RNDWEP ({"h_sword","h_dagger","h_pole","h_spear","h_flail"})
#define RNDARM ({"h_shirt","h_shield","h_helm","h_mail","h_cloak"})
/* These are random combat and defence skills for guards */
#define SKILLCOM ({35,44,30,31,29})
#define SKILLDEF ({24,25,33,35,36})
 

//  Prototypes
void arm_me();
void wear_me();

void
create_monster() {
   int ran;
 
   if (!IS_CLONE)
      return;
 
   ran = random(5);
   set_name("_hobbit_militia_");
   set_pname("hobbits");
   set_short(RNDADJ[ran] + " hobbit");
   set_race_name("hobbit");
   set_adj(RNDADJ[ran]);
   set_alignment(100 + ran);
   set_long(RNDLONG[ran]);
   add_prop(CONT_I_WEIGHT,30000);
   add_prop(CONT_I_HEIGHT,500);
   add_prop(LIVE_I_NEVERKNOWN,1);
 
   set_stats(RNDSTAT[ran]);
 
   set_skill(SS_UNARM_COMBAT, 10 + ran);
   set_skill(SS_WEP_SWORD, SKILLCOM[ran]);
   set_skill(SS_WEP_KNIFE, SKILLCOM[ran]);
   set_skill(SS_WEP_POLEARM, SKILLCOM[ran]);
   set_skill(SS_WEP_CLUB, SKILLCOM[ran]);
   set_skill(SS_DEFENCE, SKILLDEF[ran]);
   set_skill(SS_PARRY, SKILLDEF[ran]);
   clone_tobacco();
 
   set_chat_time(16+ran);
   add_chat("What is your name, stranger?");
   add_chat("You look strange to me...hmm.");
   add_chat("The Eastroad is very dangerous nowerdays.");
   add_chat("I will make my country free of orcs!");
   add_chat("Help us to kill those orcs!");
   add_chat("This area looks quite enough for you to travel.");
   add_chat("Be carefull, some people saw strangers nearby!");
   add_chat("Beware from the Black Riders, traveller.");
 
   set_cchat_time(6);
   add_cchat("Hey, stupid, stop the fighting!");
   add_cchat("Run away or I will call for my friends!");
   add_cchat("I was kidding but I gonna beat you really hard now!");
   add_cchat("We - hobbits dont like to fight. Stop it!");
   add_cchat("You will pay for this with your pointless life!");
 
   set_act_time(10+2*ran);
   add_act(({"smile","smile mis","smile dre","yawn","chuckle"}));
   set_cact_time(5);
   add_cact(({"frown","scream","kick all","explode"}));
 
   set_alarm(0.1,0.0,&arm_me());
   set_alarm(0.1,0.0,&wear_me());
   MAKE_MONEY;
 
}
/* Here I equip my militia with weapons, armours and cash */
   arm_me() {
   int ran;
   object weap;
   ran = random(5);
   weap = clone_object("/d/Shire/anri/weapons/" +RNDWEP[ran]);
   weap->move(this_object());
   this_object()->command("wield all");
   }
   wear_me() {
   int ran;
   object armo;
   ran = random(5);
   armo = clone_object("/d/Shire/anri/armours/" +RNDARM[ran]);
   armo->move(this_object());
   this_object()->command("wear all");
   }
