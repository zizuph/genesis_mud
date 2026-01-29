/*
 *  /d/Sparkle/area/tutorial/review/skip.c
 *
 *  This module allows players to skip past the review.
 *
 *  Created May 2011, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"
#include <macros.h>


/* prototypes */
public int         skip(string arg);
public int         tutorial_quit(string arg);


/* Function name:        skip
 * Description  :        allow players to skip the review
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
skip(string arg)
{
    string  word = query_verb();

    if (arg != "review")
    {
        write("If you'd like to get out of here, just type <"
          + word + " review>.\n");
        return 1;
    }

    tell_room(environment(this_player()), QCTNAME(this_player())
      + " disappears in a flash of light!\n", this_player());
    write("Light flashes, and you feel yourself magically transported!\n");

    this_player()->move_living("M", TOWN_DIR + "library2", 1);

    tell_room(environment(this_player()), QCTNAME(this_player())
      + " appears in a flash of light!\n", this_player());

    return 1;
} /* skip */


/*
 * Function name:        tutorial_quit
 * Desciption   :        we want to see if players have quit the
 *                       game, and where
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1: don't let them quit yet,
 *                           0: let them quit and log it
 */
public int
tutorial_quit(string arg)
{
    if (!this_player()->query_prop(TUTORIAL_QUIT_PROP))
    {
        write("Quitting in frustration? You can <skip> the review"
          + " and return to the library if you wish. Type <quit> again"
          + " if you really want to quit.\n");

        setuid();
        seteuid(getuid());

        this_player()->add_prop(TUTORIAL_QUIT_PROP, 1);
        return 1;
    }

    return 0;
} /* tutorial_quit */