#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit         BALIFOR_OUT;

create_balifor_room()
{
    set_short("On the South Breakwater Road");
    set_long("@@long_descr");
    add_item(({"Breakwater", "breakwater"}), "@@break_water");
    add_item(({"steppes", "Steppes"}), "@@steppes");
    add_item("wall","@@break_water");
    add_item(({"Bay of Balifor","bay of balifor","bay",
	"sea","west"}),
      "Looking out over the breakwater is a vast sea which " +
      "stretches out for miles and miles beyond your sight.\n");
    add_item(({"east","city","Balifor","balifor","port city"}),
      "To your east is the Port City of Balifor.\n");
    add_item("road","@@long_descr");
    set_tell_time(80);
    add_tell("@@wharf");
    start_room_tells();
    add_exit(BROOM + "city05", "southeast", "@@pier", 0);
    add_exit(BROOM + "wharf04", "northwest", "@@pier2", 0);
}

int
pier()
{
    write("You walk off the Breakwater, back to the street.\n");
    return 0;
}

int
pier2()
{
    write("You walk further out on the Breakwater.\n");
    return 0;
}

string
long_descr()
{
    return tod_descr1() + " You are on the South Breakwater road. " +
    "The road runs parallel to the wall, out into the Bay of " +
    "Balifor. Looking out to your west, you see the vast sea " +
    "which stretches for miles and miles beyond your sight. To " +
    "your east lies the Port City of Balifor, and beyond that " +
    "lie the steppes, that overlook the City. " + season_descr() + "\n";
}
