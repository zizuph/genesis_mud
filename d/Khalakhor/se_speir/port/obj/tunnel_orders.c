/*
 * tunnel_orders.c
 *
 * This scrap of paper contains the orders for the goblin soldiers
 * hiding in the tunnels beneath the fishmonger's shop in the village.
 * It is found by searching the hay paddocks in the different living
 * quarters, and is in a different room, randomly placed, every time.
 * It serves as partial proof of the fishmonger's treason in the port
 * macdunn invasion quest.
 *
 * Khail - April 20/97
 */
#pragma strict_types

#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "../invade_quest.h"

inherit "/std/object";

public void
create_object()
{
    set_name("paper");
    add_name("scrap");
    add_name("INVADE_QUEST_DETAILS_NAME");
    set_adj("crumpled");
    add_adj("dirty");
    set_short("crumpled dirty paper");
    set_long("The paper contains some words and drawings scrawled " +
        "in a rather crude hand, which might be readable.\n");

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 0);
}

public int
do_read(string str)
{
    mixed papers;
    object paper;

    NF("Read what?\n");

    if (!str || !strlen(str))
        return 0;

    if (!parse_command(str, TP, "[the] %i", papers))
        return 0;

    if (papers[0] == 0)
    {
        if (sizeof(papers) > 2)
        {
            NF("You can only read one paper at a time.\n");
            return 0;
        }
        else
            paper = papers[1];
    }
    else if (papers[0] > 0)
    {
        if (papers[0] > 1)
        {
            NF("You can only read one paper at a time.\n");
            return 0;
        }
        else
            paper = papers[1];
    }
    else
        paper = papers[-papers[0]];

  /* Ok, now we've figured out exactly which paper object the player */
  /* is trying to read. If it's not this one, return 0. */
    if (paper != TO)
        return 0;

  /* See if the player's language is high enough to read the gobbo */
  /* clan scrawling. */
    if (TP->query_skill(SS_LANGUAGE) < MIN_LANGUAGE_LIMIT)
    {
        write("You can't make any sense out of any of the writing, " +
            "it's in a dialect that looks like goblin, but you " +
            "don't understand it well enough to translate. However, " +
            "you can see sketches of what might be the village with " +
            "a few notes made, a list of meaningless numbers, and a " +
            "handful of longer notes at the bottom.\n");
        return 1;
    }
    write("You recognize the goblin dialect the words on the paper " +
        "are written in, and easily translate it. The paper is fairly " +
        "interesting, it looks like it's divided into three sections. " +
        "In the first, a few rough sketches of the village with a few " +
        "marks at various points and a list of times beside them, " +
        "which in itself doesn't mean much to you. The second part " +
        "is some sort of table of times and names. The third part " +
        "is a message of some sort, and although you recognize the " +
        "words, they're complete gibberish.\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_read, "read");
}
