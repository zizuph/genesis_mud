/*
 * File:    training_focus
 * Creator: Cirion, 1998.06.14
 * Purpose: Focus & blindfighting training for the monks
 */
#pragma strict_types
#include "defs.h"
#include <ss_types.h>

inherit ROOMBASE;

object    fylia;

void      reset_room();

void
create_room ()
{
    set_short("dark stone building");
    set_long("Gloom and shadows pervade this place. Shadows "
        + "seem to cling to every corner of the room. The "
        + "very air seems laden with a dragon's sighs.\n");

    // where, command
    add_exit("garden", "northeast");

    // let them light up the room if they are tenacious enough
    add_prop (ROOM_I_LIGHT, -20);

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("northeast", "As you pass through the doorway to "
        + "the shale building, you are suddenly engulfed in "
        + "impenetrable shadows.\n");

    // put in setup skills here.

    WIZINFO("This is the room where monks are able to train "
        + "focus and blindfighting.\n");

    reset_room();

    // setup the training objects that will allow players to
    // train skills here.
    msk_setup_training(SS_LAYMAN, ({ MONK_SKILL_FOCUS, SS_BLIND_COMBAT }))->set_monk_trainer(fylia);
    msk_setup_training(SS_OCCUP, ({ MONK_SKILL_FOCUS, SS_BLIND_COMBAT }))->set_monk_trainer(fylia);

}

void
populate()
{
    if(!fylia)
        fylia = m_clone_here(MONK_NPC + "fylia");

    if(!present(fylia))
        fylia->move_living("away", TO);
}

void
reset_room()
{
    populate();
}


