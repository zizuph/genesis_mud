/*
 * Random item for the Scavanger hunt
 * Coded by Finwe September 2003
 * Originally coded for the Shire, cleaned up in October 2015
 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name("skillet");
    add_name("frying skillet");
    set_adj("cast");
    set_adj("iron");
    set_short("cast iron frying skillet");
    set_long("This is "+short()+". It looks like it has been well used " +
        "as there is residue of burned on food on the side. The skillet " +
        "is round and heavy as it was made from iron.\n");
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_WEIGHT, 4);
}
