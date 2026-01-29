/*
 * Living room son
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

    string adj = one_of_list(({"green-eyed", "young", "ugly",
                               "fat", "skinny", "smiling"}));
    set_adj(adj);
    add_adj("male");
    set_name("boy");
    set_race_name("goblin");

    set_long("This goblin boy is a local resident of these caves. You are " +
        "certain the rest of his family will be nearby.\n");
    set_short(adj + " boy");

    set_base_stat(SS_STR, 45 + random(10));
    set_base_stat(SS_DEX, 35 + random(10));
    set_base_stat(SS_CON, 45 + random(10));
    set_base_stat(SS_INT, 25 + random(10));
    set_base_stat(SS_WIS, 35 + random(10));
    set_base_stat(SS_DIS, 25 + random(10));

    set_skill(SS_WEP_CLUB, 60 + random(10));
    set_skill(SS_PARRY, 30 + random(10));
    set_skill(SS_DEFENCE, 20 + random(10));
    set_skill(SS_UNARM_COMBAT, 50 + random(10));
    set_skill(SS_BLIND_COMBAT, 50 + random(10));
    set_skill(SS_AWARENESS, 20 + random(10));

    add_prop(NPC_I_NO_UNARMED, 1);

    add_chat("My father is a good warrior! He will protect us all.");
    add_chat("I like toys! Do you have any toys for me?");

    set_chat_time(60);
    set_act_time(60);
    set_cchat_time(10);
    set_cact_time(10);
    add_cact("say Stop it! My father will kill you for this!");

    add_act("emote plays a game with his stick.");
    set_default_answer(QCTNAME(TP)+" says: My mother doesn't " +
        "allow to talk to strangers.\n");

} /* create_monster */

/*
 * Function name:        arm_me
 * Description  :        equip goblin
 */
void
arm_me()
{
    clone_object(EQUIP_DIR + "l2_boystick")->move(TO);

    command("wield all");
    command("wear all");
} /* arm_me */

