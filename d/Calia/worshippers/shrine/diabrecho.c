
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
    set_short("The Chamber of Lord Diabrecho");
    set_long("This is the Chamber of Lord Diabrecho.  The walls "+
        "are made of a deep blue marble with light blue and white "+
        "swirls set into them.  In the centre of "+
        "the room you see a large statue of Lord Diabrecho sitting "+
        "on a throne.  This chamber is very clean, and very quiet.  "+
        "You can head back out to the shrine to the southwest.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_item("statue","This statue is very large.  It measures "+
        "about 5 feet across at the base of the throne, and stands "+
        "about 5 feet high at it's highest point.  It is carved out of "+
        "a beautiful block of ice that seems to radiate power from "+
        "within itself.  It depicts Lord Diabrecho sitting on his "+
        "throne, sceptre in hand, surrounded by a few of his guards.  "+
        "The eyes of the statue glow a bright blue.\n");

    add_exit(WOR_SHRINE+"common","southwest");
}

int
do_worship(string str)
{
    if (!str || str != "Lord Diabrecho")
    {
        notify_fail("Worship whom?\n");
        return 0;
    }
    write("You worship the statue of Lord Diabrecho.\n");
    say(QCTNAME(TP)+" worships the statue of Lord Diabrecho.\n");
    return 1;
}
void
init()
{
    ::init();
    add_action("do_worship","worship");
}
