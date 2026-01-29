/*
 *  /d/Sparkle/area/tutorial/lib/skip.c
 *
 *  This module allows players to skip past the beginning of the tutorial.
 *  Additionally, it tracks players who quit before entering creation.
 *
 *  Created August 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "/d/Genesis/start/newbie/newbie.h"
#include "../defs.h"
#include <login.h>
#include <macros.h>


/* prototypes */
public int         skip(string arg);
public int         tutorial_stat(string arg);
public int         tutorial_quit(string arg);
public void        log_move(string where);


/* Function name:        skip
 * Description  :        allow players to skip the tutorial
 * Arguments    :        string arg - what the player typed
 * Returns      :        int 1 - success, 0 - failure
 */
public int
skip(string arg)
{
    object sword;
	
	sword = present("_pre_creation_sword", this_player());
	
	if (objectp(sword))
    {
        sword->remove_object();
        write("\nYou can't skip with the sword, let's remove that.\n");
		write("\nYour sword disappears in a flash of light!\n\n");
		write("Now you can <skip tutorial> if you like.\n");
		return 1;
		
    }
	
	if (arg != "tutorial")
    {
        write("If you don't need the tutorial, type <skip tutorial>.\n");
        return 1;
    }

    tell_room(environment(this_player()), QCTNAME(this_player())
      + " disappears in a flash of light!\n", this_player());
    write("Light flashes, and you feel yourself magically transported!\n");
	
	   

    /* Benevolence! Keeping the spammy log in the hope that Gorboth will
     * one day actually read it. */
    if (file_size(LOG_DIR + "moves") > 100000)
	rename(LOG_DIR + "moves", LOG_DIR + "moves.old");
    write_file(LOG_DIR + "moves", ctime(time())
      + " " + this_player()->query_name() + " >>skipped<< from "
      + this_object()->query_name() + " to creation.\n");

    this_player()->move_living("M", TUTORIAL_DIR + "town/hilltop", 1, 0);

    tell_room(environment(this_player()), QCTNAME(this_player())
        + " appears through the shimmering blue portal!\n", this_player());

    return 1;
} /* skip */


/*
 * Function name:        tutorial_stat
 * Description  :        when ghosts stat themselves, it produces a
 *                       runtime error. We'll create a mask here.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 - caught something, 0 - fail
 */
public int
tutorial_stat(string arg)
{
    if (strlen(arg))
    {
        write("Curious aren't we?\n");
        return 1;
    }

    write("In your ghostlike state, that is impossible.\n");
    return 1;
} /* tutorial_stat */


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
        write("Quitting so soon? Remember, you can <skip tutorial> to"
          + " return to Greenhollow if you wish. Type <quit> again"
          + " if you really want to quit.\n");

        setuid();
        seteuid(getuid());

        this_player()->add_prop(TUTORIAL_QUIT_PROP, 1);
        return 1;
    }

    write_file(LOG_DIR + "quit", ctime(time())
      + " " + this_player()->query_name() + " quit at "
      + this_object()->query_name() + ".\n");
    return 0;
} /* tutorial_quit */


/*
 * Function name:        log_move
 * Description  :        log the movements of players as they try to
 *                       figure out the pre-creation
 * Arguments    :        string where  - the room we are entering
 */
public void
log_move(string where)
{
    /* Benevolence! Keeping the spammy log in the hope that Gorboth will
     * one day actually read it. */
    if (file_size(LOG_DIR + "moves") > 100000)
	rename(LOG_DIR + "moves", LOG_DIR + "moves.old");
    write_file(LOG_DIR + "moves", ctime(time())
      + " " + this_player()->query_name() + " moved from "
      + this_object()->query_name() + " to " + where + ".\n");
} /* log_move */
