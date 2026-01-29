#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit         BALIFOR_OUT;
object          drac;

void
reset_balifor_room()
{
    if (!objectp(drac)) {
	drac = clone_object(KNPC + "baaz");
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
    add_item("street","You are walking on a street in the town " +
      "of Port Balifor.\n");
    add_item(({"Bay","west","bay"}),
      "To your west is the Bay of Balifor.\n");
    add_item(({"Town Hall","town hall","north"}),
      "To your north is the Town Hall.\n");
    add_item(({"south","building","smaller building",
	"post office"}),
      "To your south stands the small Post Office.\n");
    add_cmd_item("sign", "read", "@@read");
    add_exit(BROOM + "city14", "southwest", 0);
    add_exit(BROOM + "city12", "northeast", 0);
    add_exit(BROOM + "city16", "southeast", 0);
    add_exit(BROOM + "city03", "northwest", 0);
    add_exit(BROOM + "po", "south", 0);
    reset_balifor_room();
}

string
read()
{
    return "Post office of the Port City of Balifor.\n";
}

string
long_descr()
{
    return tod_descr1() + " You walk along a street in central city. " +
    "To your west is the Bay, and east will take you deeper into " +
    "the city. North of you, you see Town Hall. A smaller building " +
    "rests to the south of the road, and a sign hangs above the " +
    "doorway. " + season_descr() + "\n";
}
