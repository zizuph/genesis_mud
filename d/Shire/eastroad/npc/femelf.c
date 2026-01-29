/* This file is femelf.c, used as a master elf file for the female elves
 * of the Shire :).
 * Avenger, April 30 1995
 * This file borrows from /d/Shire/michel/npc/militia.c
 * Dunstable, Jan 31 1995
 * N.B. When cloning this monster- call arm_me() before moving the object
 * to the room.
 */
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
 
/* These are random elf descriptions */
 
#define RNDADJ ({"sturdy","excited","dainty","slender","sweet","gentle",\
  "inquisitive","crass"})
#define RNDADJ2 ({"portly","nimble","elderly","jovial","kindly","friendly",\
   "merry","tired"})
#define RNDLONG ({"This sturdy elf, "+\
	"looks as if she could sweep a broom with authority.\n",\
	"This excited elf seems to be bouncing off "+\
	"the walls.\n",\
	"This dainty elf looks rather frail.\n",\
	"This slender elf looks at you with bright eyes.\n",\
	"This elf looks so sweet and kind- she couldn't harm a fly!\n",\
	"This gentle elf seems harmless.\n",\
	"This inquisitive elf looks at you in amazement.\n",\
	"This crass elf says what she means "+\
	"and means what she says.\n"})
 
/* These are random stats for the guards */
#define RNDSTAT ({\
		({72,73,75,82,67,68}),\
		({72,81,79,74,62,74}),\
		({66,70,67,85,65,60}),\
		({72,85,69,67,61,75}),\
		({62,71,71,72,73,65}),\
		({82,85,69,75,66,69}),\
		({63,73,71,83,63,77}),\
		({77,80,75,73,67,60})})
 
/* These is random equipment for guards */
#define RNDWEP ({"e_dagger","e_cknife","e_rapier","e_ssword",\
	 "e_staff"})
#define RNDARM ({"e_coat","e_hat","e_legs","e_scloak","e_splint"})
/* These are random combat and defence skills for guards */
#define SKILLCOM ({65,74,69,71,89})
#define SKILLDEF ({74,85,73,85,76})

int not_intro, alarm_id;
int intro_alarm, reintro_alarm;

void introduce_me();
void re_intro();

void 
create_monster()
{
 int ran, ran2, ran3, ranname, ranfam;
 
 if (!IS_CLONE)
  return;
 
 ran = random(8);
 ran2 = random(8);
 ran3 = random(5);
 ranname = random(39);

 ranfam = random(30);
 
 set_name(FEMALENAME[ranname]);
 add_name("villager");
 set_title(FAMILYNAME[ranfam]);
 set_pname("elves");
 set_gender(1);
 set_race_name("elf");
 set_adj(RNDADJ[ran]);
 add_adj(RNDADJ2[ran2]);
 set_alignment(276 + ran);
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
 add_chat("My husband loves to meet outsiders.");
 add_chat("How are you today?");
 add_chat("All I do is cook, clean, sew, wash, and mind the lads.");
 add_chat("I make some of the best tea.");
 add_chat("Have you been to Rivendell?");
 add_chat("My uncle once was on a grand adventure. He never came back.");
 add_chat("I learned a good bit about cooking from my mother.");
 add_chat("The best thing about the rain is the beauty it brings.");
 add_chat("My children enjoy it here at near the forest.");
 add_chat("Do you know my husband?");
 
 set_act_time(16 - ran);
  add_act("hug elves");
  add_act("pat all");
  add_act("smile happ");
  add_act("giggle merr");
 set_cact_time(5);
  add_cact("scream");
  add_cact("cry");
  add_cact("sigh sadl");
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
  command("kill orc");
  command("wield all");
  return;
  }
 race = player->query_race_name();
 if (player->query_prop("_i_kill_elfs_"))
  {
  command("glare at " + player->query_real_name());
  command("shout You're a rather bad "+ race +"!");
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
  command("wield all");
  command("shout Help! This " + ob->query_race_name() + 
   " wants to kill me!");
  ::attacked_by(ob);
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
 command("say Good riddance.");
 remove_alarm(alarm_id);
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
