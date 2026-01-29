inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>

create_object() 
{
    seteuid(getuid());
    set_name("_corpse_rubble");
    add_name("rubble");
    add_name("pile of rubble");
    set_short("pile of rubble");
    set_long("This is a big pile of rubble. It " +
	     "appears to have been some kind of statue.\n");

    add_prop(OBJ_I_VOLUME, 60000+random(20000));
    add_prop(OBJ_I_WEIGHT, 80000+random(20000));
    add_prop(OBJ_I_VALUE, 0);
}
