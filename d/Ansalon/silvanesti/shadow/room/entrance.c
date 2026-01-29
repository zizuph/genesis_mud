#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/shadow/local.h"
#include <ss_types.h>
#include <macros.h>
inherit SHADOW_IN;

void
reset_shadow_room()
{
    return;
}

create_shadow_room()
{
    set_short("Cavern entrance");
    set_long("@@long_descr");

    add_item("floor","The floor of the cavern is made of the "+
        "same granite as the rock.  It leads from the entrance "+
        "to a drop of twenty feet.\n");
    add_item("drop","You estimate twenty feet to the lower level.\n");
    add_item("wall","It looks like you will have no difficulty "+
        "getting down to the lower level.\n");

    add_prop(ROOM_I_LIGHT, 0);
    add_exit(SROOM + "tunnel01","down",0);
    add_exit("/d/Ansalon/silvanesti/kurinost/room/rock","out",0);

    reset_shadow_room();
}

string
long_descr()
{
    return "You are at the entrance of a cave system in the " +
        "Silvanesti forest.  No natural light is able to " +
        "penetrate more than a few feet in.  The floor of " +
        "the cave stops abruptly two steps in front of you " +
        "and you estimate the drop to the level below is " +
        "about twenty feet.  Luckily, the wall looks rough " +
        "enough to climb down with little trouble.\n";
}
