/*
 */

#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name("phial");
    add_name(({"holy water", "phial of holy water"}));
    add_pname(({"holy waters", "phials of holy water"}));    
    set_adj(({"holy", "water"}));
    set_short("phial of holy water");
    set_pshort("phials of holy water");
    
    set_long("This is a small phial of holy water.\n");

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 125);

    set_keep();
}

string
query_recover()
{
    return MASTER;
}
