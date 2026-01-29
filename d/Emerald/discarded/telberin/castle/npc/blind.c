inherit "/std/monster";

#include "default.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

void
create_monster()
{
   set_name("elf");
   add_name("blind");
   set_living_name("_blind_man_");
   set_adj("blind");
   set_race_name("elf");
   set_short("blind elf");
   set_long("This old man is blind, the whites of his eyes stand out. He " +
            "doesn't look decrepit though.\n");
   
   set_base_stat(SS_STR, 30);
   set_base_stat(SS_DEX, 23);
   set_base_stat(SS_CON, 29);
   set_base_stat(SS_INT, 9);
   set_base_stat(SS_WIS, 8);
   set_base_stat(SS_DIS, 30);
   
   set_skill(SS_DEFENCE, 25);
   set_skill(SS_PARRY, 22);
   set_skill(SS_WEP_POLEARM, 15);
   set_skill(SS_ELEMENT_LIFE, 40);
   set_skill(SS_AWARENESS, 45);
   set_alignment(600);
   
   set_hp(250);
   
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   add_prop(OBJ_I_WEIGHT, 14000);
   add_prop(CONT_I_MAX_WEIGHT, 120000);
   add_prop(OBJ_I_VOLUME, 89000);
   add_prop(CONT_I_MAX_VOLUME, 100000);
   add_prop(OBJ_S_WIZINFO, "/tThis blind man is used for the Royalty quest "+
      "to give the players some clues, especially for the part3 of the "+
        "quest on level three of the castle.\n");
   
   set_chat_time(10);                             /* Set speaking interval */
   add_chat("It was many years ago when the old King and Queen died.");
   add_chat("Have you looked around the castle?"); /* A bit of random chat */
   add_chat("Faerie is far away, sure you want to go there?");
   add_chat("I remember the good old days.");
   add_chat("Do you know what's up in the castle?");
   add_chat("I was young and proud once.");
   add_chat("The politics of the court are difficult to understand.");
   
   set_cchat_time(4);                      /* Set combat speaking interval */
   add_cchat("Stop this madness! Leave me alone!");            /* The usual 
   combat talk */
   add_cchat("Don't do this to an old blind elf!");
   
   set_act_time(10);                    /* Set action interval           */
   add_act("smile");              /* A few courteous actions       */
   add_act("daydream");
   add_act("sigh");
   add_act("hmm");
   
   add_ask( ({ "royalty", "king", "queen", "King", "Queen",
            "about king","about queen","about King","about Queen",
            "about royalty", "how do i enter castle", 
            "How do I enter castle" }),VBFC_ME("ask_royalty"));
   add_ask( ({ "quest", "about quest", "book", "about book", 
            "challenge", "about challenge",
            "what is the quest", "what is the challenge" }),
      VBFC_ME("ask_quest"));
   add_ask( ({"faerie", "about faerie", "Faerie", "About Faerie" }),
	VBFC_ME("ask_faerie"));
   
   set_default_answer("Sorry, I don't know about that.\n");
   trig_new("%w 'smiles.\n' %s", "react_smile");
   trig_new("%w 'smiles' %s", "react_smile");
   trig_new("%w 'growls' %s", "react_growl");
   trig_new("%w 'growls.\n' %s", "react_growl");
   trig_new("%w 'introduces' %s", "react_introduce");
   trig_new("%w 'shakes' %w 'head' %s", "react_shake");
   trig_new("%w 'giggles' %s", "react_giggle");
   trig_new("%w 'bows' %s", "react_bow");
   trig_new("%w 'sighs' %s", "react_sigh");
   trig_new("%w 'swears' 'loudly.\n' %s", "react_swear");
   call_out("arm_me", 1);
}

int
react_introduce(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      return 1;
   }
}

void
return_introduce(string who) {
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         {
         command("say Nice to meet you, " + obj->query_name() + ".");
         command("bow to " + who);
       }
      if (ran == 1)
         {
         command("bow to " + who);
       }
      if (ran == 2)
         {
         command("say Be welcome, " + obj->query_race() + ".");
         command("bow to " + who);
       }
   }
}

int
react_giggle(string who, string dummy1) {
   if (who) {
      who = lower_case(who);
      call_out("return_giggle", 3, who);
      return 1;
   }
}

return_giggle(string who) {
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Funny, eh " + obj->query_race() + "?");
      if (ran == 1)
         command("say Ah, " + LANG_PWORD(obj->query_race())
         + " are such merry people.");
      if (ran == 2)
         command("giggle");
   }
}

int
react_swear(string who, string dummy)
{
   if (who)
      {
      who = lower_case(who);
      call_out("return_swear", 3, who);
      return 1;
   }
}
void
return_swear(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      ran = random(3);
      if(ran == 0)
         command("say Don't swear in front of young "+
         (obj->query_gender() ? "woman" : "man") +"!");
      if(ran == 1)
         command("eyebrow " +who);
      if(ran == 2)
         command("growl "+who);
   }
}

int
react_growl(string who, string dummy)
{
   if (who) {
      who = lower_case(who);
      call_out("return_growl", 3, who);
      return 1;
   }
}

void
return_growl(string who) {
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say You make me uneasy with your growling, " + 
         obj->query_race()+ "...");
      if (ran == 1)
         command("say Why so hostile, " + obj->query_race() + "?");
      if (ran == 2)
         command("eyebrow");
   }
}
int
react_sigh(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      call_out("return_sigh", 3, who);
      return 1;
   }
}

void
return_sigh(string who) {
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Why are you depressed, " + obj->query_nonmet_name()
         + "?");
      if (ran == 1)
         command("comfort " + who);
      if (ran == 2)
         command("say Is life tough for you, " + obj->query_nonmet_name()
         + "?");
   }
}

int
react_bow(string who, string dummy1) {
   if (who) {
      who = lower_case(who);
      call_out("return_bow", 3, who);
      return 1;
   }
}

void
return_bow(string who) {
   command("bow " + who);
}


void
arm_me()
{
   object eq;
   
   eq = clone_object("/d/Emerald/mylos/obj/staff");
   if (eq)
      eq->move(this_object());
   eq = clone_object("/d/Emerald/room/phase/tower/torque");
   if (eq)
      eq->move(this_object());
   command("wield all");
}

string
ask_royalty()
{
   return break_string("The royalty? Ah yes, in the olden days when the "+
      "King and Queen were alive. They died of old age, having "+
      "ruled for many a century. But their children, the prince "+
      "and his bride the princess, weren't able to become the "+
      "rightful King and Queen, for on the King's deathbed, a "+
      "sobbing servant came to tell them that the Book of Ancients "+
      "had been stolen, and so the new crown could not be made. "+
      "The whole Kingdom went into shock, and the King finally "+
      "died of old age. The book has never been seen since, and "+
      "many a brave elf went adventuring to find it in the wilderness, "+
      "never to return. If you can find the book, the whole "+
      "Kingdom would be grateful to you beyond recompense.\n", 76);
}

string
ask_quest()
{
   if (this_player()->query_stat(SS_STR) < 50)
      return "You are not strong enough for the quest.\n";
   if (this_player()->query_skill(SS_CLIMB) < 30)
      return "One of your skills is not good enough.\n";
   return ("The challenge is indeed difficult, for you must "+
      "find the book, which is\nsupposedly ripped into three parts. "+
      "One part of the book was taken\nfrom the city and hidden, "+
      "another part  hidden inside the city,\nand the last was "+
      "supposedly hidden inside the castle somewhere.\nYou must "+
      "alert at all times to the dangers that this quest involves\n"+
      "and think very carefully and act very carefully on "+
      "the actions you take.\nI will give you one clue to the "+
      "whereabouts of one piece of the book:-\n"+
      "\tThe Ruler of Skies,\n\tMust be moved to the Lions mane,\n"+
      "\tNear to the heart of purity,\n\tAll against a field "+
      "of war.\n\nThat should help you a little, I wish you the "+
      "best of luck. You had better be nimble my fine young adventurer, "+
      "because you will be scampering all over the place.\n");
}

string
ask_faerie()
{
   return break_string("Faerie is a long way from here, and I am just an "+
	"old man, who knows nothing about such things.\n", 76);
}

