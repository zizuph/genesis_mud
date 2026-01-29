
/*
 * chalice.c
 * A chalice, from the seekers' Temple
 * Town of Haven
 * Tibbit, 16 February 1998
 *
 */

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("chalice");
    add_name("_seeker_quest_chalice_");
    set_adj("simple");
    add_adj("silver");

    set_short("simple silver chalice");
    set_pshort("simple silver chalices");
    set_long("This chalice is a simple cup, created from "+
        "silver.  While it is not so bejeweled as some religious "+
        "items, the simplicity of the silver chalice is to be admired.  "+
        "At least, that's what the seekers say.\n");

    add_prop(OBJ_I_WEIGHT,400);
    add_prop(OBJ_I_VOLUME, 210);
    add_prop(OBJ_I_VALUE, 300);

}

