#include "../local.h"
inherit "/d/Krynn/throtyl/throtyl-5";

public void
create_throtyl_room()
{
    ::create_throtyl_room();

    add_std_exits();
    add_exit(SANCTION_LINK,"south", 0);

}

