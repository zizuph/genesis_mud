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
    add_item(({"windows","window","plains","plains of estwilde",
	"plain"}),
      "Looking to your south you see the plains of Estwilde, a harsh, hilly-looking " +
      "land, stretch out as far as your eye can see. It is believed it is from this " +
      "direction that the dragonarmies will come. " +
      "To your east the plains stretch out until they reach a forest in the " +
      "distance that borders along some mountains.\n");
    add_item(({"mountains","forest","east","eastern window"}),
      "Looking out the eastern window you see the plains of Estwilde stretch " +
      "out until they reach a forest in the distance that borders along some " +
      "mountains. Rumour has it that that forest is plagued with goblins.\n");

    add_exit(WALL + "t2","down",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand high up in the lofty observation room of one of " +
    "the lookout towers placed along the walls of Kalaman. A window to your " +
    "south and east allow you to view the plains of Estwilde. " +
    "A stone stairway leads down to the bottom of the tower.\n";
}
