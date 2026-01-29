inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/guild/defs.h"

/* These are random guards descriptions */
#define RNDADJ ({"strong","swift","young","scowling","tough"})
#define RNDLONG ({\
   "This is a strong drow guard. He looks unhappy to be here. \n" + \
   "He looks like he is guarding his native land from intruders. \n", \
   "This drow is very skillful and quick. \n" + \
   "He is a member of the local guard force. \n", \
   "This is a young drow. He looks out of place in his uniform. \n" + \
   "He looks like a tough opponent, even tougher than others. \n", \
   "He looks annoyed about something. \n" + \
   "He likes to kill intruders \n", \
   "This hobbit is obviously not happy, messing with him would be bad. \n" + \
   "He wants to go kill some gnomes. \n"})

/* These are random stats for the guards */
#define RNDSTAT ({\
                   ({75,55,65,30,27,65}),\
                   ({52,65,59,30,30,55}),\
                   ({66,80,47,25,25,70}),\
                   ({63,62,81,33,33,65}),\
                   ({77,70,89,30,30,30})})

/* These is random equipment for guards */
#define RNDWEP ({"dw_sword","dw_dagger","dw_halb","dw_spear","dw_mace"})
#define RNDARM ({"dw_plate","dw_shield","dw_robe","dw_chain","dw_jerkin"})
/* These are random combat and defence skills for guards */
#define SKILLCOM ({55,64,50,71,49})
#define SKILLDEF ({74,65,53,75,66})

create_monster() {
   int ran;

   if (!IS_CLONE)
      return;

   ran = random(5);
   set_name("militia");
   add_name(({"drow guard","guard","_drow_guard_"}));
   set_pname("drow");
   set_short(RNDADJ[ran] + " drow");
   set_race_name("drow");
   set_adj(RNDADJ[ran]);
   set_alignment(100 - ran);
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

   set_chat_time(16+ran);
   add_chat("What is your name, stranger?");
   add_chat("You look strange...hmm.");
   add_chat("Menzoberanzan is very dangerous to those who don't belong.");
   add_chat("I will make my house rise to the top!");
   add_chat("Those pitiful gnomes!");
   add_chat("This area looks quite enough for you to travel.");
   add_chat("Be carefull, some people saw strangers nearby!");
   add_chat("Beware the High Priestess traveller they might not like you.");

   set_cchat_time(6);
   add_cchat("Hey, this idiot wants to fight!");
   add_cchat("Begone worm or Lloth's wrath will fall upon you!");
   add_cchat("You really think you can defeat a member of the streeakh?");
   add_cchat("Bring it on scumbag, I'll turn your head into mush!");
   add_cchat("Lloth will be pleased by your death.");

   set_act_time(10+2*ran);
   add_act(({"grin","sigh","smile evi","yawn","chuckle"}));
   set_cact_time(5);
   add_cact(({"frown","chuckle","kick all","grin sadis"}));
   set_random_move(10);
   set_alarm(1.0,0.0,"arm_me");

}
/* Here I equip my militia with weapons and armours */
void
arm_me()
{  
   int ran;
   object weap;
   object armo;
   seteuid(geteuid(this_object()));
   ran = random(5);
   weap = clone_object(PASS +"wep/" +RNDWEP[ran]);
   weap -> move(this_object());
   command("wield all");
   ran = random(5);
   armo = clone_object(PASS +"arm/" +RNDARM[ran]);
   armo -> move(this_object());
   armo = clone_object(PASS +"arm/" +"dw_helm");
   armo -> move(this_object());
   armo = clone_object(PASS +"arm/" +"dw_boots");
   armo -> move(this_object());
   armo = clone_object(DGUILD +"obj/" +"insignia");
   armo -> move(this_object());
   armo = clone_object(PASS +"arm/" +"piwafwi");
   armo -> move(this_object());
   command("wear all");
}
