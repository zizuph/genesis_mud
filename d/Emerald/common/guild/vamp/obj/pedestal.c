inherit "/std/container";

#include <stdproperties.h>
#include <composite.h>

public void
create_container()
{
    set_name("pedestal");
    add_adj(({ "sturdy", "polished", "wooden" }));
    
    set_short("wooden pedestal");
    set_long("A sturdy, polished, wooden pedestal.\n");

    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);
    add_prop(CONT_I_VOLUME, 100000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_HEIGHT, 30);
}
