#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit         BALIFOR_OUT;
object          merc;
object          drac;
object          drac2;

void
reset_balifor_room()
{
    if (!objectp(merc)) {
	merc = clone_object(KNPC + "mercenary");
	merc->move(TO);
    }
    if (!objectp(drac2)) {
	drac2 = clone_object(KNPC + "bozak");
	drac2->move(TO);
    }
    if (!objectp(drac)) {
	drac = clone_object(KNPC + "bozak");
	drac->move(TO);
    }
}

create_balifor_room()
{
    set_short("Business Section of the City");
    set_long("@@long_descr");
    add_item(({"breakwater", "Breakwater"}), "@@break_water");
    add_item(({"steppes", "Steppes"}), "@@steppes");
    add_item(({"roads","road"}),"A road heads north " +
      "along the side of the Steppes, while another two head " +
      "northwest towards the center of town, and southwest " +
      "towards the Bay of Balifor.\n");
    add_item("buildings","The buildings of Port Balifor " +
      "are built into the sides of the Steppes, offering " +
      "them good protection from the weather and hoodlums.\n");
    add_item(({"landscape","rocky landscape"}),"@@steppes");
    add_item(({"well guarded building","bank"}),
      "To your east stands a well guarded building, the " +
      "Bank of Balifor.\n");
    add_item("sign", "@@read");
    add_cmd_item("sign", "read", "@@read");
    add_exit(BROOM + "city16", "southwest", 0);
    add_exit(BROOM + "city18", "north", 0);
    add_exit(BROOM + "bank", "east", 0);
    add_exit(BROOM + "city12", "northwest", 0);
    reset_balifor_room();
}

string
long_descr()
{
    return tod_descr1() + " You are in the Business Section of Balifor, " +
    "on the road that runs north and south along the Steppes. The " +
    "buildings are built into the rocky landscape here, providing good " +
    "protection from weather and hoodlums. A large, well guarded " +
    "building lies to the east, with a large sign on the front of it " +
    "reading: BANK OF BALIFOR. Roads also lead northwest and southwest " +
    "away from the Steppes, and into the City itself. " + season_descr() +
    "\n";
}

string
read()
{
    return "Bank of Balifor.\n";
}
