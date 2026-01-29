/*
 * File:    
 * Creator: Cirion, 1998.06.14
 * Purpose: Room in the monk's guild hall
 * Modified:
 *    1998.07.15 Cirion added voting capability
 */
#pragma strict_types
#include "defs.h"

inherit ROOMBASE;

void
create_room ()
{
    set_short("meeting room");
    set_long("A long, smooth table of polished mahogany extends "
        + "along the length of this warm, sparsely adorned room. Running "
        + "up the stone walls are carved wooden beams painted in "
        + "dull, earth-tone reds. A small round window looks down "
        + "on a garden in the south wall. To the west is the "
        + "southern end of a large hall. A red cloth curtain blocks "
        + "a doorway to the east.\n");
    add_item(({"window","glass","glass window","garden window"}),
        "The window is perfectly round, and about the size "
        + "of a human head. It is made from paper-thin, rose "
        + "tinted glass. It looks out over the peaceful "
        + "gardens below. Framing the window are thin panes "
        + "of wood, and running horizontal across the centre "
        + "is a single oak slat of wood.\n");
    add_item(({"beam","beams","wood","wooden beam","wooden beams"}),
        "The beams supporting this room are very very "
        + "thick. They are made from strong wood, and are "
        + "painted a dull red-brown colour.\n");
    add_item(({"slat","oak","single slat","oak slat"}),
        "It runs horizontal through the center of the "
        + "circular window.\n");
    add_item(({"curtain","cloth curtain","red curtain","red cloth curtain"}),
        "Beyond the curtain, the elders meditate upon their "
        + "duties.\n");
    add_item(({"table","long table","mahogany table","polished table"}),
        " This table would be the envy of any lord. "
        + "Centuries old, it has countless layers of beeswax "
        + "rubbed into the surface. The wax traps available "
        + "light and sets the deep reddish hints of the "
        + "mahogany aglow.\n");
    add_item(({"pane","panes"}),
        " There are panes of rose-tinted glass framed by "
        + "thin panes of wood.\n");


    WIZINFO("This is the meeting room of the monks guild, where lies "
        + "the guild board.\n");

    // where, command
    add_exit("hall_upper_south", "west");
    add_exit("council", "east");

    // clone the board here
    m_clone_here(MONKBOARD);
}


void
init()
{
    ::init();

    m_vote_init();
}

public void enter_inv (object who, object from)
{
    ::enter_inv (who, from);
    vote_enter_inv (who, from);
}

