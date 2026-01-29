/*
 *  /d/Sparkle/area/tutorial/pre_creation/3.c
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
inherit LIB_DIR + "lib_sign";

/* definitions */
#define  TUTORIAL_CHAPTER    3  /* the chapter for the sign */

#include <stdproperties.h>

/* prototypes */
public void        create_room();
public string      describe();
public void        reset_room();
public void        init();
public string      sign_short();


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_name("3");
    set_short(sign_short);
    set_long(describe);

    add_item( ({ "sign", "tutorial", "tutorial sign" }), describe);

    add_cmd_item( ({ "sign", "tutorial", "tutorial sign" }),
                  ({ "read" }), describe);

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("4", "east", &log_move("4"), 1, 1);
    add_exit("2", "south", &log_move("2"), 1, 0);

    reset_room();
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
        2))
    {
        TUTORIAL_MASTER->set_tutorial(this_player()->query_real_name(),
        2);
    }

    return read_file(TEXT_DIR + "chapter_2", 0);
} /* describe */


/*
 * Function name:       reset_room
 * Description  :       restore signs and npcs as needed
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER, "note");
    }
} /* reset_room */


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
         2))
    {
        return sign_txt + " (unread)";
    }

    return sign_txt + " (" + CHAPTER_TITLES[2] + ")";
} /* sign_short */



