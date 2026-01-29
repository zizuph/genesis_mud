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

/*
 * Function name:        create_monster
 * Description  :        constructor for the object
 */
void
create_monster()
{

    string adj = one_of_list(({"feeble", "lumbering", "fragile",
                               "dimwitted", "stupid", "frightened"}));
    set_adj(adj);
    set_short(adj + " goblin");
    set_race_name("goblin");

    set_long("The " + adj + " goblin rests after a training while " +
             "watching others. Although he is tired, his muscular body " +
             "proves him as a worthy warrior.\n");

	set_base_stat(SS_STR, 45 + random(10));
	set_base_stat(SS_DEX, 35 + random(10));
	set_base_stat(SS_CON, 45 + random(10));
	set_base_stat(SS_INT, 25 + random(10));
	set_base_stat(SS_WIS, 35 + random(10));
	set_base_stat(SS_DIS, 25 + random(10));

    set_skill(SS_WEP_SWORD, 50 + random(10));
    set_skill(SS_WEP_AXE, 50 + random(10));
    set_skill(SS_WEP_KNIFE, 50 + random(10));
    set_skill(SS_PARRY, 40 + random(10));
    set_skill(SS_DEFENCE, 40 + random(10));
    set_skill(SS_UNARM_COMBAT, 40 + random(10));
    set_skill(SS_BLIND_COMBAT, 40 + random(10));
    set_skill(SS_AWARENESS, 40 + random(10));

    add_prop(NPC_I_NO_UNARMED, 1);

	add_chat("Training is everything to me, I will be the greatest " +
        "warrior ever!");
	add_chat("Train and you will become a strong warrior.");
	add_chat("I refuse to let myself become lazy and weak. By training, " +
        "I constantly make myself stronger and faster.");

    add_act("emote astutely watches the other goblins in training.");
    add_act("emote begins a series of elaborate stretching exercises.");
    add_act("emote rubs some tired muscles.");

    add_cact("emote growls: This is what I trained for.");
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
    clone_object(EQUIP_DIR + "lsword")->move(TO);
    clone_object(EQUIP_DIR + "copper_plate")->move(TO);

    command("wield all");
    command("wear all");
} /* arm_me */

