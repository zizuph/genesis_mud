#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KALAMAN_IN;
object g1;

void
reset_kalaman_room()
{
    if(!objectp(g1))
    {
	g1 = clone_object(KNPC + "sentry");
	g1->arm_me();
	g1->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("On the top floor of the lookout tower");

    add_item(({"top floor","floor","tower","lookout tower","observation room",
	"room"}),
      "@@long_descr");
    add_item("walls","You cannot really see the walls from where you are.\n");
    add_item(({"windows","window"}),
      "There are two large windows in this room, one to the north " +
      "that looks upon the estuary of the Vingaard River, and one " +
      "to the southeast, allowing one to view the harbour.\n");
    add_item(({"north","northern window","estuary","river","Vingaard River"}),
      "Looking out the northern window you see the estuary of the Vingaard " +
      "River open out into the Turbidus Ocean. All seems to be quite " +
      "calm out there.\n");
    add_item(({"southeast","southeastern window","harbour"}),
      "Looking out the southeastern window, you see a busy " +
      "harbour, with boats of various kind coming into and out " +
      "of it carrying both cargo and passengers.\n");

    add_exit(WALL + "t1","down",0);
    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand high up in the lofty observation room of one of " +
    "the lookout towers placed along the walls of Kalaman. A window to your " +
    "southeast allows you to view the entire harbour, while one to your " +
    "north allows you to view the estuary of the Vingaard River.\n";
}
