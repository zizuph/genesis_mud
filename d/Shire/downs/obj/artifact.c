/*
 * Artifact for barrow quest
 * -- Finwe January 2001
 */

inherit "/std/object";

#include <stdproperties.h>
#include "/d/Shire/sys/defs.h"
#include "../local.h"

create_object()
{
    set_name(({"_barrow_artifact", "scroll" }));
    set_short("ancient dusty scroll");
    set_adj("ancient");
    set_adj("dusty");
    set_long("This is an "+short()+". It is a large roll of parchment " +
        "that is aged and yellow. The edges are torn and there is " +
        "some writing on the scroll.\n");
    add_item(({"writing", "letters", "ancient letters"}),
        "The writing is faded grey and of ancient letters. The " +
        "characters are unreadable.\n");

    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VALUE, 2);
}
