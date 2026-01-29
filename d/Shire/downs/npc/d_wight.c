/*
 *  Barrow wight in the barrow downs
 *  Cloned by ~Shire/common/downs/stone2.c
 *
 * 2003/09/13 Last update
 * 2011/07/21 Lavellan - Added darkvision. Undead, and lives in dark barrow.
 *                     - Added gender. This one was missing it for some reason
 * 2014/12/20 Cotillion - XP Adjustment
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
    set_short("dark barrow wight");
    set_name("wight");
    add_name ("dark wight");
    add_name ("dark barrow wight");
    add_name ("barrow wight");

    set_race_name("wight");
    if (!IS_CLONE)
      return;

   
    set_long("This is a "+short()+". It inhabits the deeper regions " +
        "of the barrow, luring travellers to their deaths and " +
        "taking over their bodies. It looks like it was once a " +
        "fair person before death but now is corrupted and " +
        "searching for blood.\n");

    add_prop(CONT_I_WEIGHT,70000);   /* 70 kg  */
    add_prop(CONT_I_HEIGHT,180);     /* 180 cm */
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);     /*Does NOT look plesant*/
    add_prop(LIVE_I_UNDEAD, 38);      /*Is an undead*/
    add_prop(LIVE_I_NO_CORPSE, 1);   /*Leaves no corpse*/
    add_prop(LIVE_I_SEE_DARK, 50);   /*Can see in dark!*/
    add_prop("_ranger_i_not_blind",1);

            /* STR DEX CON INT WIS DIS */
    set_stats(({ 100, 100, 100, 71, 34, 89}));
    set_alignment(-900 - random (100));
    set_skill(SS_WEP_SWORD, 90 + random(8));
    set_skill(SS_PARRY, 90 + random(8));
    set_skill(SS_UNARM_COMBAT, 90 + random(8));
    set_skill(SS_DEFENCE, 80 + random(12));
    set_gender(G_NEUTER);

    set_aggressive(99);
    set_attack_chance(99);

    set_hp(900); /* Heal fully */

    set_act_time(15+random(30));
    add_act("emote hisses: Ghaaaaaasssst");
    add_act("emote hisses something unintelligible at you.");
    add_act("emote hisses: I smell fresh blood...");
    add_act("emote hisses: Sooo good to see you...");
    add_act("emote hisses: Have you come to claim your reward?");
    add_act("emote looks you up and down, smiling evilly.");
    add_act("emote smiles evilly at you.");
    add_act("emote hisses at you.");
    add_act("emote stretches forth a skeletal hand towards you.");
    

    set_cact_time(15+random(30));
    add_cact("emote howls devilishly at you.");
    add_cact("emote hisses: I shall feast on your earthly remains.");
    add_cact("emote hisses: Soon I shall chew your bones!!");
    add_cact("emote reaches out with a skeletal hand, chilling you " +
        "to the bone.");

   MAKE_MONEY;
   make_gold(3+random(8));
   /* Global sequence */
   set_act_time(5);
   seq_new("do_things");
   alarm_id = set_alarm(2.0,0.0,&arm());

   /* Adjusted based on difficulty / ac */
   set_exp_factor(180);
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
