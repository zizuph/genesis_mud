/*
 * Living room mother
 * Boreaulam, September 2012
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

    string adj = one_of_list(({"green-eyed", "mature", "happy-looking",
                               "tall", "short", "chubby"}));
    set_adj(adj);
    add_adj("female");
    set_race_name("goblin");

    set_long("The female goblin is a mother of a goblin family living here.\n");
    set_short(adj + " female goblin");

    set_gender(G_FEMALE);

    set_base_stat(SS_STR, 75 + random(10));
    set_base_stat(SS_DEX, 60 + random(10));
    set_base_stat(SS_CON, 75 + random(10));
    set_base_stat(SS_INT, 50 + random(10));
    set_base_stat(SS_WIS, 60 + random(10));
    set_base_stat(SS_DIS, 50 + random(10));

    set_skill(SS_WEP_CLUB, 80 + random(10));
    set_skill(SS_WEP_KNIFE, 80 + random(10));
    set_skill(SS_PARRY, 50 + random(10));
    set_skill(SS_DEFENCE, 50 + random(10));
    set_skill(SS_UNARM_COMBAT, 50 + random(10));
    set_skill(SS_BLIND_COMBAT, 50 + random(10));
    set_skill(SS_AWARENESS, 40 + random(10));

    add_prop(NPC_I_NO_UNARMED, 1);
	add_prop(NPC_M_NO_ACCEPT_GIVE, " doesn't want anything from you.\n");

    add_chat("My husband is good warrior.");
    add_chat("My son will be great fighter.");
    add_chat("What are you doing here?");

    set_chat_time(60);
    set_act_time(60);
    set_cchat_time(10);
    set_cact_time(10);
    add_cact("emote looks around.");
    add_cact("emote stares at you.");

    add_act("emote scratches her head and growls.");
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
    clone_object(EQUIP_DIR + "l2_rollingpin")->move(TO);
    clone_object(EQUIP_DIR + "l2_vest")->move(TO);

    command("wield all");
    command("wear all");
} /* arm_me */

