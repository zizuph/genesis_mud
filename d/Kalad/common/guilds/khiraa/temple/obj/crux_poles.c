/* 
 * /d/Kalad/common/guilds/khiraa/dk/obj/c_hook.c
 * Purpose    : This is a large iron hook to hook things on.
 * Located    : Can be bought by vile the smith
 * Created By : Sarr 12.Apr.97
 * Modified By: 
 */ 

inherit "/std/object";
#include "/d/Kalad/defs.h"

void
create_object()
{
    set_name("poles");
    add_name("_crucifix_poles_");
    add_adj(({"long","wooden"}));
    set_short("pair of long wooden poles");
    set_pshort("pairs of long wooden poles");
    set_long("These are a pair of long, wooden poles. One is longer "+
    "than the other, and one has a point in the end to stab into "+
    "the ground.\n");
    add_prop(OBJ_I_WEIGHT,200);
    add_prop(OBJ_I_VOLUME,170);
    add_prop(OBJ_I_VALUE,0);
}

