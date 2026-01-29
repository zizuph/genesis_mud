
/*
 *silver_tag.c
 *Used in a ferret quest to find the 'missing' dead ferrets.
 *
 *Ares July 2004
 */

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("tag");
    add_name("_silver_ferret_tag_");
    set_adj("silver");
    add_adj("ferret");

    set_short("silver ferret tag");
    set_pshort("silver ferret tags");
    set_long("The barkeeper was right, this isn't a silver coin. "+
        "It's a ferret name tag. This one belongs to a "+
        "ferret named 'Trouble' \n");
    add_prop(OBJ_M_NO_STEAL, 1);

    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_VALUE, 0);

}

