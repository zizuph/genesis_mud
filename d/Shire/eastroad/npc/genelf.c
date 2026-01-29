/* This is another master for the Elves of Shire.
 * Avenger, April 30 1995
 * This is the master for the hobbits in Whitefurrows. 
 * The code is taken from Anri's militia master in Michel.
 * File .../common/monster/random_orc.c was used as an example
 */
 
inherit "/std/monster";
 
#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/d/Shire/common/monster/tobacco.h"
#include "/sys/language.h"
#include "/d/Shire/common/make_money.h";
#include "/d/Shire/prestige.h"
#include "elfnames.h"
 
/* These are the random descriptions for the villagers */
#define RNDADJ ({"lean","sharp-eyed","nimble","cheerful", \
		"good-natured","tall"})
#define RNDLONG ({\
      "This hobbit is whistling happily. " + \
      "He returns your glance, and smiles at you. \n", \
      "This elf is rather stocky, with many freckles. " + \
      "He has a small pipe in his mouth, and is puffing away. \n", \
      "This elf looks rather surprised to see you. " + \
      "However, he quickly recovers himself, " + \
      "and stares at you curiously.\n", \
      "This elf is humming quietly to himself. " + \
      "When you glance at him, he stops, and turns away. \n", \
      "This elf is eating an apple. " + \
      "As you watch, he finishes eating, and tosses the core away. \n"})
 
/* These are the random stats for the villagers */
#define RNDSTAT ({62+random(20),65+random(20),65+random(15), \
		67+random(20),60+random(30),62+random(20)})
 
/* This is the random equipment carried by the villagers */
#define RNDWEP ({"e_cknife","e_dagger","e_rapier","e_ssword",\
		"e_staff"})
#define RNDARM ({"e_coat","e_hat","e_legs","e_scoak","e_splint"})
/*These are the random combat skills for the villagers */
#define SKILLCOM (60+random(30))
#define SKILLDEF (60+random(25))
//   Prototypes
void arm_me();
void re_intro();
void introduce_me();

int intro_id, re_intro_id;
int not_intro;
 

void
create_monster() {
 int ran, ranfam, ranname;
   
 if (!IS_CLONE)
  return;
   
 ran = random(5);
 ranname = random(77);
 ranfam = random(30);
 
 set_name(MALENAME[ranname]);
 add_name("villager");
 set_title(FAMILYNAME[ranfam]);
 
 set_pname("elves");
 set_race_name("elf");
 set_adj(RNDADJ[ran]);
 set_alignment(157 + ran);
 set_long("This is a male elf of the Shire.  Like most elves " +
  "he is tall, standing about six and a half feet tall.\n" +
 RNDLONG[ran]);
 add_prop(CONT_I_WEIGHT,3000);
 add_prop(CONT_I_HEIGHT,50000);
 
 set_stats(RNDSTAT);
 
 set_skill(SS_UNARM_COMBAT, 30 + ran);
 set_skill(SS_WEP_SWORD, SKILLCOM);
 set_skill(SS_WEP_KNIFE, SKILLCOM);
 set_skill(SS_WEP_POLEARM, SKILLCOM);
 set_skill(SS_DEFENCE, SKILLDEF);
 set_skill(SS_PARRY, SKILLDEF);

 

 set_chat_time(16+ran);
  add_chat("Where abouts are you from?");
  add_chat("You aren't from around here, are you...");
  add_chat("I hear that the Eastroad is being repaired...");
  add_chat("Have you seen those horrible trolls?");
  add_chat("I bet you've seen some strange things " +
   "in your travels...");
  add_chat("Some strange people have been passing through here lately!");
  add_chat("There is talk of danger from the East, " +
   "best that you becarefull.");
	
 set_cchat_time(6);
  add_cchat("Why are you doing this to me?");
  add_cchat("I am stronger than you think - flee while you can!");
  add_cchat("I'm too young to die!  Spare me, please!");
 set_act_time(10+5*ran);
  add_act(({"smile","smile mis","smile dre","yawn","chuckle"}));
 set_cact_time(5);
  add_cact(({"frown","scream","explode"}));
       
 set_alarm(3.0,0.0,&arm_me());
 MAKE_MONEY;
 trig_new("%w 'introduces' %s", "react_introduce");
}
/* This equips the villagers with weapons and armour */
void
arm_me()
{  
 int ran;
 object weap;
 object armo;
 
 ran = random(5);
 weap = clone_object(ER_DIR +"wep/" +RNDWEP[ran]);
 weap->move(this_object());
 this_object()->command("wield all");
 ran = random(5);
 armo = clone_object(ER_DIR +"arm/" +RNDARM[ran]);
 armo->move(this_object());
 this_object()->command("wear all");
}
 
stop_naked(object player)
{ 
 string race=player->query_race_name();
 if (player->query_prop("_i_kill_elfs_"))
  {
  command("glare at " + player->query_real_name());
  command("shout Hey!  This is the "+ race +" that has "+
   "been killing elves!");
  command("kill "+ player->query_real_name());
  }
}
 
void init_living()
{
 ::init_living();
 set_alarm(1.0,0.0,"stop_naked",TP);
}
 
public void
attacked_by(object ob)
{ 
 ::attacked_by(ob);
 if (!ob->query_prop("_i_kill_elfs_"))
  ob->add_prop("_i_kill_elfs_",1);
  /* Just to make sure that the weapon is  wielded */
  command("wield all");
  command("shout Help! This " + ob->query_race_name() + 
   " is trying to kill me!");
}
void
react_introduce(string person,string who)
{
   if (not_intro)
      return;
   if (intro_id)   
      {
      if (ftoi(get_alarm(intro_id)[2]) != 0)   
         {
         intro_id = set_alarm(4.0,0.0,&introduce_me());
      } 
   }
}
 
void
introduce_me()
{
   command("introduce me");
   not_intro = 1;
   if (re_intro_id)
      {
      if (ftoi(get_alarm(re_intro_id)[2]) != 0)
         {
         re_intro_id = set_alarm(15.0,0.0,&re_intro());
       }
   }
}
 
void
re_intro()
{
 not_intro = 0;
}
 
