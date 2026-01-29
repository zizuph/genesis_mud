#include "/d/Krynn/common/defs.h"
#include "../../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
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

    add_exit(CAVERNS + "cavern7","north",0);

    add_prop(ROOM_S_DARK_LONG, "A dark, cold cavern. Without a light " +
      "source it is too dark to see in here.\n"); 
    add_prop(ROOM_S_DARK_MSG, "The cavern is too dark to"); 
    add_prop(ROOM_I_LIGHT, DARKNESS_PASSIVE);

    add_item(({"cold cavern","cavern","throat"}),
      "You stand on a rough ridge overlooking a great cavern that " +
      "disappears down into darkness below. Once the throat of an " +
      "ancient volcano, it could potentially lead to the centre of " +
      "the earth! Or at least a very long way down...\n");
    add_item(({"ridge","rough ridge","ridge of basalt"}),
      "A rough ridge runs along the side of the cavern above you. " +
      "You may be able to climb up to it from here.\n");
    add_item(({"narrow ledge","ledge"}),
      "You stand on a narrow ledge that runs along the wall of the " +
      "cavern. Below you can just make out the floor of the cavern, " +
      "reflecting strangely back at you.\n");
    add_item(({"wall"}), "You stand against the wall of the cavern on " +
      "a narrow ledge. You could probably climb up from here to the " +
      "ridge above you.\n");
    add_item(({"floor","floor of the cavern","sheet of ice","ice",
	"below"}), "Looking down from the ledge you can make out the " +
      "cavern floor. It reflects coldly back at you, like a giant " +
      "sheet of ice.\n");
    add_item(({"volcano","ancient volcano"}), "You stand within the " +
      "throat of what was once an ancient volcano, long dormant. Over " +
      "time its great vent above you filled with ice and fell in " +
      "on itself, creating the great cavern you now overlook.\n");

    add_cmd_item(({"into cavern","cavern"}), "jump", "Self preservation " +
      "insists that jumping down into the cavern would be suicide. " +
      "You don't do it.\n");
    add_cmd_item(({"up","up cavern","to ridge","ridge","up to ridge",
	"wall"}), "climb", "@@climb_walls");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
	ONE_OF(herbs), ONE_OF(herbs) }), ({ "cavern","ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "on a narrow ledge within a dark, cold cavern";
}

string
long_descr()
{
    return "You stand on a narrow ledge running along the walls of a " +
    "cavern that was once part of the throat of an ancient volcano, " +
    "now long dormant. The ledge runs along the wall here to your " +
    "north. Far below you can just make out the floor of the " +
    "cavern, reflecting strangely back at you. Above you can make " +
    "out a a rough ridge that you may be able to climb up to.\n";
}

string
climb_walls()
{
    if(TP->query_skill(SS_CLIMB) < 36)
    {
	write("You don't have the ability to climb back up! You are " +
	  "stuck!\n");

	return "";
    }

    write("You skillfully climb up the side of the cavern to the " +
      "ridge above.\n");
    say(QCTNAME(TP) + " skillfully climbs up the side of the " +
      "cavern to the ridge above.\n");
    tell_room(CAVERNS + "cavern5", QCTNAME(TP) + " climbs up " +
      "out of the darkness of the cavern below.\n");
    TP->move_living("M", CAVERNS + "cavern5",1,0);
    return "";
}

