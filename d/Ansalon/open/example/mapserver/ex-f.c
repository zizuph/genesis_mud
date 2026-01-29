#include "local.h"
inherit THIS_DIR+"ex_base";

public void
create_map_room()
{
    set_short("forest");
    set_long("In the deep forest.\n");
    add_rel_exits();
}
