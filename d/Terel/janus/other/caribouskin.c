/*  caribouskin.c */
/*  janus 920701 */

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_object()
{
    set_name("pelt","caribou pelt");
    set_adj("caribou");
    set_long("The pelt from the caribou looks like it is of good quality,\n"+
        "maybe a tanner could use it.\n");
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,2000);  
    add_prop(OBJ_I_VALUE, 300);
}

