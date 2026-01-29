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
	g1 = clone_object(KNPC + "militiaman");
	g1->arm_me();
	g1->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("city barracks");

    add_item(({"sleeping quarters","quarters"}),
      "The room attached to this one contains the sleeping " +
      "quarters of the local militia.\n");
    add_item(({"large circular table","circular table","table"}),
      "This circular table is used by the local militia " +
      "for meals as well as gaming purposes.\n");
    add_item("chairs","A number of chairs surround the circular table.\n");


    add_exit(CITY + "r8","west",0);
    add_exit(CITY + "b2","east",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand in one of the barracks of Kalaman, housing " +
    "the local militia. In this room sits a large circular " +
    "table surrounded by chairs, used for eating " +
    "meals, as well as for dicing and playing cards. To the " +
    "east " +
    "is the entrance to the barracks sleeping quarters.\n";
}
