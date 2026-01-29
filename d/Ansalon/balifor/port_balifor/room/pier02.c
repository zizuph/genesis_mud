#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit         BALIFOR_OUT;
object          drac1;
object          drac2;

void
reset_balifor_room()
{
    if (!objectp(drac1)) {
	drac1 = clone_object(KNPC + "baaz");
	drac1->move(TO);
    }
    if (!objectp(drac2)) {
	drac2 = clone_object(KNPC + "baaz");
	drac2->move(TO);
    }
}

create_balifor_room()
{
    set_short("Pier in the Bay");
    set_long("@@long_descr");
    add_item("sign", "@@read");
    add_item(({"Breakwater", "breakwater"}), "@@break_water");
    add_item(({"steppes", "Steppes"}), "@@steppes");
    add_item(({"bay","bay of balifor"}),
      "To the west is the Bay of Balifor.\n");
    add_item("pier","Beneath your feet is a pier in the " +
      "port city of Balifor.\n");
    add_item(({"port city","city","Balifor","balifor"}),
      "To the east is the Port City of Balifor.\n");
    add_item(({"dark ships","ships"}),
      "Out in the bay you notice the dark ships of the " +
      "dragonarmy patrolling the area.\n");
    add_cmd_item("sign", "read", "@@read");
    add_exit(BROOM + "city06", "northeast", "@@pier", 0);

    set_tell_time(80);
    add_tell("@@wharf");
    start_room_tells();
    reset_balifor_room();
}

int
pier()
{
    write("You walk off the wharf, back to the street.\n");
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
    return "The sign reads: The dragonarmy courier ship to Sanction now " +
    "lands here.\n";
}
