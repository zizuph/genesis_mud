#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <stdproperties.h>
inherit "/std/object";

create_object() 
{
    set_name("ember");
    set_short("hot ember");
    set_adj("hot");
    add_name("kender_ember");
    
    set_long("The ember is quite hot. That's why it is so good at warming things up.\n");
    
    add_prop(OBJ_I_WEIGHT,5);
    add_prop(OBJ_I_VOLUME,5);
    add_prop(OBJ_I_NO_GIVE,1);
    add_prop(OBJ_M_NO_GET,"The ember is too hot for your hands.\n");
}
