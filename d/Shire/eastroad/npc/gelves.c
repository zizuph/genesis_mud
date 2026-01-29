// This file is gelves.c, used for the master elf file for Shire.
// I have taken it from ghobbit.c to make this file.
// Avenger, April 29 1995
// This file borrows from /d/Shire/michel/npc/militia.c
// Dunstable, Jan 31 1995
// N.B. When cloning this monster- call arm_me() before moving the object
// to the room.
inherit "/std/monster";
 
#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/d/Shire/common/monster/tobacco.h"
#include "/sys/language.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/prestige.h"
#include "elfnames.h"
/* These are random guards descriptions */
 
#define RNDADJ ({"tall","energetic","boisterous","jovial","sweet","talkative",\
  "curious","passive"})
#define RNDADJ2 ({"lean","agile","young","jolly","hungry","joyous",\
	"silly","thin"})
#define RNDLONG ({"This tall elf - Well most elves are tall, "+\
	"looks at you with active, searching eyes.\n",\
	"This energetic elf seems to be bouncing off "+\
	"the walls.\n",\
	"This boisterous elf looks completely irrepressible.\n",\
	"This jovial elf looks at you with plalyful eyes.\n",\
	"This elf looks so sweet and kind- he couldn't harm a fly!\n",\
	"This talkative elf seems to never close his jaws.\n",\
	"This curious elf looks at you in amazement.\n",\
	"This sleepy elf has one eye fully closed and the other "+\
	"is almost closed as well.\n"})
 
/* These are random stats for the guards */
#define RNDSTAT ({\
		({67,75,65,72,67,68}),\
		({69,78,69,84,72,74}),\
		({66,80,77,75,65,65}),\
		({77,75,69,71,61,75}),\
		({68,79,71,72,63,67}),\
		({82,75,85,85,76,69}),\
		({73,73,71,83,73,67}),\
		({77,79,85,83,77,80})})
 
/* These is random equipment for guards */
#define RNDWEP ({"e_cknife","e_dagger","e_rapier",\
	"e_ssword","e_staff"})
#define RNDARM ({"e_coat","e_hat","e_legs","e_scloak",\
	"e_splint"})
/* These are random combat and defence skills for guards */
#define SKILLCOM ({75,67,80,65,79})
#define SKILLDEF ({69,75,83,65,79})
//   Prototypes
void re_intro();
void introduce_me();

int intro_id, re_intro_id;
int not_intro, alarm_id;
 
void 
create_monster()
{
 int ran, ran2, ran3, ranfam, ranname;
 
 if (!IS_CLONE)
  return;
 
 ran = random(8);
 ran2 = random(8);
 ran3 = random(5);
 ranname = random(77);
 ranfam = random(30);
 
 set_name(MALENAME[ranname]);
 add_name("villager");
 set_title(FAMILYNAME[ranfam]);
 set_pname("elves");
 set_race_name("elf");
 set_adj(RNDADJ[ran]);
 add_adj(RNDADJ2[ran2]);
 set_alignment(302 + ran);
 set_long(RNDLONG[ran]);
 add_prop(CONT_I_WEIGHT,3000);
 add_prop(CONT_I_HEIGHT,5000);
 
 set_stats(RNDSTAT[ran]);
 
 set_skill(SS_WEP_SWORD, SKILLCOM[ran3]);
 set_skill(SS_WEP_KNIFE, SKILLCOM[ran3]);
 set_skill(SS_WEP_POLEARM, SKILLCOM[ran3]);
 set_skill(SS_DEFENCE, SKILLDEF[ran3]);
 set_skill(SS_PARRY, SKILLDEF[ran3]);
 
 set_chat_time(16+ran);
  add_chat("How are you today?");
  add_chat("It is supposed to rain tomorrow, I think.");
  add_chat("I love to drink ale and wine.");
  add_chat("Have you been to Rivendell?");
  add_chat("I have been on many adventures.");
  add_chat("My wife is an excellent cook.");
  add_chat("I had a wonderful time at the party last night.");
  add_chat("Do I know you?");
 
 set_act_time(16 - ran);
  add_act("poke all");
  add_act("cackle");
  add_act("ponder");
  add_act("chuckle misc");
 
 set_cact_time(5);
  add_cact("scream");
  add_cact("cry");
  add_cact("whine sadl");
 
 MAKE_MONEY;
 trig_new("%w 'introduces' %s", "react_introduce");
}
 

void
arm_me()
{ 
 int ran, ran2;
 object weap;
 object armo;
 
 ran = random(5);
 ran2 = random(5);
 
 weap = clone_object(ER_DIR +"wep/" +RNDWEP[ran]);
 weap->move(TO,1);
 armo = clone_object(ER_DIR +"arm/" +RNDARM[ran2]);
 armo->move(TO,1);
 TO->command("wear all");
}
 
void 
stop_killers(object player)
{
 string race;
 
 if(present("orc",environment(this_object())))
  {
  command("shout DIE ORC!");
  command("wield all");
  command("kill orc");
  return;
  }
 
 race = player->query_race_name();
 if (player->query_prop("_i_kill_elfs_"))

  {
  command("glare at " + player->query_real_name());

  command("shout This is a killer "+ race +"!");
  command("shout Stand back, I will deal with this vermin!");
  command("wield all");
  command("kill " + player->query_real_name());
  return;
  }
}
 
void
init_living()
{
 ::init_living();
 set_alarm(1.0,0.0,"stop_killers",TP);
}
 
public void
attacked_by(object ob)
{ 
 if (!ob->query_prop("_i_kill_elfs_"))
  ob->add_prop("_i_kill_elfs_",1);
  command("shout I'll make this " + ob->query_race_name() + 
   " regret it!");
  ::attacked_by(ob);
  command("wield all");
  alarm_id = set_alarm(10.0,20.0,"before_attack");
  return;
}
 
void
before_attack()
{
 if(TO->query_attack())
  {
  return;
  }
 command("unwield all");
 remove_alarm(alarm_id);
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
