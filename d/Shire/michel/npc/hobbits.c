/* This file generates a random good hobbit.  */
/* designed for Michel Delving                */
 
inherit "/std/monster";
 
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>
#include "/d/Shire/common/defs.h"
#include "/d/Shire/common/monster/tobacco.h"
#include "/d/Shire/common/make_money.h";
/*
 * Removed by Elessar, to avoid the redeclaration problem with the new GD.
 * Jan 19th 1995.
#include "/d/Shire/prestige.h"
*/
 
/* These are random guards descriptions */
#define RNDADJ ({"fat","old","young","drunk","greedy","funny"})
#define SECADJ ({\
     "blue-eyed","dark-eyed","green-eyed",\
     "grey-eyed","black-eyed","merry-eyed"})
#define RNDLONG ({\
   "This is a lazy fat hobbit.\n" + \
   "He likes to eat much and sleep long. He can defend himself \n" + \
   "well though. His fists are big enough to make you hurt. \n", \
   "This hobbit lived long in this world. \n" + \
   "He looks respected and well off. His hair and beard is \n" + \
   "white like snow. \n", \
   "This is a young hobbit. He is less than 30 years old. \n" + \
   "He enjoys life walking around his beloved country.\n" + \
   "He is very curious and adventuring a lot. \n", \
   "This hobbit like he is overdrunk a bit. \n" + \
   "You think he is returnig from a party or a local pub.\n" + \
   "His steps are unfirm and quite random. \n", \
   "This hobbit is as greedy as the most gnomes are. \n" + \
   "He spent his life raising his richies and filling\n" + \
   "his small hole with coins and goods. \n", \
   "This hobbit lad wears fancy clothes and thinks he is the best.\n" + \
   "He walks around the village chatting and smiling.\n" + \
   "He is young and cute. \n"})
 
/* These are random stats for the hobbits */
#define RNDSTAT ({\
                   ({40,35,40,15,15,15}),\
                   ({25,50,35,15,15,15}),\
                   ({35,45,30,15,15,15}),\
                   ({30,30,40,15,15,15}),\
                   ({30,45,30,15,15,15}),\
                   ({25,35,25,15,15,15})})
 
/* This is a random equipment for hobbits */
#define RNDW ({"h_flail","stick","h_dagger","h_pole"})
#define RNDA ({"h_robe","h_coat","h_cloak","h_cap"})
/* These are random combat and defence skills for hobbits */
#define SKILLUN ({35,11,11,20,15,25})
#define SKILLCOM ({5,19,33,29,15,15})
#define SKILLDEF ({29,19,25,19,36,22})
 
//   Prototypes
void arm_me();


void
create_monster() {
   int ran;
   int rnd;
   if (!IS_CLONE)
      return;
   rnd = random(6);
   ran = random(6);
   set_pname("hobbits");
   set_short(SECADJ[rnd] +" "+ RNDADJ[ran] + " hobbit");
   set_race_name("hobbit");
   set_adj(({SECADJ[rnd],RNDADJ[ran]}));
   set_alignment(100 + random(100));
   set_long(RNDLONG[ran]);
   add_prop(CONT_I_WEIGHT,30000);
   add_prop(CONT_I_HEIGHT,500);
   add_prop(LIVE_I_NEVERKNOWN,1);
 
   set_stats(RNDSTAT[ran]);
   add_ask(({"party","rony","last party"}),VBFC_ME("info"));
 
   set_skill(SS_UNARM_COMBAT, SKILLUN[ran]);
   set_skill(SS_WEP_KNIFE, SKILLCOM[ran]);
   set_skill(SS_WEP_POLEARM, SKILLCOM[ran]);
   set_skill(SS_WEP_CLUB, SKILLCOM[ran]);
   set_skill(SS_DEFENCE, SKILLDEF[ran]);
   set_skill(SS_PARRY, SKILLDEF[ran]);
   set_skill(SS_HIDE, SKILLDEF[ran]);
   clone_tobacco();
 
   set_chat_time(9+ran);
   add_chat("Lovely day, isnt it?");
   add_chat("Our tobacco is the best all over the MiddleEarth!.");
   add_chat("I am scared of orcs!");
   add_chat("The beer is really tasty this year!");
   add_chat("Help us to kill those orcs!");
   add_chat("Michel Delving is the best place in the world.");
   add_chat("Be careful, some folks saw strangers nearby!");
   add_chat("I like elvish songs.");
   add_chat("Have you seen our garden?");
   add_chat("Our pond is famous among all hobbits!\n");
 
   set_cchat_time(9);
   add_cchat("Help ! ! !");
   add_cchat("Guards ! Where are they?");
   add_cchat("I hope Gandalf will cast you into the void one day!");
   add_cchat("I am poor and don't have a coin, leave me alone!.");
   add_cchat("The Mayor must hire some dwarves to protect us!.");
 
   set_cact_time(5);
   add_cact(({"cry","scream","slap all","explode","spit"}));
   add_cact("shout Help! Murder!");
 
   set_alarm(0.1,0.0,&arm_me());
   MAKE_MONEY;
   set_random_move(50);
   set_restrain_path(({MICH_DIR,"/d/Shire/common"}));
}
/* Here I give my hobbits some stuff */
arm_me()
{  int ran;
   object eq;
   ran = random(4);
   eq = clone_object(MICH_DIR +"wep/" +RNDW[ran]);
   eq->move(this_object());
   this_object()->command("wield all");
   ran = random(4);
   eq = clone_object(MICH_DIR +"arm/" +RNDA[ran]);
   eq->move(this_object());
   this_object()->command("wear all");
}
 
public void
attacked_by(object ob)
{ ::attacked_by(ob);
    if (!ob->query_prop("_i_kill_hobbits_"))
    ob->add_prop("_i_kill_hobbits_",1);
    command("shout Help! This " + ob->query_race() + " wants to kill me!");
 
}
string info()
{
   command("thing last night party");
   command("say There was a birthday party last night in our village!");
   command("say Most of local hobbits were at the pond and me too");
   command("say We had a nice feast there - a lots of drinks and huge" +
                   " baskets with snacks!");
   command("say I enjoyed singing near the campfire.");
   command("thing favourite meat pies and ale");
   command("say Our Rony was so drunk that he barely succes to swim in "+
                            "the pond.");
   command("chuckle");
   return "";
}
query_knight_prestige() { return(-9); }
