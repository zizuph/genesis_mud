#include <ss_types.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <macros.h>

inherit "/std/object";

void
create_object()
{
    set_name("_fireknives_pole_");
    add_name("pole");
    add_adj(({"long","wooden"}));
    
    set_short("long wooden pole");
    
    set_long("This is a long reinforced wooden "
    +"pole about 3 meters. "
    +"One end of the long pole goes into a steel shod tip, "
    +"meant to be hammered into the ground while the other "
    +"end has a metal ring attached to it. A dangling "
	+"rope is attached to the metal ring.\n");
    
    add_prop(OBJ_I_WEIGHT,4000);
    add_prop(OBJ_I_VOLUME,2000);
    add_prop(OBJ_I_VALUE,0);
}

