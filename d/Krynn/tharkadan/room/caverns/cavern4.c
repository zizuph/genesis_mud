#include "/d/Krynn/common/defs.h"
#include "../../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit CAVERNS_BASE;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"cave",}));

void
reset_tharkadan_room()
{
    set_searched(0);
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(CAVERNS + "cavern3","southeast",0);
    add_exit(CAVERNS + "cavern5","north",0);

    add_prop(ROOM_S_DARK_LONG, "A dark, cold cavern. Without a light " +
          "source it is too dark to see in here.\n"); 
    add_prop(ROOM_S_DARK_MSG, "The cavern is too dark to"); 
    add_prop(ROOM_I_LIGHT, DARKNESS_PASSIVE);

    add_item(({"cold cavern","cavern","throat"}),
        "You stand on a rough ridge overlooking a great cavern that " +
        "disappears down into darkness below. Once the throat of an " +
        "ancient volcano, it could potentially lead to the centre of " +
        "the earth! Or at least a very long way down...\n");
    add_item(({"vent","lava vent"}),
        "An exit out of the volcano is here, through what was once a " +
        "lava vent.\n");
    add_item(({"ridge","rough ridge","ridge of basalt"}),
        "A rough ridge along the side of the cavern leads down into " +
        "darkness.\n");
    add_item(({"basalt"}),
        "The rough ridge beneath your feet is of a fine-grained " +
        "volcanic rock known as basalt.\n");
    add_item(({"volcano","ancient volcano"}),
        "You stand within the throat of what was once an ancient " +
        "volcano, long dormant. Over time its great vent above you " +
        "filled with ice and fell in on itself, creating the great " +
        "cavern you now overlook.\n");

    add_cmd_item(({"into cavern","cavern"}), "jump", "Self preservation " +
        "insists that jumping into the cavern would be suicide. You " +
        "don't do it.\n");
    add_cmd_item(({"down","down cavern","down ridge","into cavern"}),
        "climb", "You look around the edge of the ridge here for " +
        "handholds to climb down but can't find any.\n");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs), ONE_OF(herbs) }), ({ "cavern","ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "a dark, cold cavern within an ancient volcano";
}

string
long_descr()
{
    return "You stand on the edge of a cavern that was once part of " +
        "the throat of an ancient volcano, now long dormant. A rough " +
        "ridge of basalt runs down to your north along the edge of " +
        "the cavern into darkness, while rises to your southeast.\n";
}

