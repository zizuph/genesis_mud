// This file is wehobbit.c, used as a master hobbit file for the weaker bunch
// of hobbits -> possibly in the east farthing.
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

#define RNDADJ ({"friendly","small","rotund","fat","sturdy","chatty",\
  "curly-haired","ruddy-faced"})
//  "curly-haired","blue-eyed"})
#define RNDADJ2 ({"brown-haired","clumsy","middle-aged","jolly","sickly","fit",\
   "bouncy","blue-eyed"})
//   "bouncy","ruddy-faced"})
#define RNDLONG ({"This friendly hobbit "+\
"looks at you with smiling eyes.\n",\
"This small hobbit hardly comes up to his "+\
   "own knees, much less yours.\n",\
   "This rotund hobbit is not a stranger to the table.\n",\
   "This fat hobbit can barely see his toes.\n",\
   "This sturdy hobbit looks like a good worker.\n",\
   "This chatty hobbit always has something to say.\n",\
   "This curly-haired hobbit constantly examines his hair.\n",\
"This ruddy-faced hobbit has cheeks which are "+\
   "the color of beets.\n"})
 
/* These are random stats for the guards */
#define RNDSTAT ({\
                   ({35,55,35,10,27,38}),\
                   ({32,55,39,14,22,34}),\
                   ({36,50,37,15,25,30}),\
                   ({32,55,39,11,21,35}),\
                   ({32,55,39,12,23,25}),\
                   ({32,55,39,15,26,29}),\
                   ({33,52,31,23,23,37}),\
                   ({37,50,39,13,27,30})})
 
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
   set_alignment(140 + ran);
   set_long(RNDLONG[ran]);
   if (ran == 1)
      set_size_descs("very short", "lean");
   else if (ran == 2)
      set_size_descs("of normal length", "plump");
   else if (ran == 3)
      set_size_descs("of normal length", "fat");
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
   add_chat("Strange things go on in the West Farthing.");
   add_chat("How are you today?");
   add_chat("Sometimes I long for a look at the sea.");
   add_chat("I'd love a beer right about now!");
   add_chat("Have you been to Buckland?");
   add_chat("My parents come from Staddle.");
   add_chat("My great-great-grandfather was Mayor, a long time ago.");
   add_chat("The only good to come out of the North Farthing is tobacco.");
   add_chat("I think I saw an elf, over by Woody End.");
   add_chat("Dwarves are so blasted obstinate, at least I think so.");
   add_chat("Do I know you?");

   set_act_time(16 - ran);
   add_act("tap");
   add_act("sing");
   add_act("whistle aim");
   add_act("smile misc");

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
