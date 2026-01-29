/*
 * File:    training_ua
 * Creator: Cirion, 1998.06.14
 * Purpose: Unarmed combat training for the monk's guild
 */
#pragma strict_types
#include "defs.h"
#include <ss_types.h>

inherit ROOMBASE;

object guano;

void reset_room();

void
create_room ()
{
    set_short("stone building");
    set_long("This is a large, one-room stone building. The floor "
        + "is made from very smooth, almost soft, stone. The walls "
        + "of the building are made from rough blocks of granite."
        + NPC_DESC + " A "
        + "narrow doorway leads out into a wide garden to the "
        + "southeast.\n");


    WIZINFO("This is the room where monks are able to traing their "
        + "unarmed combat.\n");

    // where, command
    add_exit("garden", "southeast");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("southeast", "You enter the cool stone building.\n");

    // put in setup skills here.

    WIZINFO("This is the room where monks are able to traing their "
        + "unarmed combat.\n");
    // put in skill dump for wizards here.

    reset_room();

}

void
populate()
{
    if(!guano)
    {
        guano = m_clone_here(MONK_NPC + "guano", 0, "arm_me", " Standing in the "
            + "center of the room is an ancient and surly-looking goblin.");

        guano->move_living("away", TO);

        // setup the training objects that will allow players to
        // train skills here.
        msk_setup_training(SS_LAYMAN, ({ SS_UNARM_COMBAT, SS_WEP_POLEARM, MONK_SKILL_STRIKE, MONK_SKILL_PLEXUS }))->set_monk_trainer(guano);
        msk_setup_training(SS_OCCUP, ({ SS_UNARM_COMBAT, SS_WEP_POLEARM, MONK_SKILL_STRIKE, MONK_SKILL_PLEXUS }))->set_monk_trainer(guano);
    }

    if(!present(guano))
        guano->move_living("away", TO);

}

void
reset_room()
{
    populate();
}

