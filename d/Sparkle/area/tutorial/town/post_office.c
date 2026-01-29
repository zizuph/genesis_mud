/*
 *  /d/Sparkle/area/tutorial/town/post_office.c
 *
 *  This is the Greenhollow Post Office. It teaches players about the
 *  mail system in Genesis.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma save_binary
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;
inherit "/d/Genesis/lib/post";

#include <stdproperties.h>

/* definitions */
#define  TUTORIAL_CHAPTER    26  /* the chapter for the sign */


/* prototypes */
public void        create_silverdell();
public void        init();
public void        hint(string arg);
public void        leave_inv(object ob, object to);
public void        mail_message(string new);


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("the Greenhollow Post Office");
    set_long("This is the Greenhollow Post Office. Here, you can send"
      + " and receive mail from all over the world. Using a post office"
      + " is quite simple, but you can read the tutorial sign for"
      + " specific help.\n\n");

    add_item( ({ "office", "post", "here", "building", "area",
                 "post office", "greenhollow post office",
                 "post office of greenhollow" }), long);

    add_indoor_items();

    add_door_items();
    prevent_attacks();
    reset_room();

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("street_4", "west");
} /* create_silverdell */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();
    post_init();

    add_action(hint, "hint");
} /* init */


/*
 * Function name:        hint
 * Description  :        give the player a hint if they get stuck
 * Arguments    :        string - what the player typed
 * Returns      :        int 1
 */
public int
hint(string arg)
{
    write("A hint? Hmmm ... there's really not much of a trick to using"
      + " the post office. If you are confused, reread the tutorial"
      + " sign and all should be clear.\n");
 
    return 1;
} /* hint */


/*
 * Function name:       reset_room
 * Description  :       restore npc as needed
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 */
void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    post_leave_inv(ob, to);
} /* leave_inv */


/*
 * Function name:        mail_message
 * Description  :        The message that we send the player when they
 *                       receive mail in the post office.
 * Arguments    :        string text - whether or not the mail is brand
 *                                    new or simply unread.
 */
void
mail_message(string text)
{
    string spaces = "          ";
    int len = (9 - strlen(text)) / 2;

    text = "    !" + spaces[..(len-1)] + "There is" + text +
        " mail for you in the Greenhollow post office." +
	spaces[..(8-len-strlen(text))] + "!";

    write("\n"
      + "    +--------------------------------------------------------------+\n"
      + text + "\n"
      + "    !          (North then north-east and east from Hilltop)       !\n"
      + "    +--------------------------------------------------------------+\n\n");
} /* mail_message */
