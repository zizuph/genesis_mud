#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild/north/obj/cloak_base.c";

#include "/d/Gondor/defs.h"

#include <macros.h>
#include <stdproperties.h>

public void
create_robe()
{
    set_name("cloak");
    add_name("_RoN_cloak_");
    set_adj(({"dark-grey", "grey", }));
    set_short("dark-grey cloak");
    set_colour("grey");
    set_long(BSN("This is a hooded cloak made of heavy, dark-grey cloth. "
      + "The cloak is well designed for protection against wind and rain, "
      + "as well as aiding the wearer in hiding in the dark."));
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
}

public string
query_auto_load()
{
    return MASTER + ":";
}

public int
query_recover()
{
    return 0;
}

