/*
 *  /d/Gondor/morgul/city/mm_stables/obj/rack.c
 *
 *  The rack in the office of the Stable Master of Minas Morgul.
 *
 *  Deagol, August 2002
 */

inherit "/std/container";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_container()
{
    ::create_container();
    
    set_name("rack");
    add_name("huge wooden rack");
    set_adj(({"huge", "wooden"}));
    set_short("huge wooden rack");
    set_long("A huge wooden rack with basswork fittings. It is used " +
             "to store saddles, saddlebags, riding boots and other items.\n");

    add_prop(OBJ_M_NO_GET, "The rack is too heavy, you cannot take it!\n");
             
    add_prop(CONT_I_MAX_VOLUME, 300000);
    add_prop(CONT_I_MAX_WEIGHT, 600000);
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(CONT_I_WEIGHT, 20000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);
}
