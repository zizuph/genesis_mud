inherit "/std/object";
#include "/d/Kalad/defs.h"
 /* Sarr */

void
create_object()
{
    set_name("basin");
    set_adj("water");
    set_short("water basin");
    set_long("This is a stone block with a deep hole cut into it in the "+
    "shape of a half-sphere. In it, you can see a lot of water. Just off "+
    "to the side, you see a tube jutting out of the wall, where a "+
    "trickle of water spouts out into the basin.\n");
    add_prop(OBJ_M_NO_GET,1);
}

enter_env(object to, object from)
{
    ::enter_env(to,from);
    to->add_prop(OBJ_I_CONTAIN_WATER,1);
}

