/*  hskin.c */
/*  janus 920701 */

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_object()
{
    set_name("pelt","hare pelt");
    set_adj("small","hare");
    set_long("The pelt from the hare looks like it is of good quality,\n"+
        "maybe a tanner could use it.\n");
    add_prop(OBJ_I_WEIGHT,200);
    add_prop(OBJ_I_VOLUME,180);
    add_prop(OBJ_I_VALUE, 10);
}


