
 /* Digit 06 JUN 95 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include "defs.h"
#include FIRE_HEADER
#include "ash.h"

int
is_walker(object living)
{
    return living->query_guild_name_occ() == GUILD_NAME;
}

void
create_room()
{
    set_short("In a flaming chamber");
    set_long("This chamber does not seem to be carved out, but rather "+
        "burned out of the rock by the large flame you see before the "+
        "northern wall.  The flame lights the entire area with an eerie "+
        "orange glow and causes shadows to dance on the walls around "+
        "you.  The only way out of this flaming chamber appears to "+
        "be back to the south.\n");

    add_item("flame","After closer examination you discover "+
        "that the flame originates where the wall meets the "+
        "floor of this chamber.  It is giving off no heat, "+
        "yet when you touch it, it burns.  It is orange and "+
        "red in colour at the top, and a very light blue at "+
        "the bottom.  On the floor by the flame is some ash.\n");

    add_item("ash","There is a pile of ash where the flame meets "+
        "with the wall.  You could probably collect some if you wanted.\n");

    add_exit(CAVE+"room59","south");
}

void
init()
{
    ::init();
    add_action("do_enter","enter");
    add_action("do_collect","collect");
}

do_enter(string str)
{
    NF("Enter what?  The flame perhaps?\n");
    if (!str || str != "flame")
        return 0;
    if (!is_walker(TP))
    {
        write("You step into the flame and get burned badly!\n");
        TP->heal_hp(-(random(200)));
        say(QCTNAME(TP)+" steps into the flame, gets "+
            "burned badly, and jumps back.\n");
        return 1;
    }
    write("You step into the flames.\n");
    say(QCTNAME(TP)+" steps into the flame and "+
        "disappears!\n");
    tell_room(SHRINE+"entrance",QCTNAME(TP)+
        " appears in a column of flame!\n");
    TP->move_living("M",SHRINE+"entrance",1,0);
    return 1;
}
