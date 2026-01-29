#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit         BALIFOR_OUT;
object          drac2;
object          drac3;
object          drac4;
object          drac5;

void
reset_balifor_room()
{
    if (!objectp(drac2)) {
	drac2 = clone_object(KNPC + "sivak");
	drac2->move(TO);
    }
    if (!objectp(drac3)) {
	drac3 = clone_object(KNPC + "bozak");
	drac3->move(TO);
    }
    if (!objectp(drac4)) {
	drac4 = clone_object(KNPC + "kapak");
	drac4->move(TO);
    }
    if (!objectp(drac5)) {
	drac5 = clone_object(KNPC + "kapak");
	drac5->move(TO);
    }
}

create_balifor_room()
{
    set_short("Street in Central City");
    set_long("@@long_descr");
    add_item(({"breakwater", "Breakwater"}), "@@break_water");
    add_item(({"steppes", "Steppes"}), "@@steppes");
    add_item(({"roads","road"}),"Roads lead southeast " +
      "towards the business district, south west and north.\n");
    add_item(({"large white stone building","stone building",
	"white building","building","town hall"}),
      "To your northwest stands a large white stone building " +
      "that you assume to be the Town Hall.\n");
    add_exit(BROOM + "city11", "north", 0);
    add_exit(BROOM + "city17", "southeast", 0);
    add_exit(BROOM + "board", "northwest", 0);
    add_exit(BROOM + "city13", "southwest", 0);
    reset_balifor_room();
}

string
long_descr()
{
    return tod_descr1() + " You are in Central Balifor. Northwest leads " +
    "into a large white stone building, which you assume is the Town " +
    "Hall. Roads lead southeast towards the business district, south" +
    "west, and north. " + season_descr() + "\n";
}
