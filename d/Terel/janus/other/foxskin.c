/*  foxskin.c */
/*  janus 920701 */

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_object()
{
    set_name("pelt","fox pelt");
    set_adj("red","gray");
    set_long("The pelt from the fox looks like it is of good quality,\n"+
             "maybe a tanner could use it.\n");
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,1000);
}

