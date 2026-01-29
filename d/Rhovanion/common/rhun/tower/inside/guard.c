#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"

static object ggg;

void reset_room()
{

    if (!objectp(ggg))
    {
        ggg = clone_object(RHUN_DIR+"npc/easterling_guard");
        ggg->arm_me();
        ggg->move(TO,1);
        TO->tell_room(TO, QCTNAME(ggg)+" arrives.\n");
    }
}
