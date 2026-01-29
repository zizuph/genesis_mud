
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

string query_auto_load()
{
    return MASTER + ":";
}

create_object()
{
    set_name("Worshippers Permit Object");
    add_name(WOR_CAN_PERMIT);
    set_short("permit_object");
    set_long("It's invisible...who cares?\n");
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    set_no_show();
    add_prop(OBJ_M_NO_STEAL,1);
    add_prop(OBJ_M_NO_DROP,1);
}
