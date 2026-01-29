inherit "/std/container";
#include <stdproperties.h>
#include "../defs.h"

void
reset_container()
{
    if (!present("key", TO))
    clone_object(G_OBJ + "cell_key")->move(TO);
}

void
create_container()
{
    set_name("key rack");
    add_name("rack");
    set_adj("iron");
    set_short("key rack");
    set_long("A plain, rusty iron keyrackk.\n");  
    add_prop(CONT_I_WEIGHT, 1000);
    add_prop(CONT_I_VOLUME, 1000);
    add_prop(CONT_I_MAX_WEIGHT, 2000);
    add_prop(CONT_I_MAX_VOLUME, 1500);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(OBJ_M_NO_GET, "It has been fused to the wall.  Nice try, " +
        "though.\n");

    reset_container();
}
