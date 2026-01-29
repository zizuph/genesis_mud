#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit         BALIFOR_OUT;
object          drac;

void
reset_balifor_room()
{
    if (!objectp(drac)) {
	drac = clone_object(KNPC + "kapak");
	drac->move(TO);
    }
}

create_balifor_room()
{
    set_short("Street in Central City");
    set_long("@@long_descr");
    add_item(({"breakwater", "Breakwater"}), "@@break_water");
    add_item(({"steppes", "Steppes"}), "@@steppes");
    add_item("sign", "@@read");
    add_item(({"balifor","center","city","port city","town"}),
      "@@long_descr");
    add_item(({"roads","road"}),"Two roads intersect here, " +
      "the larger running southwest towards the Bay and " +
      "northeast towards the Gates of Balifor, while the other " +
      "runs northwest towards a dark building, and southeast " +
      "towards the center of Balifor.\n");
    add_item(({"gates","great gates"}),"To your northeast " +
      "are the guarded Gates of Balifor.\n");
    add_item("dark building","To your northwest stands a " +
      "dark building. Perhaps you should head that way to examine " +
      "it in better detail?\n");
    add_item("building","There are two buildings, the " +
      "dark building to your northwest, and the adventurers " +
      "guild to your north.\n");
    add_item("adventurers guild","To your north stands " +
      "Port Balifors adventurers guild. Here is where travellers " +
      "learn and pass on skills to one and other.\n");
    add_cmd_item("sign", "read", "@@read");
    add_exit(BROOM + "city02", "southwest", 0);
    add_exit(BROOM + "city08", "northwest", 0);
    add_exit(BROOM + "city10", "southeast", 0);
    add_exit(BROOM + "city20", "northeast", 0);
    add_exit(BROOM + "adv_guild", "north", 0);
    reset_balifor_room();
}

string
read()
{
    return "Adventurer's Guild of Balifor.\n";
}

string
long_descr()
{
    return tod_descr1() + " You are near the center of the Port City of " +
    "Balifor. Two roads intersect here. The larger runs southwest " +
    "towards the Bay, and northeast to the Gates of Balifor. The " +
    "smaller runs northwest towards a dark building, and southeast " +
    "into the center of Balifor. Another building lies directly north " +
    "of you, a sign hanging over the door. " + season_descr() + "\n";
}
