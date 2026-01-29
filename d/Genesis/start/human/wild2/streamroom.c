/* Streamroom
 * 2010/08/23 Lavellan Common stream-drinking stuff for Sparkle wilds.
 */

#pragma strict_types

inherit "/std/room";

#include <macros.h>     /* for QCTNAME */

#include "wild.h"

void
create_room()
{
    add_cmd_item( ({ "from stream", "water", "water from stream" }),
        "drink", "@@drink" );
    add_prop(OBJ_I_CONTAIN_WATER, -1);
}

/*
 *  Adapted from Sparkle well code.. No drinking lib/mudlib support?
 */
string
drink()
{
    int     i;

    /* Drink small amounts up to 500 soft */ 
    for (i = 0; i < 10; i++)
    {
        if (!this_player()->drink_soft(50))
        {
            /* Can't drink any more */
            break;
        }
    }

    if (i == 0)
    {
        return "You are too full to drink any water.\n";
    }

    say(QCTNAME(this_player()) + " drinks some water from the stream.\n");

    if (!this_player()->drink_soft(50, 1))
    {
        return "You drink a little water from the stream. You feel full now.\n";
    }
    else
    {
        return "You drink a little water from the stream.\n";
    }
}


string
drinkpond()
{
    int     i;

    /* Drink small amounts up to 500 soft */ 
    for (i = 0; i < 10; i++)
    {
        if (!this_player()->drink_soft(50))
        {
            /* Can't drink any more */
            break;
        }
    }

    if (i == 0)
    {
        return "You are too full to drink any water.\n";
    }

    say(QCTNAME(this_player()) + " drinks some water from the pond.\n");

    if (!this_player()->drink_soft(50, 1))
    {
        return "You drink a little water from the pond. You feel full now.\n";
    }
    else
    {
        return "You drink a little water from the pond.\n";
    }
}