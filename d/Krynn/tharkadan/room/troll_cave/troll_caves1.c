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

    add_exit(ROOM + "path16","out","@@enter_canyon");
    add_exit(TROLL_CAVES + "troll_caves2","east",0);
    add_exit(TROLL_CAVES + "troll_caves8","south",0);
 
    add_prop(ROOM_I_LIGHT, DARKNESS_PASSIVE);

    add_item(({"narrow cave","cave","cave network","network"}),
        "You stand within a narrow cave network that runs through " +
        "the Tharkadan mountain range. The roof here is quite low " +
        "making you feel claustrophobic, and there is a rank " +
        "animalistic smell that makes you think that this cave network " +
        "is occupied.\n");
    add_item(({"stalagmites","thin stalagmites", "low roof","roof"}),
        "The roof here is covered with thin stalagmites, reminding you " +
        "of milky white icicles or finger nails reaching down for you.\n");
    add_item(({"exit"}),"There is an exit out of the cave networth to " +
        "your northwest.\n");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs), ONE_OF(herbs) }), ({ "vent","ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "a narrow cave within the Tharkadan mountain range";
}

string
long_descr()
{
    return "You stand within a narrow cave network that runs through " +
        "the Tharkadan mountain range. Thin stalagmites hang around you " +
        "like icicles from the low roof of the cave, which continues " +
        "into darkness to your south and east. There is an exit out of " +
        "the cave network to your northwest.\n";
}

int
enter_canyon()
{
   write("You step out of the narrow cave and into a dark canyon...\n");
   return 0;
}