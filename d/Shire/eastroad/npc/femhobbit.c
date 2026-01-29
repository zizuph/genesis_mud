// This file is whobbit.c, used as a master hobbit file for the female hobbits
// of the Shire :).
// This file borrows from /d/Shire/michel/npc/militia.c
// Dunstable, Jan 31 1995
// N.B. When cloning this monster- call arm_me() before moving the object
// to the room.
//
// 1996/06/07 Last update
// 2011/08/03 Lavellan - Added sizes, not all very tall very skinny hobbits...

inherit "/std/monster";
 
#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/d/Shire/common/monster/tobacco.h"
#include "/sys/language.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/prestige.h"
#include "names.h"

/* These are random hobbit descriptions */

#define RNDADJ ({"sturdy","excited","dainty","slender","sweet","gentle",\
  "inquisitive","crass"})
//#define RNDADJ2 ({"portly","nimble","elderly","jovial","kindly","friendly",
#define RNDADJ2 ({"young","nimble","elderly","jovial","kindly","friendly",\
   "merry","tired"})
#define RNDLONG ({"This sturdy hobbit, "+\
"looks as if she could sweep a broom with authority.\n",\
"This excited hobbit seems to be bouncing off "+\
   "the walls.\n",\
   "This dainty hobbit looks rather frail.\n",\
   "This slender hobbit looks up at you with bright eyes.\n",\
   "This hobbit looks so sweet and kind- she couldn't harm a fly!\n",\
   "This gentle hobbit seems harmless.\n",\
   "This inquisitive hobbit looks at you in amazement.\n",\
"This crass hobbit says what she means "+\
   "and means what she says.\n"})
 
/* These are random stats for the guards */
#define RNDSTAT ({\
                   ({32,43,35,22,27,38}),\
                   ({32,51,39,24,22,34}),\
                   ({26,40,27,15,25,30}),\
                   ({32,55,29,11,21,35}),\
                   ({42,51,31,12,23,25}),\
                   ({32,45,29,15,26,29}),\
                   ({43,63,31,23,23,37}),\
                   ({27,40,25,13,27,30})})
 
/* These is random equipment for guards */
#define RNDWEP ({"h_dagger","h_pole","h_spear","h_flail",\
    "cknife","dbaxe","pitchfork","rapier","sgauche","hatchet","hickclub",\
    "ironclub","shortsword","shovel"})
#define RNDARM ({"h_shirt","h_robe","h_tunic","h_cloak",\
     "coat","hat","leggings","lshirt","pants","scloak"})
/* These are random combat and defence skills for guards */
#define SKILLCOM ({35,44,30,31,29})
#define SKILLDEF ({24,25,33,35,36})
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
   set_pname("hobbits");
   set_gender(1);
   set_race_name("hobbit");
   set_adj(RNDADJ[ran]);
   add_adj(RNDADJ2[ran2]);
   set_alignment(276 + ran);
   set_long(RNDLONG[ran]);
   if (ran == 2)
      set_size_descs("of normal length", "lean");
   else if (ran == 3)
      set_size_descs("tall", "skinny");
   else
      set_size_descs("of normal length", "of normal width");
   //add_prop(CONT_I_WEIGHT,30000);
   //add_prop(CONT_I_HEIGHT,500);

 
   set_stats(RNDSTAT[ran]);
 
   set_skill(SS_WEP_SWORD, SKILLCOM[ran3]);
   set_skill(SS_WEP_KNIFE, SKILLCOM[ran3]);
   set_skill(SS_WEP_POLEARM, SKILLCOM[ran3]);
   set_skill(SS_WEP_CLUB, SKILLCOM[ran3]);
   set_skill(SS_DEFENCE, SKILLDEF[ran3]);
   set_skill(SS_PARRY, SKILLDEF[ran3]);

   clone_tobacco();
 
   set_chat_time(16+ran);
   add_chat("My husband doesn't like outsiders.");
   add_chat("How are you today?");
   add_chat("All I do is cook, clean, sew, wash, and mind the lads.");
   add_chat("I make some of the best tea.");
   add_chat("Have you been to Hobbiton?");
   add_chat("My uncle once was on a grand adventure. He never came back.");
   add_chat("I learned a good bit about cooking from my mother.");
   add_chat("The best thing about the rain is the beauty it brings.");
   add_chat("My children enjoyed last year's fair at the White Downs.");
   add_chat("I cook six meals a day for my family.");
   add_chat("Do you know my husband?");

   set_act_time(16 - ran);
   add_act("hug hobbits");
   add_act("pat all");
   add_act("smile tiredly");
   add_act("giggle merr");

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

      ran = random(14);
      ran2 = random(10);

      weap = clone_object(ER_DIR +"wep/" +RNDWEP[ran]);
      weap->move(TO,1);
      armo = clone_object(ER_DIR +"arm/" +RNDARM[ran2]);
      armo->move(TO,1);
      armo = clone_object(ER_DIR +"arm/" +"hat");
      armo->move(TO,1);
      TO->command("wear all");
}

 
public void
attacked_by(object ob)
{ 

    if (!ob->query_prop("_i_kill_hobbits_"))
      ob->add_prop("_i_kill_hobbits_",1);
      command("shout Help! This " + ob->query_race_name() + " wants to kill me!");
      command("wield all");
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

