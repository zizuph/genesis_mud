
 /* Jaacar 06 JUN 95 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>
#include "defs.h"
#include STONE_HEADER
#include COUNCIL_HEADER
void
create_room()
{
    set_short("In the Chamber of Lady Gu");
    set_long("This is the Chamber of Lady Gu.  The walls are "+
        "made of a dark brown marble with light brown and "+
        "gold swirls set into them.  In the centre of "+
        "the room you see a large statue of Lady Gu standing "+
        "atop a mountain.  This chamber is very clean, and very "+
        "quiet.  You can head back out to the shrine to the "+
        "northeast.\n");

    add_item("statue","This statue is very large.  It measures "+
        "about 10 feet across at the base of the mountain, and "+
        "stands almost 15 feet high at it's highest point.  It is "+
        "carved out of a golden sandstone that vibrates with "+
        "energy.  It depicts Lady Gu standing atop of a newly "+
        "risen mountain.  The eyes of the statue shine like diamonds.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_exit(WORSHIP_SHRINE+"common","northeast");
}
int
do_worship(string str)
{
    if (!str || str != "Lady Gu")
    {
        notify_fail("Worship whom?\n");
        return 0;
    }
    write("You worship the statue of Lady Gu.\n");
    say(QCTNAME(TP)+" worships the statue of Lady Gu.\n");
    return 1;
}
void
init()
{
    ::init();
    add_action("do_worship","worship");
}
