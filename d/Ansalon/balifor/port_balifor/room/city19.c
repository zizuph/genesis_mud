#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit         BALIFOR_OUT;
object          merc;
object          merc2;
object          drac;

void
reset_balifor_room()
{
    if (!objectp(merc)) {
	merc = clone_object(KNPC + "mercenary");
	merc->move(TO);
    }
    if (!objectp(merc2)) {
	merc2 = clone_object(KNPC + "mercenary");
	merc2->move(TO);
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
    add_item("sign", "@@read");
    add_item(({"city","balifor"}),"@@long_descr");
    add_item(({"gates","great gates"}),
      "Directly to your northeast are the Great Gates of Balifor, now heavily guarded by the troops of the dragonarmy.\n");
    add_item(({"large road","road"}),
      "A large road leads southwest towards the bay, and an " +
      "intersecting road leads northwest towards towards the " +
      "barracks.\n");
    add_item("barracks","Following the road to your northwest " +
      "will take you to the barracks.\n");
    add_item("shop","A small shop stands to the east.\n");
    add_cmd_item("sign", "read", "@@read");
    add_exit(BROOM + "city10", "southwest", 0);
    add_exit(BROOM + "city18", "south", 0);
    add_exit(BROOM + "shop", "east", 0);
    add_exit(BROOM + "city20", "northwest", 0);
    reset_balifor_room();
}

string
long_descr()
{
    return tod_descr1() + " You stand in the eastern parts " +
    "of the Port " +
    "City of Balifor. Looking north you see the Great Gates " +
    "of Balifor, now heavily guarded by the troops of the dragonarmy. " +
    "Southwest the large road leads back towards the Bay, and another " +
    "road intersects it here, leading northwest towards the barracks, " +
    "and southeast towards the business section of town. You see a " +
    "shop to the east, with a sign on the door. " + season_descr() + "\n";
}

string
read()
{
    return "Eorl the Merchant of Balifor.\n";
}
