/*
 *  /d/Sparkle/area/tutorial/pre_creation/1.c
 *
 *  These rooms are part of the character creation tutorial, which is
 *  intended to provide a more welcoming and helpful environment to
 *  people who are unfamiliar with mudding.
 *
 *  Created August 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/room";
inherit LIB_DIR + "skip";

#include <stdproperties.h>

/* prototypes */
public void        create_room();
public string      describe();
public void        init();
public string      sign_short();
public int         notify_gorboth();


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_name("1");
    set_short(sign_short);
    set_long(describe);

    add_item( ({ "sign", "tutorial", "tutorial sign" }), describe);

    add_cmd_item( ({ "sign", "tutorial", "tutorial sign" }),
                  ({ "read" }), describe);

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("2", "north", notify_gorboth, 1, 1);
} /* create_room */


/*
 * Function name:        describe
 * Description  :        provide the long description for the room
 * Returns      :        string - the room description
 */
public string
describe()
{
    if (!TUTORIAL_MASTER->query_tutorial(this_player()->query_real_name(),
        0))
    {
        TUTORIAL_MASTER->set_tutorial(this_player()->query_real_name(),
        0);
    }

    return read_file(TEXT_DIR + "intro", 0);
} /* describe */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(skip, "skip");
    add_action(tutorial_stat, "stats");
    add_action(tutorial_quit, "quit");
} /* init */


/*
 * Function name:        sign_short
 * Description  :        the short description will include in
 *                       parenthesis information about what the
 *                       sign teaches. If unread, tell the player.
 * Returns      :        string - the short description for the sign
 */
public string
sign_short()
{
    string  sign_txt = "a tutorial sign";

    if (!TUTORIAL_MASTER->query_tutorial(this_player()->query_real_name(),
         0))
    {
        return sign_txt + " (unread)";
    }

    return sign_txt + " (" + CHAPTER_TITLES[0] + ")";
} /* sign_short */


/*
 * Function name:        notify_gorboth
 * Description  :        tell gorboth stuff
 */
public int
notify_gorboth()
{
    string  pl = capitalize(this_player()->query_real_name());

    find_living("gorboth")->catch_msg("\n"
      + "    ****  " + pl + " enters the pre-creation! ****\n\n");
    log_move("2");
    return 0;
} /* notify_gorboth */

