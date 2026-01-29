inherit "/std/container";
#include <stdproperties.h>
#include "../defs.h"

void
reset_container()
{
    if (!present("torch", TO))
    clone_object(G_OBJ + "torch")->move(TO);
}

void
create_container()
{
    set_name("skeleton");
    set_adj("preserved");
    set_short("skeleton");
    set_long( BS("This is a well preserved, human skeleton.  It looks as if " +
        "it has been here a long, long time.\n"));  
    add_prop(CONT_I_WEIGHT, 8000);
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(CONT_I_MAX_WEIGHT, 9500);
    add_prop(CONT_I_MAX_VOLUME, 10500);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "Its so fragile, it would crumble to dust.\n");

    reset_container();
}
