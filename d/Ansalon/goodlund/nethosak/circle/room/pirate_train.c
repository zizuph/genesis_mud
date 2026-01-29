/*
 * File Name        : pirate_center_room.c
 * By               : Elmore.
 * Inspiration from : -
 * Date             : Nov. 2000.
 * Description      : The training room of the pirates.
 *                    I might add a npc that teaches them
 *                    the skills.
 *
 */

#pragma strict_types

/* Base file for skill trainers */
inherit "/lib/skill_raise";
inherit "/std/room";

#include "../local.h"

#include <ss_types.h>

/*
 * Function name: set_up_skills
 * Description:   Initialize the trainer and set the skills we train
 */
void
set_up_skills()
{
    create_skill_raise();
  
    sk_add_train(SS_TRADING, "make deals", "trading", 0, 35);
    sk_add_train(SS_SWIM, "swim", "swim", 0, 50);
    sk_add_train(SS_AWARENESS, "perceive", "awareness", 0, 40);
    sk_add_train(SS_DEFENSE, "dodge attacks", "defense", 0, 40);
    sk_add_train(SS_PARRY, "parry attacks", "parry", 0, 45);
    sk_add_train(SS_WEP_SWORD, "fight with a sword", "sword", 0, 55);
    sk_add_train(SS_GUILD_SPECIAL_SKILL, "stab at your enemy", "stab",
	80, 100);
}

void
create_room()
{
    set_short("Guild Trainer");
    set_long("This is the " + GUILD_NAME + " training hall.\n");

    add_exit("start", "north");

    /* configure the trainer */
    set_up_skills();
}

void
init()
{
    ::init();

    /* add the trainer's commands */
    init_skill_raise();
}
