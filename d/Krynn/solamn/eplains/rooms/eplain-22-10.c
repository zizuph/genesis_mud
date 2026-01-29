#include "../local.h"
inherit TDIR+"eplain-L";

public void
create_eplains_room()
{
    ::create_eplains_room();

    add_std_exits();
    add_cmd_item(({"opening","rift","great rift","large cave","cave"}),"enter",
      "@@enter_tunnel");

}
