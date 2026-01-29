inherit "/std/container";

#include <stdproperties.h>


public void
create_container()
{
    set_short("equipment rack");
    set_name("rack");
    set_adj("equipment");
    set_long("This rack may contain alot of general equipment.\n");


    add_prop(OBJ_M_NO_GET, "It is bolted to the ground.\n");
    add_prop(CONT_I_MAX_VOLUME, 500000);
    add_prop(CONT_I_MAX_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME,  5000);
    add_prop(CONT_I_WEIGHT, 25000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);
  
}


