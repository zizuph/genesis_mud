/*
 * quill.c
 *
 */

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit "/std/object";

int wet;

create_object()
{
    set_name("quill");
   add_name(({"_quill_","pen"}));

    set_short("quill");
    add_adj("feathered");

    set_long("This is a feathered quill you could write with.\n");

    add_prop(OBJ_I_WEIGHT,  4);
    add_prop(OBJ_I_VALUE,  24);
    add_prop(OBJ_I_VOLUME, 10);

    wet = 10;
}

int
query_wet()
{
    return wet > 0;
}

int
set_wet()
{
    wet = 10;
}

varargs int
add_dry(int much = 1)
{
    wet -= much;
    if (wet<0)
	wet = 0;
    return wet;
}
