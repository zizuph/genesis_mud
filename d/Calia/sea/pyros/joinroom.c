
 /* Digit 03 FEB 95 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>
#include "defs.h"
#include FIRE_HEADER
#include "join.c"


int
is_fire(object living)
{
    return living->query_guild_name_occ() == GUILD_NAME;
}

void
create_room()
{
    set_short("A strange room");
    set_long("You find yourself standing in the middle of a "+
        "large circle of flames.  The walls can be seen through "+
        "the flames, and are bright white in colour save one "+
        "patch on the south wall which is shimmering a bright red, "+
        "almost blood red.  A voice is echoing throughout the room "+
        "saying 'Dedicate your life to me!  Dedicate your life to "+
        "Pyros!'.  "+
        "\n");
}

void
init()
{
    ::init();
    add_action("do_join","dedicate");
    add_action("do_enter","enter");
}

int
do_enter(string str)
{
    if (str !="flames")
    {
        notify_fail("Enter what?  Flames?\n");
        return 0;
    }
    write("You start to step into the flames, but decide against "+
        "it at the last moment as they are very hot.  A voice echoes "+
        "throughout the room 'Fool!  Dedicate your life to me!  "+
        "Dedicate your life to Pyros!'.\n");
    return 1;
}
