inherit "/std/monster";

#include "default.h"

void arm_me();

void
create_monster()
{
   
   set_name("cleric");
   set_race_name("elf");
   set_short("cleric");
   set_long("This is an elven cleric who tends to the woods for the people " +
      "of Telberin. She serves the Goddess of Nature, and has " +
      "dedicated her life to her.\n");
   
   add_prop(CONT_I_WEIGHT,35000);
   add_prop(CONT_I_MAX_WEIGHT,90000);
   add_prop(CONT_I_VOLUME,35000);
   add_prop(CONT_I_MAX_VOLUME,60000);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   
   set_gender(1);  /* male=0, female=1, other=2 */
   
   /* stats -   STR  DEX  CON  INT  WIS  DIS  */
   set_stats(({  40,  37,  42,  50,  51,  40})); /* My, what fine stats. */
   set_hp(query_max_hp());                       /* Fully healed         */
   
   /* Set unarmed attacks and armour classes. */
   set_all_hitloc_unarmed(18);
   set_all_attack_unarmed(23,24);
   
   set_attack_chance(0);
   set_alignment(500);
   
   set_alarm(1.0, 0.0, arm_me);
   
   
   set_skill(SS_UNARM_COMBAT,34);
   set_skill(SS_BLIND_COMBAT,50);
   set_skill(SS_PARRY,35);
   set_skill(SS_DEFENCE,36);
   
   set_skill(SS_AWARENESS,50);
   
   set_chat_time(10);                             /* Set speaking interval */
   add_chat("Are you here to pray?"); /* A bit of random chat */
   add_chat("Offerings are not accepted at this time of year.");
   add_chat("Are you sure you're in the correct temple, adventurer?");    
   
   set_cchat_time(4);                      /* Set combat speaking interval */
   add_cchat("The Goddess shall protect me.");            
   add_cchat("Paladins! Aid me now!");
   
   set_act_time(10);                    /* Set action interval           */
   add_act("smile");              /* A few courteous actions       */
   add_act("sigh");
   add_act("emote mumbles something under her breath.");
}

void
arm_me()
{
   object eq;
   eq = clone_object(WEP_DIR + "c_staff");
   if (eq)
      eq->move(this_object());
   eq = clone_object(ARM_DIR + "c_robes");
   if (eq)
      eq->move(this_object());
   command("wear all");
   command("wield all");
   return;
}
