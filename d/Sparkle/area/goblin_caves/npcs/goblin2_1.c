/*
 * Easy level 2 goblin
 * Boreaulam, April 2012
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

    string adj = one_of_list(({"weak", "deft", "skinny",
                               "dense", "foolish", "fearful"}));
    set_adj(adj);
    set_race_name("goblin");

    set_long("The " + adj + " goblin is a common resident of these caves.\n");
    set_short(adj + " goblin");

	set_base_stat(SS_STR, 100 + random(20));
	set_base_stat(SS_DEX, 80 + random(20));
	set_base_stat(SS_CON, 100 + random(20));
	set_base_stat(SS_INT, 60 + random(20));
	set_base_stat(SS_WIS, 80 + random(20));
	set_base_stat(SS_DIS, 60 + random(20));

    set_skill(SS_WEP_AXE, 60 + random(20));
    set_skill(SS_PARRY, 50 + random(20));
    set_skill(SS_DEFENCE, 50 + random(20));
    set_skill(SS_UNARM_COMBAT, 50 + random(20));
    set_skill(SS_BLIND_COMBAT, 50 + random(20));
    set_skill(SS_AWARENESS, 40 + random(20));

    add_prop(NPC_I_NO_UNARMED, 1);
    add_prop(OBJ_I_RES_MAGIC, 15);

	add_chat("What are you doing here?");
	add_chat("I don't think you are supposed to be here. Leave!");
	add_chat("Get lost! Leave before I make you leave!");

    add_cact("emote growls: So you want a fight? I'll give you a fight you " +
        "scum!");
    set_chat_time(20);
    set_act_time(20);
    set_cchat_time(10);
    set_cact_time(10);
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
    clone_object(EQUIP_DIR + "l2_bronze_helm")->move(TO);
    clone_object(EQUIP_DIR + "l2_bronze_bplate")->move(TO);
    clone_object(EQUIP_DIR + "l2_axe")->move(TO);

    command("wield all");
    command("wear all");
} /* arm_me */

