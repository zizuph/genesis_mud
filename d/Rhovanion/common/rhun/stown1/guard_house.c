#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"
inherit RHUN + "stowns/guard_master";

create_room()
{
    set_short("Guard house");
    set_long("You are standing in the guardhouse at the north end of " +
        "this little town.  It is made entirely of wood, and is sparsely " +
        "furnished.  The only exit from it leads south to a crossroads.\n");

    AE(RHUN + "stown1/crossroads", "south");

    IN;

    reset_room();
}
