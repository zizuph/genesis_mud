#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;
object g1;

void
reset_kalaman_room()
{
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
    set_short("Cobbled street in the southern part of Kalaman");

    add_item(({"wealthy looking home","home","building"}),
      "To the east stands a rather wealthy looking home.\n");
    add_item(({"city wall","wall","walls"}),
      "To the west rise the great walls that surround Kalaman.\n");

    add_exit(CITY + "r31","northwest",0);
    add_exit(CITY + "r33","southeast",0);

    add_item_city();

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand on a cobbled street in the southern district of Kalaman. " +
    tod_descr1() + season_road() + "To the east rises a rather wealthy " +
    "looking home, while to the west stands the city wall.\n";
}
