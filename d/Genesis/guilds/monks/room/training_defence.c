/*
 * File:    training_defence
 * Creator: Cirion, 1998.06.14
 * Purpose: Defence training for the monk's guild
 */
#pragma strict_types
#include "defs.h"
#include <ss_types.h>

inherit ROOMBASE;

object samir;

void reset_room();

void
create_room ()
{
    set_short("granite stone building");
    set_long("Covering the floor of this large, one-room stone "
        + "building is a carpet of dried reeds, which crackle "
        + "underfoot." + NPC_DESC + " Sunlight from the garden to the southwest, "
        + "as well as through the three small windows in each of the "
        + "other walls give good illumination to this room.\n");


    WIZINFO("This is the room where monks are able to traing their "
        + "defence.\n");

    // where, command
    add_exit("garden", "southwest");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("southwest", "As you enter the granite stone building, "
        + "the dry reeds of the floor crackle noisly.\n");

    // put in setup skills here.

    WIZINFO("This is the room where monks are able to traing their "
        + "defence.\n");

    reset_room();

    // put in skill dump for wizards here.
    // setup the training objects that will allow players to
    // train skills here.
    msk_setup_training(SS_LAYMAN, ({ SS_DEFENCE }))->set_monk_trainer(samir);
    msk_setup_training(SS_OCCUP, ({ SS_DEFENCE }))->set_monk_trainer(samir);
}

void
populate()
{
    if(!samir)
        samir = m_clone_here(MONK_NPC + "samir", 0, "arm_me", " Standing "
            + "in the center of the room is a stern, confident human with "
            + "dark skin and blue eyes.");

    if(!present(samir))
        samir->move_living("away", TO);
}

void
reset_room()
{
    populate();
}

