// This file is mhobbit.c, used as a master hobbit file for the top bunch
// of hobbits in the Shire :).
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
#include "names.h"

/* These are random guards descriptions */

#define RNDADJ ({"long-armed","stout","sturdy","stoic","proud","haughty",\
  "strong","eager"})
#define RNDADJ2 ({"merry","good-natured","slim","smiling","aging","happy",\
   "joking","bouncy"})
#define RNDLONG ({"This long-armed hobbit seems to "+\
"have a good reach with any weapon.\n",\
"This stout hobbit has solid muscle on his "+\
   "bones.\n",\
   "This sturdy hobbit looks really tough.\n",\
   "This stoic hobbit seems like he can take anything.\n",\
   "The proud hobbit acts as if he can take on the world alone!\n",\
   "This haughty hobbit seems above the likes of you.\n",\
   "This strong hobbit could easily lift you over his head.\n",\
"This eager hobbit is ready "+\
   "for action.\n"})
 
/* These are random stats for the guards */
#define RNDSTAT ({\
                   ({67,73,65,42,37,58}),\
                   ({49,68,59,34,32,54}),\
                   ({36,80,57,45,35,50}),\
                   ({37,65,59,31,31,55}),\
                   ({48,69,61,42,33,55}),\
                   ({52,75,55,35,46,59}),\
                   ({93,83,61,33,33,57}),\
                   ({37,75,65,33,37,50})})
 
/* These is random equipment for guards */
#define RNDWEP ({"h_dagger","h_pole","h_spear","h_flail",\
    "cknife","dbaxe","pitchfork","rapier","sgauche","hatchet","hickclub",\
    "ironclub","shortsword","shovel"})
#define RNDARM ({"h_shirt","h_robe","h_tunic","h_cloak",\
     "coat","hat","leggings","lshirt","pants","scloak"})
/* These are random combat and defence skills for guards */
#define SKILLCOM ({55,64,50,51,59})
#define SKILLDEF ({54,35,53,65,46})

int alarm_id;
int intro_alarm;
int reintro_alarm;
int not_intro;

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
   ranname = random(77);
   ranfam = random(30);

   set_name(MALENAME[ranname]);
   add_name("villager");
   set_title(FAMILYNAME[ranfam]);
   set_pname("hobbits");
   set_race_name("hobbit");
   set_adj(RNDADJ[ran]);
   add_adj(RNDADJ2[ran2]);
   set_alignment(370 + ran);
   set_long(RNDLONG[ran]);
   if (ran2 == 2)
        set_size_descs("of normal length", "skinny");
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
   add_chat("I don't like outsiders much.");
   add_chat("How are you today?");
   add_chat("Just let me at those accursed orcs, I'll teach them.");
   add_chat("At night, there's nothing so comfortable as a fire.");
   add_chat("Have you been to Greenfields?");
   add_chat("I have been on many adventures.");
   add_chat("My friends back me up on my adventures.");
   add_chat("The only good to come out of the South Farthing is tobacco.");
   add_chat("I drank too much at the party last night.");
   add_chat("I could sure use my dinner right about now.");
   add_chat("Do I know you?");

   set_act_time(16 - ran);
   add_act("stare");
   add_act("emote smiles grimly.");
   add_act("think");
   add_act("grin");

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
    command("cheer");
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
    remove_alarm(intro_alarm);
    command("introduce myself");
    not_intro = 1;
    if (!reintro_alarm)
        reintro_alarm = set_alarm(15.0, 0.0, &re_intro());
}

void
re_intro()
{
    remove_alarm(reintro_alarm);
    not_intro = 0;
}

