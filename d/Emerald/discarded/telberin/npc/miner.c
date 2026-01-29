inherit "/std/monster";

#include "/d/Emerald/defs.h"

void
create_monster()
{
   set_name("miner");
   set_adj("deranged");
   set_race_name("human");
   set_short("deranged miner");
   set_long("This old miner appears to be round the bend. His appearance " +
      "is scruffy and his long grey beard is unkept and not like many " +
      "humans you have seen.\n");
   
   set_base_stat(SS_STR, 30);
   set_base_stat(SS_DEX, 20);
   
   set_base_stat(SS_CON, 25);
   set_base_stat(SS_INT, 13);
   set_base_stat(SS_WIS, 10);
   set_base_stat(SS_DIS, 20);
   
   set_skill(SS_WEP_AXE, 20);
   set_skill(SS_DEFENCE, 15);
   set_skill(SS_PARRY, 15);
   set_skill(SS_FORM_DIVINATION, 25);
   set_skill(SS_ELEMENT_LIFE, 40);
   set_skill(SS_APPR_MON, 70);
   set_skill(SS_AWARENESS, 45);
   
   set_hp(300);
   
   add_prop(CONT_I_WEIGHT, 62000);
   add_prop(CONT_I_MAX_WEIGHT, 120000);
   add_prop(OBJ_I_VOLUME, 62000);
   add_prop(CONT_I_MAX_VOLUME, 100000);
   
   set_chat_time(10);                             /* Set speaking interval */
   add_chat("Get out of my mines! It's all mine you hear?");
   
   set_cchat_time(4);                      /* Set combat speaking interval */
   add_cchat("What are you doing? Attacking a defenceless old man!");
   add_cchat("Leave me alone! I haven't done anything to you...");
   
   set_act_time(10);                    /* Set action interval           */
   add_act("cackle");
   add_act("growl");
}

void
arm_me()
{
   object eq;
   
   eq = clone_object("/d/Emerald/telberin/wep/paxe");
   if (eq)
      eq->move(this_object());
  eq = clone_object("/d/Emerald/telberin/arm/jerkin");
   /*Halgor 17.3.93     */
   if (eq)
      eq->move(TO);
   command("wield all");
   command("wear all");
}
