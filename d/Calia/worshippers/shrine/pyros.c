
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
    set_short("The Chamber of Lord Pyros");
    set_long("This is the Chamber of Lord Pyros.  The walls are "+
        "made of a deep red marble with orange and gold swirls "+
        "set into them.  In the centre of the room you see a large "+
        "statue of Lord Pyros rising out of a large flaming area.  "+
        "This chamber is very clean, and very quiet.  You can head "+
        "back out to the shrine to the northwest.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_item("statue","This statue is very large.  It measures "+
        "about 8 feet across at the base of the flaming area, and "+
        "stands about 6 feet high at it's highest point.  It is "+
        "carved out of some sort of glowing rock that seems to "+
        "pulse with power.  There is incredible heat emanating from "+
        "it.  It depicts Lord Pyros rising out of the flaming ground, "+
        "hands rising above his head.  The eyes of the statue "+
        "glow bright yellow.\n");

    add_exit(WOR_SHRINE+"common","northwest");
}

int
do_worship(string str)
{
    if (!str || str != "Lord Pyros")
    {
        notify_fail("Worship whom?\n");
        return 0;
    }
    write("You worship the statue of Lord Pyros.\n");
    say(QCTNAME(TP)+" worships the statue of Lord Pyros.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action("do_worship","worship");
}

