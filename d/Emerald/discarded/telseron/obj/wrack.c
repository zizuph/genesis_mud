/* township/obj/wrack.c is cloned by township/forge.c */
inherit "/std/container";
 
#include "/d/Emerald/defs.h"
 
 
void
create_container()
{
    set_name("rack");
    set_short("weapon rack");
    set_adj("weapon");
    set_long("It's a simple wooden rack that the blacksmith uses to store"+
        " unclaimed or lost weapons.\n");
 
    add_prop(CONT_I_WEIGHT,5000);
    add_prop(CONT_I_MAX_WEIGHT,50000);
    add_prop(CONT_I_VOLUME,5500);
    add_prop(CONT_I_MAX_VOLUME,60000);
    add_prop(CONT_I_RIGID,1);
    add_prop(OBJ_M_NO_GET,"The rack seems to be firmly secured to the floor"+
        ".\n");
}
