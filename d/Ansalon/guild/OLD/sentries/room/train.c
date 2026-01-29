/*
 * File Name        : train.c
 * By               : Elmore and Boron
 * Inspiration from : -
 * Date             : March 2001.
 * Description      : The training room for the Knights of Palanthas
 *
 */

#pragma strict_types

/* Base file for skill trainers */
inherit "/lib/skill_raise";
inherit "/d/Krynn/std/room";

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

    sk_add_train(SS_TRADING, "make deals", "trading", 0, 45);
    sk_add_train(SS_ACROBAT, "make acrobatics", "acrobat", 0, 40);
    sk_add_train(SS_SWIM, "swim", "swim", 0, 40);
    sk_add_train(SS_2H_COMBAT, "fight with two weapons", "two handed combat", 0, 50);
    sk_add_train(SS_AWARENESS, "perceive", "awareness", 0, 50);
    sk_add_train(SS_WEP_KNIFE, "fight with a knife", "knife", 0, 60);
    sk_add_train(SS_DEFENSE, "dodge attacks", "defense", 0, 50);
    sk_add_train(SS_PARRY, "parry attacks", "parry", 0, 50);
    sk_add_train(SS_WEP_SWORD, "fight with a sword", "sword", 0, 50);
    sk_add_train(SS_LANGUAGE, "speak languages", "language", 0, 45);
}

object trainer;

void
reset_krynn_room()
{

}

void
create_krynn_room()
{
    set_short("Practice hall");
    set_long("This is a large room, made of white stone blocks, there "
            + "are sentinels of Palanthas training everywhere, perfecting "
            + "thier skills.\n");

    add_exit("center_room", "south");

    /* configure the trainer */
    set_up_skills();
    reset_room();
}

void
init()
{
    ::init();

    /* add the trainer's commands */
    init_skill_raise();
}
