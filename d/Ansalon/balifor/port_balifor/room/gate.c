#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit         BALIFOR_OUT;
object          drac;
object          drac2;
object          drac3;

void
reset_balifor_room()
{
    if (!objectp(drac)) {
	drac = clone_object(KNPC + "bozak");
	drac->move(TO);
    }
    if (!objectp(drac2)) {
	drac2 = clone_object(KNPC + "bozak");
	drac2->move(TO);
    }
    if (!objectp(drac3)) {
	drac3 = clone_object(KNPC + "bozak");
	drac3->move(TO);
    }
}

create_balifor_room()
{
    set_short("The Gates of Port Balifor");
    set_long("@@long_descr");
    add_item(({"breakwater", "Breakwater"}), "@@break_water");
    add_item(({"steppes", "Steppes"}), "@@steppes");
    add_item(({"gates","gates of balifor","entrance"}),
      "To the northeast are the open Gates of Balifor, the " +
      "only entrance into and out of Port Balifor by land.\n");
    add_item(({"city","port city","town","balifor"}),
      "@@long_descr");
    add_item("guard rooms","To your northwest and southeast " +
      "stand two guard rooms that keep watch over the gates.\n");
    add_item("road","The road leads northeast out the gates " +
      "of Balifor and southwest into the heart of Port Balifor.\n");
    add_item(({"plains","plains of balifor"}),
      "Out the gate to your northeast you can make out the " +
      "plains of Balifor.\n");
    add_exit("/d/Ansalon/balifor/steppe/room/road11",
      "northeast","@@leave_balifor");
    add_exit(BROOM + "city20", "southwest", 0);
    add_exit(BROOM + "guard2", "southeast", 0);
    add_exit(BROOM + "guard1", "northwest", 0);
    reset_balifor_room();
}

string
long_descr()
{
    return tod_descr1() + "You stand at the Gates of Balifor. The " +
    "only entrance to the Port City by land. The town is sheltered " +
    "by the steppes to the east and south, and surrounded by water on " +
    "the west. To your southeast and northwest lie the two guard " +
    "rooms that keep watch on the gate at all times. A large road " +
    "travels southwest from here into the city, and northeast out " +
    "of the Port City, and into the plains of Balifor. " +
    season_descr() + "\n";
}

int
leave_balifor()
{
    write("You pass through the gates of Balifor.\n");
    return 0;
}
