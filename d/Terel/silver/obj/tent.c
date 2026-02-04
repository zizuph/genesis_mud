#include "/d/Terel/include/Terel.h"

#include "../include/defs.h"

inherit STDOBJECT;

#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include <std.h>


create_object()
{
    set_name("tent");
    add_adj(({"green", "rudge"}));

    set_short("green ridge tent");
    set_long("This is a regular ridge tent, it has a rectangular floor shape " +
             "that ranges between 20-30 feet in width and 10-15 feet in height. " +
	     "At each corner of the tent, a wooden pole is stuck to the ground " +
	     "with a guy rope bound to each of them to maintain the balance and " +
	     "structure of it all.\n");
    add_prop(OBJ_I_NO_GET,1);

}
