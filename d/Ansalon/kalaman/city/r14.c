#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;
object m1, g1;

void
reset_kalaman_room()
{
    if(!objectp(m1))
    {
	m1 = clone_object(KNPC + "maiden");
	m1->arm_me();
	m1->move(TO);
    }

    if(!objectp(g1))
    {
	g1 = clone_object(KNPC + "militiaman");
	g1->arm_me();
	g1->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("At an intersection near the city walls");
    add_item(({"city walls","walls","great walls","wall"}),
      "Surrounding the city are high walls made of solid grey stone.\n");

    add_item_city();
    add_exit(CITY + "r13","north",0);
    add_exit(CITY + "r15","east",0);
    add_exit(CITY + "r34","west",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand at an intersection in the southern parts of Kalaman. " +
    season_road() + tod_descr1()+ "The street continues to your east and west, " +
    "while branching off towards the middle of the city to your north. " +
    "The high walls surrounding Kalaman rise to your south.\n";
}
