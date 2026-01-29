#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"

inherit         BALIFOR_OUT;

create_balifor_room()
{
    set_short("Street on the Bay");
    set_long("@@long_descr");
    add_item(({"Breakwater", "breakwater"}), "@@break_water");
    add_item(({"steppes", "Steppes"}), "@@steppes");
    add_item(({"main road","road"}),
      "The main road ends here. It leads off to the southeast.\n");
    add_item(({"coast","bay"}),
      "To the west is the Bay of Balifor.\n");
    add_item(({"building","barracks"}),
      "To the east is one side of the large barracks of the city " +
      "of Balifor. Its entrance is not on this side.\n");
    add_exit(BROOM + "city06", "southeast", 0);
    add_exit(BROOM + "wharf01", "southwest", "@@pier", 0);
    set_tell_time(30);
    add_tell("@@wharf");
    start_room_tells();
}

int
pier()
{
    write("You walk out onto the wharf.\n");
    return 0;
}

string
long_descr()
{
    return tod_descr1() + " You are on the North side of Port Balifor, " +
    "where the main road along the coast ends. The breakwater extends " +
    "southwest from here, out into the bay. The building to the east " +
    "has been taken over by the dragonarmies, who use it as a barracks" +
    " for their troops. " + season_descr() + "\n";
}
