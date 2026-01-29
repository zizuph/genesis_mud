/*
 * Rack guard on level 2
 * Boreaulam, September 2012
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

	set_name("guard");
    add_name("_rack_guard");
    set_short("muscular goblin guard");
    set_race_name("goblin");

    set_long("This muscular goblin is clearly guarding the racks here. \n");

	set_base_stat(SS_STR, 145 + random(15));
	set_base_stat(SS_DEX, 120 + random(15));
	set_base_stat(SS_CON, 145 + random(15));
	set_base_stat(SS_INT, 85 + random(15));
	set_base_stat(SS_WIS, 120 + random(15));
	set_base_stat(SS_DIS, 85 + random(15));

    set_skill(SS_WEP_SWORD, 80 + random(10));
    set_skill(SS_WEP_AXE, 80 + random(10));
    set_skill(SS_WEP_KNIFE, 80 + random(10));
    set_skill(SS_PARRY, 80 + random(10));
    set_skill(SS_DEFENCE, 80 + random(10));
    set_skill(SS_UNARM_COMBAT, 70 + random(10));
    set_skill(SS_BLIND_COMBAT, 70 + random(10));
    set_skill(SS_AWARENESS, 70 + random(10));

    add_prop(NPC_I_NO_UNARMED, 1);
    add_prop(OBJ_I_RES_MAGIC, 20);


	add_chat("These racks are protected and you have no business here. So " +
        "get lost!");
	add_chat("You should leave right now, before I have to call someone " +
        "to escort you out.");
	add_chat("These racks are only for residents of these caves, and " +
        "that clearly does not include you. So, perhaps you can just " +
        "leave now.");

    add_act("emote walks around to check the rack, making sure everything " +
        "is secure.");

    add_cact("emote growls: I will see you dead if it is the last thing " +
        "I ever do!");
    add_cact("shout We are under attack.");
    set_chat_time(20);
    set_act_time(20);
    set_cchat_time(10);
    set_cact_time(10);
    set_default_answer(QCTNAME(TP)+" says: I don't want to help you. Leave!\n");

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
    clone_object(EQUIP_DIR + "l2_bronze_greaves")->move(TO);
    clone_object(EQUIP_DIR + "l2_axe")->move(TO);

    command("wield all");
    command("wear all");
} /* arm_me */

