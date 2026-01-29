#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;
object c1, m1;

void
reset_kalaman_room()
{
    if(!objectp(m1))
    {
	m1 = clone_object(KNPC + "maiden");
	m1->arm_me();
	m1->move(TO);
    }

    if(!objectp(c1))
    {
	c1 = clone_object(KNPC + "civilian");
	c1->arm_me();
	c1->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Cobbled street in the southern part of Kalaman");

    add_item(({"residential buildings","buildings","building"}),
      "On both the eastern and western side of the road stand tall two-story " +
      "buildings, homes for the richer members of Kalaman's society.\n");

    add_exit(CITY + "r28","north",0);
    add_exit(CITY + "r31","south",0);
    add_item_city();

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand on a cobbled street in the southern district of Kalaman. " +
    tod_descr1() + season_road() + "Residential buildings rise up on either side " +
    "of the road.\n";
}
