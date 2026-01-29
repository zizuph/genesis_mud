/*
 *  /d/Gondor/clubs/nisse/room/post.c
 *
 *  The Nisse Ohtar post office.
 *
 *  Tigerlily & Deagol, April 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Genesis/lib/post";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

/*
 *  Global variables
 */
string	text_on_sign =
            "The sign reads:\nTry <exa mailreader> to get the " +
            "information you need to use the post office.\n";

/*
 *  Prototypes
 */
int	read_sign(string str);

void
create_gondor()
{
    ::create_gondor();
    
    set_short("Post office of the Nisse Ohtar");
    set_long("This is the camp post office. As form follows function, " +
        "the room is very bare with only a counter and some simple " +
        "writing tools. You notice, however, that there is an empty " +
        "wooden crate on a shelf behind the counter. A sign " +
        "contains information on how to use the post.\n");
    add_item(({"shelf"}),
        "It is over there, behind the counter. An empty wooden crate lies " +
        "on it.\n");
    add_item(({"crate", "wooden crate"}),
        "The wooden crate is empty. You notice there are a few white " +
        "feathers and some spots of blood on it. There is a crude notice " +
        "nailed to the crate.\n");
    add_item(({"tools", "writing tools"}),
        "You see plenty of quills, ink-pots, scrolls and paper.\n");
    add_item(({"counter"}),
        "The counter is made from wood and is bare with the exception of a " +
        "writing stylus and some paper.\n");
    add_item(({"notice"}),
        "You examine the notice and see the words \"Pigeons for Rent\" " +
        "crudely marked out. Underneath it is written: \"No more pigeons " +
        "due to hawks!\"\n");
    add_item(({"sign"}), text_on_sign);

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(NISSE_ROOM_DIR + "path3", "out", 0, 0, 0);
}

/*
 *  Function name: read_sign
 *  Description  : Reads the sign.
 *  Arguments    : string str - as entered by the player
 *  Returns      : 0/1
 */
int
read_sign(string str)
{
    if (str == "sign")
    {
        write(text_on_sign);
        return 1;
    }

    return 0;
}

/*
 *  Function name: leave_inv
 *  Description:   Called when objects leave this container or when an
 *                 object is about to change its weight/volume/light status.
 *  Arguments:     ob: The object that just leaved this inventory
 *                 to: Where it went.
 */
void
leave_inv(object obj, object to)
{
    ::leave_inv(obj, to);

    post_leave_inv(obj, to);
}

void
init()
{
    ::init();

    add_action(read_sign, "read");
    post_init();
}
