inherit "/std/monster";
 
#include "default.h"
#define G_MALE 0
 
void return_bow(string who);
void return_smile(string who);
void return_introduce(string who);
void return_shake(string who);
 
void
create_monster()
{
   set_name("squire");
   set_living_name("_mylos_squire_");
   set_race_name("elf");
   set_short("elven squire");
   set_long("This young elf is a squire at the court at Telberin. He is " +
            "wearing the tabard of the royal house and wielding his foil " +
            "like a courtier.\n");
 
   set_base_stat(SS_STR, 35);
   set_base_stat(SS_DEX, 30);
   set_base_stat(SS_CON, 45);
   set_base_stat(SS_INT, 40);
   set_base_stat(SS_WIS, 32);
   set_base_stat(SS_DIS, 40);
 
   set_skill(SS_WEP_SWORD, 40);
   set_skill(SS_DEFENCE, 40);
   set_skill(SS_PARRY, 35);
   set_alignment(304);
 
   set_hp(765);
 
   set_all_hitloc_unarmed(5); /* Inherent AC of 5 */
 
   add_prop(OBJ_I_WEIGHT, 19000);
 
   add_prop(CONT_I_MAX_WEIGHT, 180000);
   add_prop(OBJ_I_VOLUME, 89000);
   add_prop(LIVE_O_ENEMY_CLING, 1);
   add_prop(CONT_I_MAX_VOLUME, 100000);
 
   set_chat_time(15);                             /* Set speaking interval */
   add_chat("Where is that wyvern?");
   add_chat("Hi there! How are you?");
   add_chat("They sent me here just to look for the clerics.");
   add_chat("Do you like my brand new tabard?\n");
   add_chat("There's supposed to be a nasty wyvern around here.\n");
   add_chat("Have you visited the city recently?");
 
   set_cchat_time(8);                      /* Set combat speaking interval */
   add_cchat("Don't hit me, please!");
   add_cchat("Can't we be friends?");
 
   set_act_time(10);                    /* Set action interval           */
   add_act("ponder");
   add_act("smile");
 
   trig_new("%w 'smiles' %s", "react_smile");
   trig_new("%w 'introduces' %s", "react_introduce");
   trig_new("%w 'shakes' %w 'head' %s", "react_shake");
   trig_new("%w 'bows' %s", "react_bow");
}
 
int
react_bow(string who, string dummy) {
   if(who) {
      who = lower_case(who);
      set_alarm(3.0, 1.0, &return_bow(who));
      return 1;
   }
}
 
void
return_bow(string who) {
   object obj;
   int ran;
 
   if(obj = present(who, environment())) {
      ran = random(3);
      if(ran == 0)
         command("say Hello there!");
      if(ran == 1)
         command("bow to " + who);
      if(ran == 2)
         command("say Nice to meet you, "+
         obj->query_nonmet_name() +".");
   }
}
 
int
react_smile(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      set_alarm(1.0, 0.0, &return_smile(who));
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
         command("say Nice to see that you are happy, " +
         obj->query_nonmet_name() + "?");
      if (ran == 1)
         command("shake " + who);
      if (ran == 2)
         command("say What a beautiful day isn't it, " +
         obj->query_nonmet_name() + "?");
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
         command("say How are you, " + obj->query_race() + "?");
         command("bow to " + who);
       }
   }
}
 
int
react_shake(string who, string dummy1, string dummy2) {
   if (who) {
      who = lower_case(who);
      set_alarm(2.0, 0.0, &return_shake(who));
      return 1;
   }
}
 
void
return_shake(string who) {
   object obj;
   int ran;
 
   if (obj = present(who, environment())) {
      ran = random(2);
      if (ran == 0)
         command("say That's friendly, " + obj->query_race() + "!");
      if (ran == 1)
         command("say I agree with you, "
         + ((obj->query_gender() == G_MALE) ? "master" : "lady") + ".");
   }
}
 
void
arm_me()
{ 
   clone_object(WEP_DIR + "foil")->move(this_object(), 1);
   clone_object(ARM_DIR + "tabard")->move(this_object(), 1);
   clone_object(ARM_DIR + "l_hel")->move(this_object(), 1);
   clone_object(ARM_DIR + "l_cui")->move(this_object(), 1);
   command("wield all");
   command("wear all");
}
