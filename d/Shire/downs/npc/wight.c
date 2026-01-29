/*
 *  Barrow wight in the barrow downs
 *  Cloned by ~Shire/common/downs/stone2.c
 *
 * 2001/12/27 Last update
 * 2011/07/21 Lavellan - Added darkvision. Undead, and lives in dark barrow.
 */

inherit "/std/monster";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/common/lib/evilkill.h"
#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

//   Prototypes
void arm();

int alarm_id;


void
create_monster()
{
   if (!IS_CLONE)
      return;

   set_name(({"black barrow wight","wight","barrow wight","black wight"}));
   set_title("black");
   set_race_name("wight"); 
   set_adj(({"black","barrow"}));
   set_pshort("black barrow wights");
   set_long("This is a spirit of a long dead noble. His " +
        "skeletal features are shrouded in a cloak of darkness. " +
        "Luminous, cold eyes pierce the shroud of darkness and " +
        "stare at you.\n");

   add_prop(CONT_I_WEIGHT,67000);   /*  10 Kg */
   add_prop(CONT_I_HEIGHT,169);     /* 169 cm */
   add_prop(LIVE_I_NEVERKNOWN,1);  /* Always known by people */
   add_prop(NPC_I_NO_LOOKS, 1);     /*Does NOT look plesant*/
   add_prop(NPC_I_NO_RUN_AWAY, 1); /* Not wimpy */
   add_prop(LIVE_I_UNDEAD, 43);      /*Is an undead*/
   add_prop(LIVE_I_NO_CORPSE, 1);   /*Leaves no corpse*/
   add_prop(LIVE_I_SEE_DARK, 50);   /*Can see in dark!*/
  add_prop("_ranger_i_not_blind",1);

            /* STR DEX CON INT WIS DIS */
   set_stats(({ 125, 111, 110, 80, 75, 115}));
   set_alignment(-700-random(100));
   set_skill(SS_WEP_SWORD,70);
   set_skill(SS_UNARM_COMBAT, 50);
   set_skill(SS_DEFENCE, 50);
   set_skill(SS_PARRY, 60);
   set_pick_up(99);
   set_gender(G_NEUTER);
    

   set_aggressive(70);
   set_attack_chance(75);

   set_act_time(5);
   add_act("emote hisses: Come to me and I shall reward you well.");
   add_act("emote hisses: You are a fine person, worthy of what I can give you.");
   add_act("emote hisses: I smell flesh.");
   add_act("emote hisses: No one will save you here.");

   set_cact_time(5);
   add_cact("emote hisses: Die, mortal.");
   add_cact("emote hisses: You shall be mine!");
   add_cact("emote hisses: I shall feast on your corpse!");
   add_cact("grips you in his strong grasp.");
   add_cact("touches you with a skeletal hand that almost " +
        "freezes your blood.");

   MAKE_MONEY;
   make_gold(3+random(8));
   /* Global sequence */
   set_act_time(5);
   seq_new("do_things");
   alarm_id = set_alarm(2.0,0.0,&arm());
  
   /* XP Adjustment, AoB team */
   set_exp_factor(80);
}

void
arm()
{
	object sword, plate, money;

    remove_alarm(alarm_id);
	sword	= clone_object(DOWNS_WEP +"w_sword");
	sword->move(this_object());

	plate = clone_object(DOWNS_ARM +"w_plate");
	plate->move(this_object());	
	
	command ("wear all");
	command ("wield all");
 	command ("grin demonically");

}


return_to_normal() {
   set_act_time(5);
}
