#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit         BALIFOR_OUT;
inherit "/d/Genesis/gsl_ships/lib/pier";

object          drac1;
object          drac2;

void
reset_balifor_room()
{
    if (!objectp(drac1)) {
	drac1 = clone_object(KNPC+ "baaz");
	drac1->move(TO);
    }
    if (!objectp(drac2)) {
	drac2 = clone_object(KNPC+ "baaz");
	drac2->move(TO);
    }
}

create_balifor_room()
{
  set_short("Pier in the Bay");
    set_long("@@long_descr");
    //add_item("sign", "@@read");
    add_item(({"Breakwater", "breakwater"}), "@@break_water");
    add_item(({"steppes", "Steppes"}), "@@steppes");
    add_item(({"bay","bay of balifor","Bay of Balifor"}),
      "Looking out to the west is the Bay of Balifor. A cool " +
      "breeze comes off the bay and sweeps up the streets of the " +
      "city.\n");

    add_item("pier","@@long_descr");
    add_item(({"city","port city","Balifor","balifor"}),
      "The pier leads to the southeast towards the port city " +
      "of Balifor.\n");
    add_item(({"dark ships","boats"}),
      "The dark ships of the dragonarmies seem to frequently " +
      "sail into this port city.\n");
    //add_cmd_item("sign", "read", "@@read");
    add_exit(BROOM + "city04", "southeast", "@@pier", 0);

    set_tell_time(80);
    add_tell("@@wharf");
    start_room_tells();
    reset_balifor_room();
    add_pier_entry(MASTER_OB(TO), "Balifor", "Telberin - Poros Circle");
    initialize_pier();
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
    "\nA sign stands here." +
    "\n";
}
/*
string
read()
{
  //return "Decorated with a fiery red-scaled dragon, this " +
    "sign reads: The line too Gont Port is currently inactive.\n";
}
*/
