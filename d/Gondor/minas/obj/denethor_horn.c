/*
 * /d/Gondor/minas/obj/denethor_horn.c
 *
 * The cloven horn in Denethor's lap
 *
 * Alto 23 April 2001
 *
 */
 
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

object actor;

void
create_object()
{
    set_name("horn");
    add_name("cloven horn", "warhorn");
    set_adj("mighty");
    add_adj("cloven");
    set_short("mighty cloven horn");
    set_pshort("mighty cloven horns");
    set_pname("horns");
    set_long("The two halves of a cloven wild-ox horn. This is an "
        + "heirloom of the House of Hurin, borne by the eldest son "
        + "in the House of Stewards. When it was intact, its mighty "
        + "call could be heard for leagues in any direction.\n");
    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 100);
    seteuid(getuid(TO));
}

