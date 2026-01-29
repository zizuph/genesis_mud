/*
 * Random item for the Scavanger hunt
 * Coded by Finwe September 2003
 * Originally coded for the Shire, cleaned up in October 2015
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

void
create_object()
{
    seteuid(getuid());
    set_name("skeleton");
    set_adj("fish");
    set_adj("dirty");
    set_short("dirty fish skeleton");
    set_long("This is "+short()+". It is dried and hideous looking, " +
        "with lots of teeth marks on it, with all the flesh picked " +
        "from the bones. The skeleton is quite large, but many of " +
        "the bones are broken.\n");

	add_prop(OBJ_I_WEIGHT, 50);
	add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 400);
}
