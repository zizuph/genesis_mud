inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/farlong.h"

reset_room()
{
    if (!present("_mayor"))
    {
        object mayor;
        mayor = clone_object(RHUN + "npc/mayor");
        mayor->add_name("_mayor");
        mayor->move(TO, 1);
    }
}
