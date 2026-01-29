#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"
inherit RHUN + "stowns/home_master";

create_room()
{
    set_short("Small home");
    set_long("You have stepped into a small home in this tiny town.  " +
        "The walls are hewn of wooden logs, and the ceiling thatched.  " +
	"A few scattered bits of furniture are here-- a bed, chair and " +
	"table, for the most part.  The resident of this tiny estate is " +
	"obviously quite poor.  The only exit is back out a small open " +
	"doorway to the south.\n");

    AE(RHUN + "stown1/roadnw", "south");

    IN;

    add_item(({"furniture","bed","table","chair","chairs"}),
        "The furniture which adorns this humble abode is all made from " +
	"wood.  It is of no interest to you.\n");

    reset_room();
}

