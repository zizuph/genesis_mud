inherit "/std/monster";

#include "default.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

void
create_monster()
{
   set_name("hermit");
   set_living_name("_mylos_hermit_");
   set_race_name("human");
   set_short("hermit");
   set_long(break_string("This crazy human is dressed in the most weird "+
         "fashion, with all types of rags that were available. He looks "+
         "like he is mad.\n",76));
   
   set_base_stat(SS_STR, 30);
   set_base_stat(SS_DEX, 23);
   set_base_stat(SS_CON, 29);
   set_base_stat(SS_INT, 9);
   set_base_stat(SS_WIS, 8);
   set_base_stat(SS_DIS, 30);
   
   set_skill(SS_DEFENCE, 25);
   set_skill(SS_PARRY, 22);
   set_skill(SS_UNARM_COMBAT, 30);
   set_skill(SS_ELEMENT_LIFE, 40);
   set_skill(SS_AWARENESS, 45);
   
   set_hp(250);
   
   add_prop(OBJ_I_WEIGHT, 14000);
   add_prop(CONT_I_MAX_WEIGHT, 120000);
   add_prop(OBJ_I_VOLUME, 89000);
   add_prop(CONT_I_MAX_VOLUME, 100000);
   add_prop(OBJ_S_WIZINFO, "/dThis hermit is mad, totally. He will however, "+
      "help the player who gives him something to eat, preferably "+
      "one of the rats or even a corpse of a rat.\n");
   
   set_chat_time(10);                             /* Set speaking interval */
   add_chat("Get away from me!");
   add_chat("Who am I to tell people things?"); 
   add_chat("The sky disappeared that day...");
   add_chat("The bell was ringing a lot that day...");
   add_chat("They came from the sky...");
   add_chat("Mushrooms are good for you, you know!");
   add_chat("You don't need teeth, youngster!");
   
   set_cchat_time(4);                      /* Set combat speaking interval */
   add_cchat("What are you doing?");            /* The usual combat talk */
   add_cchat("Pain, pain afflicts me not.");
   
   set_act_time(10);                    /* Set action interval           */
   add_act("smile");  
   add_act("ponder");
   add_act("sigh");
   
   add_ask( ({ "monk", "about monk", "how do i help monk",
            "How do I help monk" }),
      VBFC_ME("ask_monk"));
   add_ask( ({ "quest", "about quest", "challenge", "about challenge",
            "what is the quest", "what is the challenge" }),
      VBFC_ME("ask_quest"));
   trig_new("%w 'smiles.\n' %s", "react_smile");
   trig_new("%w 'smiles' %s", "react_smile");
   trig_new("%w 'growls' %s", "react_growl");
   trig_new("%w 'growls.\n' %s", "react_growl");
   trig_new("%w 'introduces' %s", "react_introduce");
   trig_new("%w 'shakes' %w 'head' %s", "react_shake");
   trig_new("%w 'giggles' %s", "react_giggle");
   trig_new("%w 'bows' %s", "react_bow");
   trig_new("%w 'swears' 'loudly.\n' %s", "react_swear");
   call_out("arm_me", 1);
}

int
react_smile(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      call_out("return_smile", 3, who);
      return 1;
   }
}

void
return_smile(string who) {
   object obj;
   int ran;
   
   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Life is great, isn't it, " + obj->query_nonmet_name()
         + "?");
      if (ran == 1)
         command("smile at " + who);
      if (ran == 2)
         command("say It is great to see you smiling, " +
         obj->query_nonmet_name()
         + ".");
   }
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
react_shake(string who, string dummy1, string dummy2) {
   if (who) {
      who = lower_case(who);
      call_out("return_shake", 3, who);
      return 1;
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
         command("say I agree with you, "
         + ((obj->query_gender() == G_MALE) ? "master" : "lady") + ".");
      if (ran == 2)
         command("say Why do " + LANG_PWORD(obj->query_race())
         + " always disagree?");
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

string
ask_monk()
{
   return break_string("The monk was a member of this order, destroyed "+
      "by the magi. He wanders this place as I do, but he is stuck in "+
      "Limbo, a wraith of his former self. If you can help him to find "+
      "rest, then you will be rewarded by the Gods, I swear. But be "+
      "careful, a monks grave is as humble as his attitude.\n", 76);
}

string
ask_quest()
{
   if (this_player()->query_stat(SS_STR) < 20)
      return "You would not be strong enough for that.\n";
   return break_string("You must find the spectre of a monk, and return "+
      "him to his proper resting place, where his body lieth. He will "+
      "not harm thee unless you harm him, there is nothing to be "+
      "frightened of. Somewhere in this accursed castle, the crypts lie, "+
      "but there is no-one with the knowledge of them anymore, not even I "+
      "remember, and the scripts at our Motherhouse were destroyed.\n", 76);
}
