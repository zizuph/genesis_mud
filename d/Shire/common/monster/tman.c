/*
* An old man sitting by the road, minding his own business (mostly)
* Cloned by ~Shire/common/gondorlink
*/

inherit "/std/monster";

#include "defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/language.h"


//    Prototypes
void return_smile(string who);
void return_smirk(string who);
void return_sigh(string who);
void return_nod(string who);
void return_grin(string who);
void return_giggle(string who);
void return_frown(string who);
void return_bow(string who);
void return_growl(string who);
void return_wave(string who);
void return_shrug(string who);
void return_spit(string who);
void return_cackle(string who);
void return_laugh(string who);
void return_shake(string who);
void return_clone(string who);
void return_Call(string who);
void arm_me();

int tied_up;

void
create_monster()
{
   seteuid(getuid());
   if (!IS_CLONE)
      return;
   
   set_name("old man");
   add_name(({"_old_man_","human"}));
   set_adj("old");
   set_race_name("human"); 
   set_long(break_string("The old man is sitting on the log looking at the "
         + "people travelling this road.\n",70));
   
   add_prop(CONT_I_WEIGHT,102000);  /* 102 Kg */
   add_prop(CONT_I_HEIGHT,183);     /* 183 cm */
   
   /* STR DEX CON INT WIS DIS */
   set_stats(({ 13, 6, 27, 41, 55, 5}));
   set_hp(10000); /* Heal fully */
   set_pick_up(75);
   set_skill(SS_UNARM_COMBAT,20);
   set_skill(SS_DEFENCE,20);
   set_skill(SS_WEP_CLUB, 20);
   
   /* Actions */
   set_act_time(5);
   add_act("sigh");
   add_act("sniff");
   add_act("sit on bench");
   add_act("stand");
   
   set_chat_time(5);
   add_chat("Nice weather we have here.");
   add_chat("Are you going south?");
   add_chat("There are lots of dangerous things to the south!");
   
   /* Combat chat-strings */
   set_cchat_time(5);
   add_cchat("Don't beat me, please!");
   add_cchat("Haven't I suffered enough?");
   add_cchat("Why do you beat an old man like this?");
   
   add_prop(LIVE_I_NEVERKNOWN, 1); /* You never get to meet him */
   
   /* Triggers */
   trig_new("%s 'south.' %s", "react_south");
   trig_new("%w 'fetches' 'something' 'from' 'another' 'dimension.\n' %s",
      "react_clone");
   trig_new("%w 'patched' 'the' 'internals' 'of' %s", "react_Call");
   
   set_alarm(1.0,0.0,&arm_me());
}

void
react_south()
{
   command("shout Don't go that way. It's dangerous.");
}

void
arm_me()
{
   object cane,boots;
   
   cane = clone_object(STAND_WEAPON + "cane");
   boots = clone_object(STAND_ARMOUR + "boots");
   cane->move(this_object());
   boots->move(this_object());
   
   cane->set_long("This is a wooden cane used by the old man by the roadside\n"
      + "to support him when he walks.\n");
   
   command("wield cane");
   command("wear boots");
}



/********************************************************************
*
*  Some feelings to make the old chap more vivid.
*  The feelings are split in two parts: the part that is called by
*  a trigger function, and a part that is called after a random time.
*  This is done to get a feeling of reality in the game.
*/

void
return_sigh(string who)
{
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Dangerous things to the south depress me too, "
         + obj->query_nonmet_name()
         + "?");
      if (ran == 1)
         command("comfort " + who);
      if (ran == 2)
         command("say Is life tough for you, " + obj->query_nonmet_name()
         + "?");
   }
}

void
return_smile(string who) {
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say It is good to see someone smile once in a while.");
      if (ran == 1)
         command("smile at " + who);
      if (ran == 2)
         command("say You will not be smiling if you go south from here, "
         + ((obj->query_gender() == G_MALE) ? "master" : "lady") + ".");
   }
}

void
return_smirk(string who) {
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Sha, right...");
      if (ran == 1)
         command("smirk");
      if (ran == 2)
         command("grin at " + who);
   }
}

void
return_grin(string who) {
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say What are you grinning about, "
         + ((obj->query_gender() == G_MALE) ? "master" : "lady")
         + "?");
      if (ran == 1)
         command("grin");
      if (ran == 2)
         command("say Hehehe...");
   }
}

void
add_introduced(string who)
{
   object obj;
   
   if (obj = present(who, environment()))
      {
      switch(random(3))
      {
         case 0:
         command("say Nice to meet you, " + capitalize(who) + ".");
         command("bow to " + who);
         command("shake " + who);
         return;
         
         case 1:
         command("bow to " + who);
         command("shake " + who);
         command("smile at " + who);
         return;
         
         case 2:
         default:
         command("say Hi there, " + obj->query_race() + ".");
         command("bow to " + who);
         return;
       }
   }
}

void
return_nod(string who) {
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say I could not agree more, "
         + ((obj->query_gender() == G_MALE) ? "master" : "lady") + ".");
      if (ran == 1)
         command("pat " + who);
      command("smile at " + who);
      if (ran == 2)
         command("say Indeed, " + obj->query_race() + ".");
   }
}

void
return_shake(string who) {
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say So you disagree, " + obj->query_race() + "?");
      if (ran == 1)
         command("say In a way, you are right, "
         + ((obj->query_gender() == G_MALE) ? "master" : "lady") + ".");
      if (ran == 2)
         command("say Why do " + LANG_PWORD(obj->query_race())
         + " always disagree?");
   }
}

void
return_laugh(string who) {
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Laugh while you still can; visit the south and you won't");
      if (ran == 1)
         command("laugh");
      if (ran == 2)
         command("cackle");
   }
}

void
return_growl(string who) {
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say You frighten me with your growling, " + obj->query_race()
         + "...");
      if (ran == 1)
         command("say Have I said anything wrong, "
         + ((obj->query_gender() == G_MALE) ? "master" : "lady") + "?");
      if (ran == 2)
         command("frown");
   }
}

void
return_cackle(string who) {
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say You quack like a duck, "
         + ((obj->query_gender() == G_MALE) ? "master" : "lady") + ".");
      if (ran == 1)
         command("say " + capitalize(LANG_PWORD(obj->query_race()))
         + " cackle very often.");
      if (ran == 2)
         command("giggle");
   }
}

void
return_shrug(string who) {
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Is there anything you " + LANG_PWORD(obj->query_race())
         + " do know?");
      if (ran == 1)
         command("say Don't look at me... I don't know either!");
      if (ran == 2)
         command("shrug");
   }
}

void
return_bow(string who) {
   command("bow " + who);
}

void
return_wave(string who) {
   command("wave");
   command("say Bye bye.");
}

void
return_frown(string who) {
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Is something wrong, " + obj->query_race());
      if (ran == 1)
         command("say It wasn't my fault!");
      if (ran == 2)
         command("say The perilous south makes me frown as well...");
   }
}

void
return_spit(string *arr) {
   string who, where;
   object obj;
   int ran;
   
   who = arr[0];
   where = arr[1];
   if (obj = present(who, environment())) {
      ran = random(4);
      if (ran == 0)
         {
         command("sigh");
         command("say " + capitalize(LANG_PWORD(obj->query_race()))
            + " and spitting, inseparable...");
       }
      if (ran == 1)
         command("say Some people consider spitting to be indecent.");
      if (ran == 2)
         command("say Why do you spit " + where + "?");
      if (ran == 3)
         command("say " + capitalize(LANG_PWORD(obj->query_race()))
         + " are such rude people!");
   }
}

return_giggle(string who) {
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Giggling becomes you, "
         + ((obj->query_gender() == G_MALE) ? "master" : "lady") + ".");
      if (ran == 1)
         command("say Ah, " + LANG_PWORD(obj->query_race())
         + " are so merry.");
      if (ran == 2)
         command("giggle");
   }
}


int
react_clone(string who, string dummy1) {
   if (who) {
      who = lower_case(who);
      set_alarm(3.0,0.0,&return_clone(who));
      write("who = "+who+"\nDummy = "+dummy1+"\n");
      return 1;
   }
}

return_clone(string who) {
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("gasp");
      if (ran == 1)
         if (ran == 1)
         {
         command("say Such awesome display of power!");
         command("grovel " + who);
       }
      if (ran == 2)
         {
         command("say Honour to the great "
            + obj->query_race() + " conjurer!");
         command("grovel " + who);
       }
   }
}

int
react_Call(string who, string dummy1) {
   if (who) {
      who = lower_case(who);
      set_alarm(3.0,0.0,&return_Call(who));
      return 1;
   }
}

return_Call(string who) {
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         {
         command("grovel " + who);
         command("say Please leave me in one piece, mighty "
            + obj->query_race() + " wizard!");
         command("shiver");
       }
      if (ran == 1)
         {
         command("say Hail to the mighty one!");
         command("grovel " + who);
       }
      if (ran == 2)
         command("gasp");
   }
}


/* For the solamnic Knights */

void
emote_hook(string emote, object actor, string adverb = 0)
{
   string name = actor->query_real_name();
   switch(emote)
   {
      case "smile":
      set_alarm(3.0,0.0,&return_smile(name));
      break;
      case "smirk":
      set_alarm(3.0,0.0,&return_smirk(name));
      break;
      case "sigh":
      set_alarm(3.0,0.0,&return_sigh(name));
      break;
      case "nod":
      set_alarm(3.0,0.0,&return_nod(name));
      break;
      case "grin":
      set_alarm(3.0,0.0,&return_grin(name));
      break;
      case "giggle":
      set_alarm(3.0,0.0,&return_giggle(name));
      break;
      case "frown":
      set_alarm(3.0,0.0,&return_frown(name));
      break;
      case "bow":
      set_alarm(3.0,0.0,&return_bow(name));
      break;
      case "growl":
      set_alarm(3.0,0.0,&return_growl(name));
      break;
      case "wave":
      set_alarm(3.0,0.0,&return_wave(name));
      break;
      case "shrug":
      set_alarm(3.0,0.0,&return_shrug(name));
      break;
      case "spit":
      set_alarm(3.0,0.0,&return_spit(name));
      break;
      case "cackle":
      set_alarm(3.0,0.0,&return_cackle(name));
      break;
      case "laugh":
      set_alarm(3.0,0.0,&return_laugh(name));
      break;
      case "shake":
      set_alarm(3.0,0.0,&return_shake(name));
      break;
   }
}

query_knight_prestige() { return(-2); }
