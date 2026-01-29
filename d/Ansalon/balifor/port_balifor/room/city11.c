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
    set_short("Balifor Central");
    set_long("@@long_descr");
    add_item(({"breakwater", "Breakwater"}), "@@break_water");
    add_item(({"steppes", "Steppes"}), "@@steppes");
    add_item(({"large white building","large building",
	"white building","building","town hall"}),
      "To your west stands a large white building which " +
      "acts as the Town Hall of Balifor.\n");
    add_item(({"stone","arch","entrance","door"}),
      "A stone arch acts as the entrance to the Town Hall. " +
      "There are words carved along it that can be read.\n");
    add_item(({"words", "word", "carving"}), "@@read");
    add_cmd_item(({"words", "word", "carving"}), "read", "@@read");
    add_exit(BROOM + "city10", "north", 0);
    add_exit(BROOM + "city18", "east", 0);
    add_exit(BROOM + "board", "west", 0);
    add_exit(BROOM + "city12", "south", 0);
    reset_balifor_room();
}

string
read()
{
    return "Balifor City Hall.\n";
}

string
long_descr()
{
    return tod_descr1() + " You are standing in front of a large white " +
    "building running through central Balifor. An arch is cut into " +
    "the stone here, which serves as an entrance to the building. " +
    "Words are carved over the arch, curving with the stone above the " +
    "door. " + season_descr() + "\n";
}
