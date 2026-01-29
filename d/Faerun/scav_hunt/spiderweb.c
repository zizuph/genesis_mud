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
    set_name("spiderweb");
    set_adj("delicate");
    set_adj("silk");
    set_short("delicate silk spiderweb");
    set_long("This is "+short()+". It is circular with criss-crossed " +
        "threads. It was spun by a large spider, and its threads are " +
        "thick and silky looking. The spiderweb looks almost invisible " +
        "but appears in good shape. The threads glisten in the light.\n");

	add_prop(OBJ_I_WEIGHT, 50);
	add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 400);
}
