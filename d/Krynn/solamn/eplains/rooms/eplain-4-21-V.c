#include "../local.h"
inherit TDIR+"eplain-V";

public void
create_eplains_room()
{
    ::create_eplains_room();

    add_std_exits();
    add_exit("river1","northwest","@@flood_closed@@",10,1);
    add_exit("/d/Krynn/solamn/eplains/ferryman_hut","southwest",0,2,1);

    if (flooded())
      set_alarm(0.0,0.0,start_ferry);
}
