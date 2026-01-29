/*
 *  /d/Emerald/common/guild/aod/rooms/post.c
 *
 *  This is the Post Office for the Army of Darkness.
 *
 *  Created July 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit AOD_ROOM_DIR + "cave_room";
inherit AOD_LIB_DIR + "add_spike";
inherit "/d/Genesis/lib/post";

#include <files.h>
#include <mail.h>

/* prototypes */
public void        create_cave_room();
public void        leave_inv(object ob, mixed to);
public void        mail_message(string new);


/*
 * Function name:        create_cave_room
 * Description  :        set up the room
 */
public void
create_cave_room()
{
    set_short("the Army of Darkness post office");
    set_em_long("This chamber is filled with Darkling Magic. Because"
      + " ogres are far too stupid to read and write, spells have been"
      + " fashioned here which assist in the process of written"
      + " communication. Huge purple flames levitate above the"
      + " floor, and slowly move around the room. Though you are"
      + " too stupid to know how, really, it seems you are able to"
      + " <mail> someone here just as if you were a literate being.\n");

    add_item( ({ "chamber", "area", "here" }), long);
    add_item( ({ "post", "post office", "office" }),
        "An ogre post office ... will wonders never cease!\n");
    add_item( ({ "magic", "darkling magic" }),
        "The Darkling Magic exists in the form of large purple flames"
      + " which slowly bob and weave around the room.\n");
    add_item( ({ "flame", "flames", "purple flame", "purple flames",
                 "huge purple flames", "huge purple flame" }),
        "Whenever an ogre is ready to read or write mail, these flames"
      + " wander over, envelop him, and actually animate his arms so"
      + " that what is in his mind ends up on paper. How delicious!\n");

    add_cave_items();
    add_spike("post");

    add_exit("tunnel2", "southwest");
} /* create_cave_room */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();
    post_init();
} /* init */


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 */
public void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
} /* leave_inv */


/*
 * Function name:        mail_message
 * Description  :        The message that we send the player when they
 *                       receive mail in the post office.
 * Arguments    :        string new - whether or not the mail is brand
 *                                    new or simply unread.
 */
void
mail_message(string new)
{
    string text;

    if (new == " NEW")
    {
        text = "    !   There is NEW mail for you in the Army of Darkness"
             + " post office.  !";
    }
    else if (new == " UNREAD")
    {
        text = "    ! There is UNREAD mail for you in the Army of"
             + " Darkness post office. !";
    }
    else
    {
        return;
    }
    
    write("\n"
      + "    +-----------------------------------------------------------"
      + "--------+\n"
      + text + "\n"
      + "    +-----------------------------------------------------------"
      + "--------+\n\n");
} /* mail_message */

