/*
 *  Barrow wight in the barrow downs
 *  Cloned by ~Shire/common/downs/stone2.c
 */

inherit "/std/monster";
#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Shire/common/make_money.h"
#include "/d/Shire/common/lib/evilkill.h"

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
   set_long("This is a black barrow wight, the worst of them all."
+" It fears no mortal creature, and lusts for the taste of blood.\n");

   add_prop(CONT_I_WEIGHT,67000);   /*  10 Kg */
   add_prop(CONT_I_HEIGHT,169);     /* 169 cm */
   add_prop(LIVE_I_NEVERKNOWN,1);  /* Always known by people */
   add_prop(NPC_I_NO_LOOKS, 1);     /*Does NOT look plesant*/
   add_prop(NPC_I_NO_RUN_AWAY, 1); /* Not wimpy */
   add_prop(LIVE_I_UNDEAD, 43);      /*Is an undead*/
   add_prop(LIVE_I_NO_CORPSE, 1);   /*Leaves no corpse*/
  add_prop("_ranger_i_not_blind",1);

            /* STR DEX CON INT WIS DIS */
   set_stats(({ 112, 102, 114, 82, 11, 93}));
   set_alignment(-100);
   set_skill(SS_WEP_SWORD,70);
   set_skill(SS_UNARM_COMBAT, 50);
   set_skill(SS_DEFENCE, 50);
   set_skill(SS_PARRY, 60);
   set_pick_up(99);
    

   set_aggressive(70);
   set_attack_chance(75);

   set_chat_time(5);
   add_chat("HUUUHHHHHH");
   add_chat("AHHHHHH, Blood");
   add_chat("I smell Flesh");
   add_chat("Tom Bombadil is far away");

   set_cchat_time(5);
   add_cchat("Die, mortal.");
   add_cchat("Dont fear, TREMBLE!");
   add_cchat("I shall feast on your corpse");

   MAKE_MONEY;
   make_gold(3+random(8));
   /* Global sequence */
   set_act_time(5);
   seq_new("do_things");
   alarm_id = set_alarm(2.0,0.0,&arm());
}

void
arm() {
	object sword, plate, money;

        remove_alarm(alarm_id);
	sword	= clone_object(DOWNS_DIR +"wep/w_sword");
	sword->move(this_object());

	plate = clone_object(DOWNS_DIR +"arm/w_plate");
	plate->move(this_object());	
	
	command ("wear all");
	command ("wield all");
 	command ("grin");

}


return_to_normal() {
   set_act_time(5);
}
