#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;
object c1,m1;

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
    set_short("A cobbled street in Kalaman");

    add_item(({"markets","market"}),
      "To your northwest the road leads to the markets of Kalaman.\n");

    add_item_city();

    add_exit(CITY + "r24","north",0);
    add_exit(CITY + "r2","southeast",0);
    add_exit(CITY + "m2","northwest",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand on a cobbled street in Kalaman. " +
    tod_descr1() + season_road() + "The road branches " +
    "off to the north, while continuing to the northwest " +
    "towards the markets.\n";
}
