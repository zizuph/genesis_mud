
/*
 *shiny_object.c
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
    add_name("_quest_shiny_object_");
    set_adj("shiny");
    add_adj("ferret");

    set_short("shiny ferret tag");
    set_pshort("shiny ferret tags");
    set_long("This shiny object is a ferret name tag. This one belongs to a "+
        "ferret named 'Trilob' \n");

    add_prop(OBJ_I_WEIGHT,1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_VALUE, 0);

}

