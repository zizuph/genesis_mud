inherit "/std/monster";

#include "/sys/stdproperties.h"
#include "default.h"

void
create_monster()
{
   set_name("paladin");
   set_adj("elven");
   set_living_name("_mylos_paladin_3_");
   set_race_name("elf");
   set_short("elven paladin");
   set_long(break_string("This powerful warrior one of the few elite "+
         "guards that protect the Prince and Princess from all harm in "+
         "the castle of Telberin.\n", 76));
   
   set_base_stat(SS_STR, 98);         
   set_base_stat(SS_DEX, 88);         
   set_base_stat(SS_CON, 97);         
   set_base_stat(SS_INT, 104);
   set_base_stat(SS_WIS, 56);
   set_base_stat(SS_DIS, 82);
   
   set_skill(SS_WEP_SWORD, 86);
   set_skill(SS_DEFENCE, 40);
   set_skill(SS_PARRY, 80);
   set_alignment(1000);
   
   set_hp(2657);
   
   set_all_hitloc_unarmed(14); /* Inherent AC of 5 */
   
   add_prop(OBJ_I_WEIGHT, 19000);
   
   add_prop(CONT_I_MAX_WEIGHT, 96000);
   add_prop(OBJ_I_VOLUME, 89000);
   add_prop(LIVE_O_ENEMY_CLING, 1);
   add_prop(CONT_I_MAX_VOLUME, 100000);
	add_prop(NPC_I_NO_RUN_AWAY, 1);
   
   set_chat_time(15);                             /* Set speaking interval */
   add_chat("Are you here on official business?");
   add_chat("Greetings stranger! How art thou?");
   
   
   set_cchat_time(8);                      /* Set combat speaking interval */
   add_cchat("Protect the Prince and Princess!");
   add_cchat("Leave before the rest of my comrades aid me!");
   
   
   set_act_time(10);                    /* Set action interval           */
   add_act("ponder");
   add_act("smile");
   add_act("hmm");
   
   trig_new("%w 'smiles' %s", "react_smile");
   trig_new("%w 'introduces' %s", "react_introduce");
   trig_new("%w 'shakes' %w 'head' %s", "react_shake");
   trig_new("%w 'bows' %s", "react_bow");
   
   call_out("arm_me", 1);
}

int
react_bow(string who, string dummy) {
   if(who) {
      who = lower_case(who);
      call_out("return_bow", 3, who);
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
         command("say Greetings.");
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
         command("say Nice to see that you are happy, " + obj->query_nonmet_name()
         + "?");
      if (ran == 1)
         command("shake " + who);
      if (ran == 2)
         command("say It's a lovely day today, " + obj->query_nonmet_name()
         + "?");
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
         command("say Really, " + obj->query_race() + "?");
      if (ran == 1)
         command("say I agree with you, "
         + ((obj->query_gender() == G_MALE) ? "master" : "lady") + ".");
      if (ran == 2)
         command("say Why do " + LANG_PWORD(obj->query_race())
         + " always disagree?");
   }
}

void
arm_me()
{
   object eq;
   
   eq = clone_object("/d/Emerald/mylos/obj/e_longs");
   if (eq)
      eq->move(this_object());
   eq = clone_object("/d/Emerald/mylos/obj/w_plate");
   if (eq)
      eq->move(this_object());
   eq = clone_object("/d/Emerald/mylos/obj/w_hel");
   if (eq)
      eq->move(this_object());
   command("wield all");
   
   command("wear all");
   
}
