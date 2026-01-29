#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit CITY_OUT;

object door;

void
reset_kalaman_room()
{
    return;
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Cobbled street before a fenced private park");

    add_item(({"private park","park","great trees","trees","garden"}),
      "Great trees, both deciduous and evergreen, rise on the other side of the " +
      "fence. The smell of flowers and strange herbs tease your nose as a soft " +
      "breeze coming from the other side of the garden passes by you.\n");
    add_item(({"tall iron fence","iron fence","fence"}),
      "The iron fence surrounding the garden is of elaborate design. It is " +
      "tall, approximately ten feet in height, but does not seem difficult to climb. " +
      "The cobbled street you stand on leads up to its gate to the south.\n");

    add_item_city();
    add_exit(CITY + "r3","north",0);

    door = clone_object(KOBJ + "garden_gate1b");
    door->move(TO);

    add_cmd_item(({"fence","gate"}),"climb","@@climb_fence");

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand on a cobbled side-street in the eastern parts of Kalaman. " +
    tod_descr1() + season_road() + "To your south rises a tall iron fence that " +
    "surrounds a private park.\n";
}

string
climb_fence()
{
    if(TP->query_skill(SS_CLIMB) < 20)
    {
	write("You try and climb the fence, but your " +
	  "climbing ability really does suck. Guess you'll " +
	  "have to think of some other way to enter the " +
	  "garden.\n");
	say(QCTNAME(TP) + " tries and climbs the " +
	  "tall fence around the garden but fails.\n");
	return "";
    }
    write("You climb over the tall fence " +
      "and into the garden.\n");
    say(QCTNAME(TP) + " climbs over the fence.\n");
    TP->move_living("M",CITY + "g1",1,0);
    return "";
}
