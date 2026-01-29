/*
 * monk_train.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

void
create_room()
{
/*    set_short("training room");*/
    set_short("tidy room");
/*
    set_long("This is the training room of the " +
             "monastery. Here you may learn new skills or improve old " +
             "ones, for a fee. To the west you see a darkened room. " +
             "To the east is a quiet alcove.\n");
*/
    set_long("Another tidy, empty room. The air in here is not as fresh as " +
             "in the others.\n");

/*    add_prop(ROOM_M_NO_ATTACK,
      "You can not do that while on Sacred ground.\n");*/
    add_prop(ROOM_I_INSIDE, 1); /* This is a real room */

    add_exit("monk_entr", "south");
    add_exit("monk_start", "west");
    add_exit("monk_kahedan_post", "east");
}
