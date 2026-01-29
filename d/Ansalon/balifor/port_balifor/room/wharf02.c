#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit         BALIFOR_OUT;

create_balifor_room()
{
    set_short("On the tip of the North Breakwater");
    set_long("@@long_descr");
    add_item(({"Breakwater", "breakwater"}), "@@break_water");
    add_item(({"steppes", "Steppes"}), "@@steppes");
    add_item(({"Bay of Balifor","bay of balifor","bay"}),
      "Looking to the west you see nothing but the waters of " +
      "the Bay of Balifor.\n");
    add_item(({"great ships","ships"}),
      "Great ships sail in and out of the harbor before you.\n");
    add_item(({"harbor","port city","balifor","Balifor"}),
      "To your southeast is the port city of Balifor.\n");
    add_item("south","To your south you notice the Southern " +
      "Breakwater.\n");
    set_tell_time(80);
    add_tell("@@wharf");
    start_room_tells();
    add_exit(BROOM + "wharf01", "northeast", "@@pier", 0);
}

int
pier()
{
    write("You walk along the Breakwater, heading towards the city.\n");
    return 0;
}

string
long_descr()
{
    return tod_descr1() + " You stand at the tip of the Northern " +
    "Breakwater, overlooking the beautiful Bay of Balifor. " +
    "Great ships " +
    "sail in and out of the Harbor, passing before you. Far to the " +
    "east you see the Port City, and to your south you see the tip of " +
    "the Southern Breakwater, about a hundred meters away from you. " +
    season_descr() + "\n";
}
