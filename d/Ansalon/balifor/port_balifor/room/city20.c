#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"
#define FLIVING "/d/Ansalon/balifor/flotsam/living/"

inherit         BALIFOR_OUT;
object          kender;

void
reset_balifor_room()
{
    if (!objectp(kender)) {
	kender = clone_object(FLIVING + "kender");
	kender->move(TO);
    }
}

create_balifor_room()
{
    set_short("Northeast part of Town");
    set_long("@@long_descr");
    add_item(({"breakwater", "Breakwater"}), "@@break_water");
    add_item(({"steppes", "Steppes"}), "@@steppes");
    add_item(({"great gates","gates"}),
      "To your northeast are the Great Gates of Balifor, " +
      "now heavily guarded by the troops of the dragonarmy.\n");
    add_item(({"balifor","city","town"}),"@@long_descr");
    add_item(({"road","large road","roads"}),
      "A large road leads southwest towards the Bay of Balifor " +
      "and northeast towards the Great Gates, while another " +
      "road leads northwest towards the barracks and southeast " +
      "towards the business section of the town.\n");
    add_item("barracks","To your northwest are the cities " +
      "barracks.\n");
    add_item(({"business section","section"}),"The business " +
      "section is down the road to the southeast.\n");
    add_exit(BROOM + "city09", "southwest", 0);
    add_exit(BROOM + "city19", "southeast", 0);
    add_exit(BROOM + "gate", "northeast", 0);
    add_exit(BROOM + "city21", "northwest", 0);
    reset_balifor_room();
}

string
long_descr()
{
    return tod_descr1() + " You stand on the northeast corner of the Port " +
    "City of Balifor. Directly to your northeast are the Great Gates " +
    "of Balifor, now heavily guarded by the troops of the dragonarmy. " +
    "Southwest the large road leads back towards the Bay, and another " +
    "road intersects it here, leading northwest towards the barracks, " +
    "and southeast towards the business section of town. " +
    season_descr() + "\n";
}
