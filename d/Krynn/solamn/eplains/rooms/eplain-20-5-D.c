#include "../local.h"
inherit TDIR+"eplain-D";

public void
create_eplains_room()
{
    ::create_eplains_room();

    add_std_exits();
    add_exit(DARGAARD_LINK, "southeast", 0,0);
}
