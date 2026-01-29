/*
 * /d/Gondor/minas/obj/horse_rake.c
 *
 * A tool for the bench in the Royal Stables
 *
 * Alto 23 April 2001
 *
 */
 
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"


void
create_object()
{
    set_name("rake");
    set_adj("tough");
    add_adj("wooden");
    set_short("tough wooden rake");
    set_pshort("tough wooden rakes");
    set_pname("rakes");
    set_long("This is a tough wooden rake used to clean out the stalls "
       + "in which horses live. It looks (and smells!) like it has been "
       + "in service for years. On the handle is a small inscription.\n");
    add_item(({"inscription", "small inscription"}), "The inscription "
        + "reads: Property of the Royal Stables.\n");
    add_item(({"handle"}), "It bears a small inscription.\n");
    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_WEIGHT, 150);
    seteuid(getuid(TO));
}

