/*
 *  Meriadoc Brandybuck, better known as Merry
 */

#pragma save_binary

inherit "/std/monster";

#include "defs.h"
#include "/sys/ss_types.h"
#include "/sys/language.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void return_introduce(string who);

create_monster()
{
   if (!IS_CLONE)
      return;

   set_name(({"merry","meriadoc"}));
   set_adj(({"young","merry"}));
   set_title("Brandybuck");
   set_race_name("hobbit"); 
   set_living_name("_merry_");
   set_long("This hobbit is a personal friend of master Frodo Baggins.\n");

   set_alignment(100);
   add_prop(CONT_I_WEIGHT,43000);   /* 40 Kg */
   add_prop(CONT_I_HEIGHT,87);      /* 82 cm */

   set_stats(({ 46, 20, 20, 34, 44, 46}));

   set_hp(10000); /* Heal fully */

   set_chat_time(5);
   add_chat("Hello, friend!");
   add_chat("How are you today?");
   add_chat("Hobbiton is sure busy today.");

   set_cchat_time(5);
   add_cchat("Have I done anything to you?");
   add_cchat("Does this mean we're no longer friends?");
   add_cchat("I don't think I like you anymore!");

   set_aggressive(0);
   set_attack_chance(0);

}

int
add_introduced(string who)
{
   if (who) {
      who = lower_case(who);
      set_alarm(3.0, 0.0, &return_introduce(who));
      return 1;
   }
}


/********************************************************************
 *
 *  Some trigger feelings to make Merry a wee bit more vivid.
 *  The effect is that he will be very annoying (not unlike Harry).
 *  The feelings are split in two parts: the part that is called by
 *  a trigger function, and a part that is called after a random time.
 *  This is done to get a feeling of reality in the game.
 */
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
	 command("introduce myself");
      }
      if (ran == 1)
      {
         command("bow to " + who);
	 command("introduce myself");
      }
      if (ran == 2)
      {
         command("say Welcome to Hobbiton, " + obj->query_race_name() + ".");
         command("bow to " + who);
	 command("introduce myself");
      }
   }
}

void
return_sigh(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Is something wrong, " + obj->query_nonmet_name()
               + "?");
      if (ran == 1)
         command("comfort " + who);
      if (ran == 2)
         command("say So, you're not happy, " + obj->query_nonmet_name()
               + "?");
   }
}

int
react_sigh(string who) {
   if (who) {
      who = lower_case(who);
      set_alarm(3.0, 0.0, &return_sigh(who));
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
         command("smile");
      if (ran == 1)
         command("smile at " + who);
      if (ran == 2)
         command("say A smile a day keeps the alchemist away, "
		+ obj->query_nonmet_name() + ".");
   }
}

int
react_smile(string who) {
   if (who) {
      who = lower_case(who);
      set_alarm(3.0, 0.0, &return_smile(who));
      return 1;
   }
}

void
return_smirk(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say I sense irony, " + obj->query_nonmet_name()
               + "...");
      if (ran == 1)
         command("smirk");
      if (ran == 2)
         command("grin at " + who);
	 command("poke " + who);
   }
}

int
react_smirk(string who) {
   if (who) {
      who = lower_case(who);
      set_alarm(3.0, 0.0, &return_smirk(who));
      return 1;
   }
}

void
return_grin(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say You sound devious, "
                     + ((obj->query_gender() == G_MALE) ? "master" : "lady")
               + "...");
	 command("poke " + who);
      if (ran == 1)
         command("grin");
      if (ran == 2)
         command("say What are you planning, devious "+ obj->query_race() + "?");
   }
}

int
react_grin(string who) {
   if (who) {
      who = lower_case(who);
      set_alarm(3.0, 0.0, &return_grin(who));
      return 1;
   }
}

void
return_nod(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say You are right, "
               + ((obj->query_gender() == G_MALE) ? "master" : "lady") + ".");
      if (ran == 1)
         command("pat " + who);
         command("nod");
      if (ran == 2)
         command("say Agreed, " + obj->query_race() + ".");
   }
}

int
react_nod(string who) {
   if (who) {
      who = lower_case(who);
      set_alarm(3.0, 0.0, &return_nod(who));
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
         command("say No, " + obj->query_race() + "?");
      if (ran == 1)
         command("say I don't think so either, "
               + ((obj->query_gender() == G_MALE) ? "master" : "lady") + ".");
      if (ran == 2)
         command("say Why do " + LANG_PWORD(obj->query_race())
               + " always disagree?");
   }
}

int
react_shake(string who) {
   if (who) {
      who = lower_case(who);
      set_alarm(3.0, 0.0, &return_shake(who));
      return 1;
   }
}

void
return_laugh(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say Witty...");
      if (ran == 1)
         command("laugh");
      if (ran == 2)
         command("giggle");
	 command("poke " + who);
   }
}

int
react_laugh(string who) {
   if (who) {
      who = lower_case(who);
      set_alarm(3.0, 0.0, &return_laugh(who));
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
         command("say Why do " + LANG_PWORD(obj->query_race())
               + "always growl at me?");
      if (ran == 1)
         command("say Why so hostile, " + obj->query_race() + "?");
      if (ran == 2)
         command("frown");
   }
}

int
react_growl(string who) {
   if (who) {
      who = lower_case(who);
      set_alarm(3.0, 0.0, &return_growl(who));
      return 1;
   }
}


void
return_cackle(string who) {
   object obj;
   int ran;

   if (obj = present(who, environment())) {
      ran = random(3);
      if (ran == 0)
         command("say You quack like a duckling, " + obj->query_race() + ".");
      if (ran == 1)
         command("say " + capitalize(LANG_PWORD(obj->query_race()))
               + " are known cacklers.");
      if (ran == 2)
         command("giggle");
   }
}

int
react_cackle(string who) {
   if (who) {
      who = lower_case(who);
      set_alarm(3.0, 0.0, &return_cackle(who));
      return 1;
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

int
react_shrug(string who) {
   if (who) {
      who = lower_case(who);
      set_alarm(3.0, 0.0, &return_shrug(who));
      return 1;
   }
}

void
return_bow(string who) {
   command("bow " + who);
}

int
react_bow(string who) {
   if (who) {
      who = lower_case(who);
      set_alarm(3.0, 0.0, &return_bow(who));
      return 1;
   }
}

void
return_wave(string who) {
   command("wave");
}

int
react_wave(string who) {
   if (who) {
      who = lower_case(who);
      set_alarm(3.0, 0.0, &return_wave(who));
      return 1;
   }
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
         command("frown");
   }
}

int
react_frown(string who) {
   if (who) {
      who = lower_case(who);
      set_alarm(3.0, 0.0, &return_frown(who));
      return 1;
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
         command("say Damn " + LANG_PWORD(obj->query_race()) + "!");
      if (ran == 1)
         command("say Nooo! And I just cleaned the place up!");
         command("growl");
      if (ran == 2)
         command("say Hey! Don't spit there!");
      if (ran == 3)
         command("say " + capitalize(LANG_PWORD(obj->query_race()))
               + " are such rude people!");
   }
}

int
react_spit(string who) {
   string where;
   if (who) {
      who = lower_case(who);
    /*
      if (str[strlen(str)-2] == '.')
         str = str[0..strlen(str)-3];
      else
         str = str[0..strlen(str)-2];
     */
      set_alarm(3.0, 0.0, &return_spit(({who, ""})));
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
               + " are witty.");
      if (ran == 2)
         command("giggle");
   }
}

int
react_giggle(string who) {
   if (who) {
      who = lower_case(who);
      set_alarm(3.0, 0.0, &return_giggle(who));
      return 1;
   }
}

public void
emote_hook(string emote, object who, string adj = 0)
{
    switch(emote)
    {
        case "smile":
            react_smile(who->query_real_name());
            break;
        case "smirk":
            react_smirk(who->query_real_name());
            break;
        case "sigh":
            react_sigh(who->query_real_name());
            break;
        case "nod":
            react_nod(who->query_real_name());
            break;
        case "grin":
            react_grin(who->query_real_name());
            break;
        case "giggle":
            react_giggle(who->query_real_name());
            break;
        case "frown":
            react_frown(who->query_real_name());
            break;
        case "bow":
            react_bow(who->query_real_name());
            break; 
        case "growl":
            react_growl(who->query_real_name());
            break;
        case "wave":
            react_wave(who->query_real_name());
            break;
        case "shrug":
            react_shrug(who->query_real_name());
            break;
        case "spit":
            react_spit(who->query_real_name());
            break;
        case "cackle":
            react_cackle(who->query_real_name());
            break;
        case "laugh":
            react_laugh(who->query_real_name());
            break;
        case "shake":
            react_shake(who->query_real_name());
            break;
    }
}
