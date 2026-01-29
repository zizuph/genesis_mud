#include "/d/Rhovanion/defs.h"
inherit MIRK_DIR+"mirk-s";

void
create_map_room()
{
    ::create_map_room();
    remove_exit("east");
    add_exit(ESG_DIR+"westbridge2", "east", 0, 1);
}
