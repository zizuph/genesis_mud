/*
 * /d/Gondor/minas/obj/horse_mallet.c
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
    set_name("mallet");
    set_adj("small");
    add_adj("wooden");
    set_short("small wooden mallet");
    set_pshort("small wooden mallets");
    set_pname("mallets");
    set_long("This is a small wooden mallet used to nail iron shoes to "
       + "the hooves of horses. On the handle is a small inscription.\n");
    add_item(({"inscription", "small inscription"}), "The inscription "
        + "reads: Property of the Royal Stables.\n");
    add_item(({"handle"}), "It bears a small inscription.\n");
    add_prop(OBJ_I_VALUE, 50);
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_WEIGHT, 150);
    seteuid(getuid(TO));
}

