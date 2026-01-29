#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"
inherit RHUN + "stowns/mayor_master";

create_room()
{
    set_short("Mayor's house");
    set_long("This is the home of the mayor of this little town.  It is " +
        "a bit more well-furnished than others in town, though still " +
        "not especially impressive.  The exit heads back to the northeast.\n");

    AE(RHUN + "stown1/crossroads", "northeast");

    IN;

    reset_room();
}

