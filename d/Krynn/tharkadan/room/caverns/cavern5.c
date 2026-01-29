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

    add_exit(CAVERNS + "cavern4","south",0);

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
      "A rough ridge along the side of the cavern ends here. Below " +
      "you can make out a ledge far below.\n");
    add_item(({"ledge","narrow ledge","wall"}),
      "Far below you running along the wall of the cavern you can " +
      "make out a narrow ledge. A skilled climber may be able to " +
      "climb down to it.\n");
    add_item(({"basalt"}),
      "The rough ridge beneath your feet is of a fine-grained " +
      "volcanic rock known as basalt.\n");
    add_item(({"volcano","ancient volcano"}),
      "You stand within the throat of what was once an ancient " +
      "volcano, long dormant. Over time its great vent above " +
      "you filled with ice and fell in on itself, creating the great " +
      "cavern you now overlook.\n");

    add_cmd_item(({"into cavern","cavern"}), "jump", "Self preservation " +
      "insists that jumping into the cavern would be suicide. You " +
      "don't do it.\n");
    add_cmd_item(({"down","down cavern","down ridge","into cavern",
	"down to ledge"}), "climb", "@@climb_walls");

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
    "ridge rises up to your south along the edge of the cavern, " +
    "while beneath you some distance down you can make out a " +
    "ledge you may be able to climb down to.\n";
}

string
climb_walls()
{
    if(TP->query_skill(SS_CLIMB) < 36)
    {
	write("You realise you don't have the ability to climb back up " +
	  "after climbing down. So you decide against trying to make " +
	  "your way down to the ledge.\n");

	return "";
    }

    write("You skillfully climb down the side of the cavern to the " +
      "ledge below.\n");
    say(QCTNAME(TP) + " lowers " +HIM(TP)+ "self over the rough ridge " +
      "and begins climbing carefully down to the ledge below.\n");
    tell_room(CAVERNS + "cavern6", QCTNAME(TP) + " lowers " +HIM(TP)+ 
      "self from the ridge above down to the ledge where you now " +
      "stand.\n");
    TP->move_living("M", CAVERNS + "cavern6",1,0);

    return "";
}

