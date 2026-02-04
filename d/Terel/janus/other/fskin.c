/*  fskin.c */
/*  janus 920701 */

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_object()
{
    set_name("pelt","ferret pelt");
    set_adj("small");
    set_long("The pelt from the ferret looks like it is of good quality\n"+
        ", maybe a tanner could use it.\n");
    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME,100);  
    add_prop(OBJ_I_VALUE, 20);
}

