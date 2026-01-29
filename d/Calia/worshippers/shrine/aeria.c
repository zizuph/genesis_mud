
 /* Jaacar 06 JUN 95 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>
#include "defs.h"

void
create_room()
{
    set_short("The Chamber of Lady Aeria");
    set_long("This is the Chamber of Lady Aeria.  The walls are "+
        "made of a light blue marble with white swirls set into "+
        "it.  In the centre "+
        "of the room you see a large statue of Lady Aeria floating "+
        "magically above some clouds.  This chamber is very clean, "+
        "and very quiet.  You can head back out to the shrine to "+
        "the southeast.\n");
    add_prop(ROOM_I_INSIDE,1);

    add_item("statue","This statue is very large.  It measures "+
        "about 4 feet across at the base of the clouds, and stands "+
        "about 6 feet high at it's highest point.  It is carved out "+
        "of a transparent crystal, glowing with power.  It depicts Lady "+
        "Aeria floating above the lands, watching over her "+
        "peoples.  The eyes of the statue seem to sparkle an "+
        "emerald green.\n");

    add_exit(WOR_SHRINE+"common","southeast");
}

int
do_worship(string str)
{
    if (!str || str != "Lady Aeria")
    {
        notify_fail("Worship whom?\n");
        return 0;
    }
    write("You worship the statue of Lady Aeria.\n");
    say(QCTNAME(TP)+" worships the statue of Lady Aeria.\n");

    return 1;
}

void
init()
{
    ::init();
    add_action("do_worship","worship");
}
