/*
 *  /d/Sparkle/area/tutorial/obj/plaque.c
 *
 *  A special version of the signpost which prints out the tutorial for
 *  new players in Genesis.
 *
 *  Created August 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/object";

#include <stdproperties.h>


/* Global Variables */
public int         Chapter;


/* Prototypes */
public void        create_object();
public string      describe();
public string      sign_short();

public void        set_chapter(int i) { Chapter = i; }

/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("plaque");
    add_name("_tutorial_plaque");
    add_adj( ({ "large", "mounted" }) );

    set_short(sign_short);
    set_long(describe);

    add_cmd_item( ({ "plaque", "large plaque", "mounted plaque",
                     "large mounted plaque" }),
                  ({ "read" }), describe);

    setuid();
    seteuid(getuid());

    add_prop(OBJ_M_NO_GET, "The plaque is securely mounted, and cannot"
      + " be taken.\n");
} /* create_object */


/*
 * Function name:        describe
 * Description  :        give a text description of the plaque
 * Returns      :        string - the description
 */
public string
describe()
{
    if (!TUTORIAL_MASTER->query_read_sign(this_player()->query_real_name(),
        Chapter))
    {
        TUTORIAL_MASTER->set_read_sign(this_player()->query_real_name(),
            Chapter);
    }

    return read_file(TEXT_DIR + "chapter_" + Chapter, 0);
} /* describe */


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
    string  sign_txt = "large mounted plaque";

    if (!TUTORIAL_MASTER->query_read_sign(this_player()->query_real_name(),
         Chapter))
    {
        return sign_txt + " (unread)";
    }

    return sign_txt + " (" + CHAPTER_TITLES[Chapter] + ")";
} /* sign_short */
