#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit         BALIFOR_OUT;

create_balifor_room()
{
    set_short("On the North Breakwater Road");
    set_long("@@long_descr");
    add_item(({"Breakwater", "breakwater"}), "@@break_water");
    add_item(({"steppes", "Steppes"}), "@@steppes");
    add_item("wall","@@break_water");
    add_item("road","The road runs parallel to the breakwater " +
      "wall.\n");
    add_item(({"bay","Bay of Balifor","bay of balifor","west",
	"vast sea","sea"}),
      "The Bay of Balifor stretches out for miles and miles to " +
      "the west.\n");
    add_item(({"port city","balifor","Balifor","east"}),
      "To your east is the port city of Balifor.\n");
    set_tell_time(80);
    add_tell("@@wharf");
    start_room_tells();
    add_exit(BROOM + "city07", "northeast", "@@pier", 0);
    add_exit(BROOM + "wharf02", "southwest", "@@pier2", 0);
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
    return tod_descr1() + " You are on the North Breakwater road. " +
    "The road runs parallel to the wall, out into the Bay of " +
    "Balifor. Looking out to your west, you see the vast sea " +
    "which stretches for miles and miles beyond your sight. To " +
    "your east lies the Port City of Balifor, and beyond that " +
    "lie the steppes, that overlook the City. " + season_descr() + "\n";
}
