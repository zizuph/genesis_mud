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
    add_item(({"corner","city","balifor"}),"@@long_descr");
    add_item("large road","To your northeast a large road " +
      "heads towards the business part of town.\n");
    add_item(({"smaller roads","roads","small roads"}),
      "Smaller roads travel west and northwest from here towards " +
      "the Bay.\n");
    add_item(({"buildings","large buildings"}),
      "Two large buildings are built into the side of the Steppe. " +
      "There is nothing unusual about either of them.\n");
    add_exit(BROOM + "city14", "west", 0);
    add_exit(BROOM + "city17", "northeast", 0);
    add_exit(BROOM + "city13", "northwest", 0);
    reset_balifor_room();
}

string
long_descr()
{
    return tod_descr1() + " You stand in the southeast corner of the " +
    "Port City of Balifor. Northeast a large road heads towards the " +
    "business part of town, you see two large buildings built into " +
    "the Steppes.  Smaller roads travel west and northwest from here, " +
    "leading back towards the Bay. " + season_descr() + "\n";
}
