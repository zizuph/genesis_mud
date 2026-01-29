#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit         BALIFOR_OUT;

void
reset_balifor_room()
{
    return;
}

create_balifor_room()
{
    set_short("Pier in the Bay");
    set_long("@@long_descr");
    add_item("sign", "@@read");
    add_item(({"Breakwater", "breakwater"}), "@@break_water");
    add_item(({"steppes", "Steppes"}), "@@steppes");
    add_item(({"Bay of Balifor","bay of balifor","bay"}),
      "To your west is the Bay of Balifor.\n");
    add_item("pier","You are at present standing on a pier " +
      "on the edge of the Bay of Balifor.\n");
    add_item(({"dark ships","ships"}),
      "Dark ships of the dragonarmies often sail into and " +
      "out of this port city.\n");
    add_cmd_item("sign", "read", "@@read");
    add_exit(BROOM + "pier01","south", "@@pier", 0);
    set_tell_time(80);
    add_tell("@@wharf");
    start_room_tells();
    reset_balifor_room();
}

int
pier()
{
    write("You head further down the pier...\n");
    return 0;
}

string
long_descr()
{
    return tod_descr1() + " You are looking over the Bay of Balifor, " +
    "standing out on a pier. The dragonarmies have taken over the " +
    "port city, and confiscated all boats for their use. The dark " +
    "ships sail in and out of Balifor frequently. " + season_descr() +
    "\nThere is a sign standing here." +
    "\n";
}

string
read()
{
    return "The sign reads: The ship to the Dragonarmy base at Kurinost "+
           "lands here. "+
    "Please have your equipment ready for a swift departure.\n";
}
