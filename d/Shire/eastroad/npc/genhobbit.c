/* This is the master for the hobbits in Whitefurrows. */
/* The code is taken from Anri's militia master in Michel. */
/* File .../common/monster/random_orc.c was used as an example */

inherit "/std/monster";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/d/Shire/common/monster/tobacco.h"
#include "/sys/language.h"
#include "/d/Shire/common/make_money.h";
#include "/d/Shire/prestige.h"
#include "names.h"
/* These are the random descriptions for the villagers */
#define RNDADJ ({"fat","sharp-eyed","nimble","cheerful", \
      "good-natured","tall"})
#define RNDLONG ({\
      "This hobbit is whistling happily. " + \
      "He returns your glance, and smiles at you. \n", \
      "This hobbit is rather stocky, with many freckles. " + \
      "He has a small pipe in his mouth, and is puffing away. \n", \
      "This hobbit looks rather surprised to see you. " + \
      "However, he quickly recovers himself, " + \
      "and stares at you curiously.\n", \
      "This hobbit is humming quietly to himself. " + \
      "When you glance at him, he stops, and turns away. \n", \
      "This hobbit is eating an apple. " + \
      "As you watch, he finishes eating, and tosses the core away. \n"})

/* These are the random stats for the villagers */
#define RNDSTAT ({20+random(10),40+random(20),15+random(15), \
      25+random(10),25+random(10),15+random(20)})

/* This is the random equipment carried by the villagers */
#define RNDWEP ({"h_dagger","h_knife","h_staff","h_club","h_spear"})
#define RNDARM ({"h_shirt","h_robe","h_cloak","h_tunic"})
/*These are the random combat skills for the villagers */
#define SKILLCOM (15+random(15))
#define SKILLDEF (15+random(10))
//   Prototypes
void arm_me();

int not_intro;
int intro_alarm, reintro_alarm;

void introduce_me();
void re_intro();


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

   set_pname("hobbits");

   set_race_name("hobbit");
   set_adj(RNDADJ[ran]);
   set_alignment(157 + ran);
   set_long("This is a male Hobbit of the Shire.  Like most hobbits " +
      "he is short, standing only about three and a half feet tall. " +
      "His hair is curly, and his shoeless feet are covered in thick " +
      "curly hair as well.  He is quite plump, " +
      "from too much good cooking.\n" + RNDLONG[ran]);
   add_prop(CONT_I_WEIGHT,30000);
   add_prop(CONT_I_HEIGHT,500);

   
   set_stats(RNDSTAT);
   
   set_skill(SS_UNARM_COMBAT, 10 + ran);
   set_skill(SS_WEP_KNIFE, SKILLCOM);
   set_skill(SS_WEP_POLEARM, SKILLCOM);
   set_skill(SS_WEP_CLUB, SKILLCOM);
   set_skill(SS_DEFENCE, SKILLDEF);
   clone_tobacco();
   
   set_chat_time(16+ran);
   add_chat("Where abouts are you from?");
   add_chat("You aren't from around here, are you...");
   add_chat("I hear that the Eastroad is being repaired...");
   add_chat("Have you seen those horrible trolls?");
   add_chat("I bet you've seen some strange things " +
      "in your travels...");
   add_chat("Have you got some tobacco for me?");
   add_chat("Some strange people have been passing through here lately!");
   add_chat("There is talk of danger from the East, " +
      "but surely those are just old wives tales?");
   
   set_cchat_time(6);
   add_cchat("Why are you doing this to me?");
   add_cchat("I am stronger than you think - flee while you can!");
   add_cchat("I'm too young to die!  Spare me, please!");
   add_cchat("I tell you anything, please spare me!");
   add_cchat("The shirriffes will defend me - just wait and see!");
   add_cchat("Don't kill me, please!  I'll be good, " +
      "really!");
   set_act_time(10+5*ran);
   add_act(({"smile","smile mis","smile dre","yawn","chuckle"}));
   set_cact_time(5);
   add_cact(({"frown","scream","explode","cry"}));
   
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
   ran = random(4);
   armo = clone_object(ER_DIR +"arm/" +RNDARM[ran]);
   armo->move(this_object());
   this_object()->command("wear all");
}

stop_naked(object player)
{ 
 
   string race=player->query_race_name();
   if (player->query_prop("_i_kill_hobbits_"))
      {
        command("glare at " + race);
        command("shout Hey!  This is the "+ race +" that has been killing hobbits!");
        command("say Please don't kill me, " +race +"!");
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
   if (!ob->query_prop("_i_kill_hobbits_"))
      ob->add_prop("_i_kill_hobbits_",1);
   command("shout Help! This " + ob->query_race_name() + " wants to kill me!");
}
void
react_introduce(string person,string who)
{
    if (not_intro)
	return;
    if (!intro_alarm)
        intro_alarm = set_alarm(4.0, 0.0, &introduce_me());
}

void
introduce_me()
{
    command("introduce myself");
    not_intro = 1;
    if (!reintro_alarm)
        reintro_alarm = set_alarm(15.0, 0.0, &re_intro());
}

void
re_intro()
{
    not_intro = 0;
}
