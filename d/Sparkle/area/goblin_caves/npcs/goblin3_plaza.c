/*
 * Level 3 plaza goblin
 * Boreaulam, Jan 2018
 */
#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"

/*
 * Function name:        create_monster
 * Description  :        constructor for the object
 */
void
create_monster()
{

    string adj1 = one_of_list(({"strong", "muscular", "mighty",
                               "massive", "big", "powerful"}));
    string adj2 = one_of_list(({"lithe", "agile", "swift",
                               "quick", "graceful", "nimble"}));
    set_adj(adj1);
    set_adj(adj2);
    set_race_name("goblin");

    set_long("The " + adj1 + " " + adj2 + " goblin is a common resident of these caves.\n");
    set_short(adj1 + " " + adj2 + " goblin");

	set_base_stat(SS_STR, 150 + random(20));
	set_base_stat(SS_DEX, 130 + random(20));
	set_base_stat(SS_CON, 150 + random(20));
	set_base_stat(SS_INT, 80 + random(20));
	set_base_stat(SS_WIS, 100 + random(20));
	set_base_stat(SS_DIS, 80 + random(20));

    set_skill(SS_WEP_AXE, 70);
    set_skill(SS_PARRY, 70);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_BLIND_COMBAT, 70);
    set_skill(SS_AWARENESS, 50);

    add_prop(NPC_I_NO_UNARMED, 1);
    add_prop(OBJ_I_RES_MAGIC, 15);

	add_chat("Do you like this plaza?");
	add_chat("I don't think you are supposed to be here. Leave!");

    add_cact("emote growls: So you want a fight? I'll give you a fight you " +
        "scum!");
    set_chat_time(60);
    set_act_time(60);
    set_cchat_time(30);
    set_cact_time(30);
    set_default_answer(QCTNAME(TP)+" says: I'm not sure "+
        "what you are asking.\n");

} /* create_monster */

/*
 * Function name:        arm_me
 * Description  :        equip goblin
 */
void
arm_me()
{
    clone_object(EQUIP_DIR + "l3_iron_helm")->move(TO);
    clone_object(EQUIP_DIR + "l3_iron_bplate")->move(TO);
    clone_object(EQUIP_DIR + "l3_iron_greaves")->move(TO);
    clone_object(EQUIP_DIR + "l3_iron_bracers")->move(TO);
    clone_object(EQUIP_DIR + "l3_battleaxe")->move(TO);

    command("wield all");
    command("wear all");
} /* arm_me */

