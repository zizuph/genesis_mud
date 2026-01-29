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
    set_short("Street in Central City");
    set_long("@@long_descr");
    add_item(({"breakwater", "Breakwater"}), "@@break_water");
    add_item(({"steppes", "Steppes"}), "@@steppes");
    add_item(({"central balifor","balifor","town"}),"@@long_descr");
    add_item(({"large white stone building","stone building",
	"white stone building","building","town hall"}),
      "To your southwest is a large white stone building " +
      "which you assume to be the Town Hall.\n");
    add_item("roads","Roads lead northeast towards the " +
      "business district, northwest, and south.\n");
    add_exit(BROOM + "city11", "south", 0);
    add_exit(BROOM + "city19", "northeast", 0);
    add_exit(BROOM + "city09", "northwest", 0);
    add_exit(BROOM + "board", "southwest", 0);
    reset_balifor_room();
}

string
long_descr()
{
    return tod_descr1() + " You are in Central Balifor. Southwest leads " +
    "into a large white stone building, which you assume is the Town " +
    "Hall. Roads lead northeast towards the business district, north" +
    "west, and south. " + season_descr() + "\n";
}
