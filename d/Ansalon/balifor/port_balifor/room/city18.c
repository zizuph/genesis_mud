#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"
#include <ss_types.h>

#define MINIMUM_SPELLCRAFT 39

inherit         BALIFOR_OUT;
object          drac;

void
reset_balifor_room()
{
    if (!objectp(drac)) {
	drac = clone_object(KNPC + "sivak");
	drac->move(TO);
    }
}

create_balifor_room()
{
    set_short("Business Section of the City");
    set_long("@@long_descr");
    add_item(({"breakwater", "Breakwater"}), "@@break_water");
    add_item(({"steppes", "Steppes"}), "@@steppes");
    add_item(({"balifor","business district","city"}),"@@long_descr");
    add_item(({"large roads","two large roads","roads","road"}),
      "A road heads north towards the Gates, south towards the Bay, " +
      "and west towards the center of Balifor.\n");
    add_item(({"building","new building"}),
      "An inconspicuous building, with nothing standing out about it apart " +
      "from a small sign planted directly in front of it.\n");
    add_item("sign", "@@read");
    add_cmd_item(({"sign","small sign"}), "read", "@@read");
    add_exit(BROOM + "city19", "north", 0);
    add_exit(BROOM + "city17", "south", 0);
    add_exit(BROOM + "pb_mageware_shop","east",0);
    add_exit(BROOM + "city11", "west", 0);
    reset_balifor_room();
}

string
long_descr()
{
    return tod_descr1() + " You stand in the center of the Business " +
    "district of Balifor, to the north and south are two large " +
    "roads heading to the city Gates and the Bay respectively. A road " +
    "also leads west into central Balifor. A new building overlooks " +
    "the road from the east. A sign has been planted in the ground " +
    "directly in front of it. " + season_descr() + "\n";
}

string
read()
{
    if(this_player()->query_skill(SS_SPELLCRAFT) > MINIMUM_SPELLCRAFT)
    {
      return "Upon the sign is the symbol of a huge white eye with a " +
       "black pupil and a red iris. Being skilled in spell lore, you " +
       "recognise this as the Night of the Eye - " +
       "a symbol of that singular event where the three moons of magic " +
       "align. It is also a symbol to alert practitioners of magic that " +
       "within this building can be purchase mageware equipment.\n";
    }
      return "Upon the sign is the symbol of a huge white eye with a " +
        "black pupil and a red iris. You are not sure what that means.\n";
}
