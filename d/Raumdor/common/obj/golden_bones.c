inherit "/std/object";
#include "/d/Raumdor/defs.h"
/* Pile of bones, Sarr */

void
create_object()
{
    set_name("bones");
    add_adj("golden");
    set_short("pile of golden bones");
    set_pshort("piles of golden bones");
    set_long("These look like skeleton bones, but they are made out of gold!\n");
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,1400);
    add_prop(OBJ_I_VALUE,13824);
}


