/*
 * File:    stair_lower
 * Creator: Cirion, 1998.06.14
 * Purpose: Room in the monk's guild hall
 */
#pragma strict_types
#include "defs.h"

inherit ROOMBASE;

object          mzenska;

public void reset_room();


void
create_room ()
{
    set_short("stairwell");
    set_long("Aged blocks of rough stone make up the walls "
        + "of this circular stairwell. Smooth, worn stone steps "
        + "ascend into the darkness above."
        + " To the west is the "
        + "northern end of a great hall.\n");
    add_item(({"steps","stone"}),
        "The stone steps are worn smooth by the passage of "
        + "many feet.\n");


    WIZINFO("This is wizard info for the monks room.\n");

    // where, command
    add_exit("hall_lower_north", "west");
    add_exit("stair_upper", "up", VBFC_ME("try_up"));

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("up", "You descend the circular stairwell.\n");

    reset_room();

}

public int
try_up ()
{
    if (!present (mzenska))
        return 0;

    if (this_player ()->query_wiz_level ())
    {
        this_player ()->catch_msg (QCTNAME (mzenska) + " slides "
            + "respectfully out of your way.\nYou hear a whisper "
            + "in your mind: 'Welcome, wizard'.\n");
        return 0;
    }

    if (m_query_monk (this_player ()))
    {
        this_player ()->catch_msg (QCTNAME (mzenska) + " slides "
            + "out of your way.\n");
        return 0;
    }

    this_player ()->catch_msg (QCTNAME (mzenska) + " slithers across your "
        + "path.\n");
    say (QCTNAME (mzenska) + " slithers across the path of "
        + QTNAME (this_player ()) + ", blocking "
        + this_player ()->query_possessive () + " path.\n");

    mzenska->command ("emote hisses threateningly.");
    return 1;
}

private void
populate()
{
    if(!mzenska)
        mzenska = m_clone_here(MONK_NPC + "mzenska", 0, "arm_me", " Lying "
            + "at the base of the stair is a long, sinuous fire lizard, "
            + "casually observing his surroundings with ruby-red eyes.");

    if(!present(mzenska))
        mzenska->move_living("away", TO);
}

public void
reset_room()
{
    populate();
}

