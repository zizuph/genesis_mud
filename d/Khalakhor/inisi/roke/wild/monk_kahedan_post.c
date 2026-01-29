/*
 * monk_kahedan_post.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Coded by Amelia
 *  4/5/98
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
/*inherit "/d/Genesis/lib/post";*/

#include <stdproperties.h>

void
create_room()
{
/*    set_short("The Kahedan post office");*/
    set_short("small dusty alcove");
/*
    set_long("This is a small quiet alcove " +
             "where you can send and receive mails in peace. " +
             "There are now aliases here for council and elders, " +
             "as in <mail elders> or <mail council>. " +
             get_std_use());
*/
    set_long("This is a small, dusty alcove.\n");
/*    add_prop(ROOM_I_IS, 1); */ /* Why was this here? */
    add_prop(ROOM_I_INSIDE, 1);
/*    add_prop(ROOM_M_NO_ATTACK, "I don't think so!\n");*/

    add_exit("monk_train", "west");
}

/*
void
init()
{
    ::init();
    post_init();
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}
*/
