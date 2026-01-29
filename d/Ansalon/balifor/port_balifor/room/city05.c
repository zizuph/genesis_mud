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
      "Here is where the main road ends. It heads off in a " +
      "northeasterly direction.\n");
    add_item(({"coast","bay","bay of balifor","Bay of Balifor"}),
      "To your west is the Bay of Balifor. A cool breeze comes " +
      "off the bay and sweeps down the streets of the city.\n");
    add_item(({"exit","southeast","passage"}),
      "To your southeast there was an exit, but that has " +
      "been boarded up for some reason.\n");
    add_exit(BROOM + "city04.c", "northeast", 0, 1);
    add_exit(BROOM + "wharf03", "northwest", "@@pier", 0);
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
    return tod_descr1() + " You are on the South side of Port Balifor, " +
    "where the main road along the coast ends. The breakwater extends " +
    "northwest from here, out into the bay. There was once an exit " +
    "southeast here, but it is now boarded up, blocking passage that " +
    "way. " + season_descr() + "\n";
}

