
 /* Digit 03 FEB 95 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "defs.h"
#include FIRE_HEADER

int
is_fire(object living)
{
    return living->query_guild_name_occ() == GUILD_NAME;
}


void
create_room()
{
    set_short("In a dark tunnel");
    set_long("You are standing in a dark tunnel.  Warm air is "+
        "flowing in from the south, probably from the river.  "+
        "There is a mark of some sort on the wall.  The only "+
        "exit is back to the south.  "+
        "The walls here have been expertly carved from the "+
        "basalt of this cavern.  They have been carefully "+
        "smoothed so there are no rough edges protruding, "+
        "except for the one mark.  "+
        "\n");

    add_item(({"walls","wall","basalt"}),"The walls are very "+
        "smooth here unlike most of the rest of this cavern.\n");
    add_item("mark","It appears to be a hand print and looks as "+
        "though your hand might fit if you placed it into it.\n");

    add_exit(CAVE+"room52","south");

}

void
init()
{
    ::init();
    add_action("do_place","place");
}

do_place(string str)
{
    object tp = this_player();
    notify_fail("Place what where?\n");
    if (!str)
        return 0;
    if ((str != "hand into mark") && (str != "hand in mark"))
        return 0;

    if (is_fire(tp))
    {
        notify_fail("You are already a member of the Firewalkers!\n");
        return 0;
    }

    if (!present("_fchosen_", TP))
    {
        notify_fail("Nothing happens.\n");
        return 0;
    }
    write("You suddenly feel dizzy.\n");
    say(QCTNAME(TP)+" is suddenly engulfed in flames and disappears!\n");
    TP->move_living("M",CAVE+"joinroom");
    return 1;
}
