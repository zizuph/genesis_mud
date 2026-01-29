#pragma strict_types

inherit "/std/receptacle.c";

#include <stdproperties.h>
#include "../nov.h"

void
create_receptacle()
{
    
    set_short("wooden chest");
    set_pshort("wooden chests");
    set_name("chest");
    add_adj("wooden");
    set_long("This is a wooden chest, ment for storing various " +
    "components for the necromancers.\n");
 
    //set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "The wooden chest is fixed to the floor.\n");
    add_prop(CONT_I_MAX_VOLUME, 500000);
    add_prop(CONT_I_MAX_WEIGHT, 750000);
    add_prop(CONT_I_VOLUME,  45000);
    add_prop(CONT_I_WEIGHT,  50000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     0);
    add_prop(CONT_I_CLOSED, 1);
    
    setuid();
    seteuid(getuid());
 
}
