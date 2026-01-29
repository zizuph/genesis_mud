/*
 *  /d/Sparkle/area/tutorial/obj/sign.c
 *
 *  The signpost which prints out the tutorial for new
 *  players in Genesis.
 *
 *  Created August 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/object";

#include <stdproperties.h>


/* Global Variables */
public int         Chapter; /* the chapter of the tutorial */
public string      Name;    /* what it is if not a sign */


/* Prototypes */
public void        create_object();
public string      sign_short();

public void        set_chapter(int i) { Chapter = i; }

/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("_tutorial_sign");
} /* create_object */


/*
 * Function name:        config_sign
 * Description  :        set up the sign, called from the object
 *                       which clones the sign
 * Arguments    :        string name - the name of the object
 */
public void
config_sign(string s)
{
    Name = s;

    add_name( ({ Name }) );
    add_adj( ({ "large", "mounted", "tutorial" }) );

    set_short(sign_short);
    set_long("A tutorial " + Name + " has been posted here. To see what"
      + " is written on it, you can use the command <read " + Name
      + ">.\n");

    add_item( ({ "post", Name + "post" }),
        "The " + Name + " is mounted on a sturdy post.\n");

    setuid();
    seteuid(getuid());

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_M_NO_GET, "The " + Name + " is mounted on a sturdy post,"
     + " and cannot be taken.\n");
} /* config_sign */


/*
 * Function name:        describe
 * Description  :        give a text description of the tutorial
 * Returns      :        string - the tutorial chapter
 */
public int 
command_read()
{
    if (!TUTORIAL_MASTER->query_tutorial(this_player()->query_real_name(),
        Chapter))
    {
        TUTORIAL_MASTER->set_tutorial(this_player()->query_real_name(),
            Chapter);

        if (present("_tutorial_journal", this_player()))
        {
            this_player()->catch_tell("\nAs you read,"
              + " You copy chapter " + Chapter + " into your"
              + " tutorial journal.\n");
        }
    }

    write(read_file(TEXT_DIR + "chapter_" + Chapter, 0));
    return 1;
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
    string  sign_txt = "tutorial " + Name;

    if (!TUTORIAL_MASTER->query_tutorial(this_player()->query_real_name(),
         Chapter))
    {
        return sign_txt + " (unread)";
    }

    return sign_txt + " (" + CHAPTER_TITLES[Chapter] + ")";
} /* sign_short */


/*
 * Function name:        scribe_chapter
 * Description  :        tell the player that they have copied a
 *                       chapter into their journal
 * Arguments    :        object who  - the player,
 *                       int chapter - the chapter number
 */
public void
scribe_chapter(object who, int chapter)
{
    if (!present("_tutorial_journal", who))
    {
        return;
    }

    who->catch_tell("You copy chapter " + chapter + " into your"
      + " tutorial journal.\n");
    return;
} /* scribe_chapter */



