/*
 * File:    
 * Creator: Cirion, 1998.06.14
 * Purpose: Misc. training for the monks
 */
#pragma strict_types
#include "defs.h"
#include <ss_types.h>

inherit ROOMBASE;

object    esaria;

void      reset_room();

void
create_room ()
{
    set_short("stone building");
    set_long("The walls of this one-room stone building are made "
        + "from soft grey basalt." + NPC_DESC + " The floor is uncovered gravel, "
        + "and a wide doorway leads out to the northwest into "
        + "the brightly-lit garden.\n");

    // where, command
    add_exit("garden", "northwest");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("northwest", "You enter the basalt stone building.\n");

    // put in setup skills here.

    WIZINFO("This is the room where monks are able to train some "
        + "misc skills.\n");
    // put in skill dump for wizards here.

    reset_room();

    // setup the training objects that will allow players to
    // train skills here.
    msk_setup_training(SS_LAYMAN, ({ SS_AWARENESS, SS_HERBALISM, SS_APPR_OBJ, 
        SS_APPR_MON, SS_ELEMENT_AIR, SS_FORM_DIVINATION }))->set_monk_trainer(esaria);
    msk_setup_training(SS_OCCUP, ({ SS_AWARENESS, SS_HERBALISM, SS_APPR_OBJ, 
        SS_APPR_MON, SS_ELEMENT_AIR, SS_FORM_DIVINATION }))->set_monk_trainer(esaria);
}


void
populate()
{
    if(!esaria)
        esaria = m_clone_here(MONK_NPC + "esaria", 0, "arm_me", " Leaning against "
            + "the corner of the room is a smiling, childlike female gnome.");

    if(!present(esaria))
        esaria->move_living("away", TO);
}

void
reset_room()
{
    populate();
}

