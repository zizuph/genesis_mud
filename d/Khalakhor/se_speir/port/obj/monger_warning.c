/*
 * monger_warning.c
 *
 * This slip of paper is a message from the fishmonger to the goblins
 * he's hiding telling them to lie low, as someone is looking for them.
 * It's found randomly on the corpse of one of the goblins after they've
 * been killed by a player (or stolen, if the player's a decent thief).
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
    add_name(INVADE_QUEST_WARN_NAME);
    set_adj("small");
    add_adj("folded");
    set_short("small folded paper");
    set_long("The small folded paper contains a single line of " +
        "text, and you could probably read it.\n");

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

    papers = ({});

    if (!parse_command(str, TP, "[writing] / [text] [on] " +
       "[the] %i", papers))
    {
        if (str == "text" || str == "writing")
            paper = TO;
        else
            return 0;
    }

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
        write("It's a single line of text, and appears to be " +
            "a goblin dialect, but you don't understand enough " +
            "to read it.\n");
        return 1;
    }
    write("The writing is a single line:\n" +
          "    You were seen recently, the guard has someone\n" +
          "    looking for you. Lie low.\n" +
          "And to your shock, is signed:\n" +
          "    (fishmonger name here)\n" +
          "The fishmonger is a traitor!\n");
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_read, "read");
}
