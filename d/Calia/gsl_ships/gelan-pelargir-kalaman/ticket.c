
/* Ticket for the gelan-krynn shipline of Calia. */ 

#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

void
create_object()
{
    set_name("ticket");
    add_name("gelan-palanthas line");
    add_adj("beige");
    set_long("A beige ticket with the picture of a walnut stamped "+
             "on it.\n");
    add_prop(OBJ_I_VALUE, 30);
    add_prop(OBJ_M_NO_SELL, 1); 
}

