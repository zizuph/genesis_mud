
inherit "/std/object";
#include <stdproperties.h>
#include "defs.h"

create_object()
{
    set_name("Worshippers Spell Object");
    add_name(I_CAN_CAST);
    set_short("spell_object");
    set_long("It's invisible...who cares?\n");
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    set_no_show();
    add_prop(OBJ_M_NO_STEAL,1);
    add_prop(OBJ_M_NO_DROP,1);
}
