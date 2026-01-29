/*
 * Easy level 1 goblin
 * Boreaulam, April 2012
 */
#pragma save_binary
#pragma strict_types

inherit "/std/monster";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"
void arm_me();

/*
 * Function name:        create_monster
 * Description  :        constructor for the object
 */
void
create_monster()
{

    string adj = one_of_list(({"puny", "stiff", "sickly",
                               "moronic", "inane", "gutless"}));
    set_adj(adj);
    set_race_name("goblin");

    set_long("Judging from its feeble physique and the nervous look in " +
        "its eyes, the " + adj + " goblin will not be a dangerous foe " +
        "in a fight.\n");
    set_short(adj + " goblin");

	set_base_stat(SS_STR, 40 + random(10));
	set_base_stat(SS_DEX, 30 + random(10));
	set_base_stat(SS_CON, 40 + random(10));
	set_base_stat(SS_INT, 20 + random(10));
	set_base_stat(SS_WIS, 30 + random(10));
	set_base_stat(SS_DIS, 20 + random(10));

    set_skill(SS_WEP_SWORD, 50 + random(10));
    set_skill(SS_WEP_AXE, 50 + random(10));
    set_skill(SS_WEP_KNIFE, 50 + random(10));
    set_skill(SS_PARRY, 30 + random(10));
    set_skill(SS_DEFENCE, 20 + random(10));
    set_skill(SS_UNARM_COMBAT, 30 + random(10));
    set_skill(SS_BLIND_COMBAT, 30 + random(10));
    set_skill(SS_AWARENESS, 20 + random(10));

    add_prop(NPC_I_NO_UNARMED, 1);

    add_chat("We will rule the world!");
    add_chat("Goblins are a superior race!");
    add_chat("I should hone my combat skills.");

    set_chat_time(20);
    set_act_time(20);
    set_cchat_time(10);
    set_cact_time(10);
    add_cact("emote howls at you while his eyes dart around erratically " +
        "in an insane manner.");

    add_act("emote scratches his head and growls.");
    add_act("emote stares intently at you for a long, awkward moment.");
    add_act("emote stares at the ceiling of the cave and suddenly begins " +
        "to laugh maniacally.");
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
    clone_object(EQUIP_DIR + "lsword")->move(TO);
    clone_object(EQUIP_DIR + "leather_armour")->move(TO);

    command("wield all");
    command("wear all");
} /* arm_me */

