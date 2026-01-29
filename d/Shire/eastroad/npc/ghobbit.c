// This file is ghobbit.c, used as a master hobbit file for the middle bunch
// of hobbits in the West Farthing :).
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
/* These are random guards descriptions */

#define RNDADJ ({"tall","energetic","boisterous","short","sweet","talkative",\
  "curious","sleepy"})
//  "curious","passive"})
#define RNDADJ2 ({"chubby","agile","young","jolly","hungry","drunken",\
   "silly","passive"})
//   "silly","sleepy"})
#define RNDLONG ({"This tall hobbit - well, tall is a relative term, "+\
"looks at you with active, searching eyes.\n",\
"This energetic hobbit seems to be bouncing off "+\
   "the walls.\n",\
   "This boisterous hobbit looks completely irrepressible.\n",\
   "This short hobbit looks up at you with wide eyes.\n",\
   "This hobbit looks so sweet and kind- he couldn't harm a fly!\n",\
   "This talkative hobbit seems to never close his jaws.\n",\
   "This curious hobbit looks at you in amazement.\n",\
"This sleepy hobbit has one eye fully closed and the other "+\
   "is almost closed as well.\n"})
 
/* These are random stats for the guards */
#define RNDSTAT ({\
                   ({47,63,45,22,27,48}),\
                   ({49,58,49,24,22,44}),\
                   ({36,70,47,15,25,40}),\
                   ({37,55,49,11,21,45}),\
                   ({48,59,41,12,23,35}),\
                   ({52,65,45,15,26,49}),\
                   ({43,63,31,23,23,37}),\
                   ({37,55,45,13,27,40})})

/* These are the sizes for the hobbits. Silly system... */
#define RNDHEIGHT ({\
                "tall",\
                "of normal length",\
                "of normal length",\
                "short",\
                "of normal length",\
                "of normal length",\
                "of normal length",\
                "of normal length"})

#define RNDWIDTH ({\
                "fat",\
                "lean",\
                "lean",\
                "of normal width",\
                "of normal width",\
                "of normal width",\
                "of normal width",\
                "of normal width"})
 
/* These is random equipment for guards */
#define RNDWEP ({"h_dagger","h_pole","h_spear","h_flail",\
    "cknife","dbaxe","pitchfork","rapier","sgauche","hatchet","hickclub",\
    "ironclub","shortsword","shovel"})
#define RNDARM ({"h_shirt","h_robe","h_tunic","h_cloak",\
     "coat","hat","leggings","lshirt","pants","scloak"})
/* These are random combat and defence skills for guards */
#define SKILLCOM ({75,64,60,61,59})
#define SKILLDEF ({65,45,53,65,76})
int not_intro, alarm_id;
int intro_alarm, reintro_alarm;

void introduce_me();
void re_intro();

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

   set_pname("hobbits");
   set_race_name("hobbit");
   set_adj(RNDADJ[ran]);
   add_adj(RNDADJ2[ran2]);
   set_size_descs(RNDHEIGHT[ran], RNDWIDTH[ran2]);
   set_alignment(302 + ran);
   set_long(RNDLONG[ran]);
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
   add_chat("I don't like outsiders much.");
   add_chat("How are you today?");
   add_chat("It is supposed to rain tomorrow, I think.");
   add_chat("I love to drink ale and wine.");
   add_chat("Have you been to Whitfurrows?");
   add_chat("I have been on many adventures.");
   add_chat("My wife is an excellent cook.");
   add_chat("The only good to come out of the South Farthing is tobacco.");
   add_chat("I had a wonderful time at the party last night.");
   add_chat("I missed lunch today- can you believe it?");
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
      command("shout I'll make this " + ob->query_race_name() + " regret it!");
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
