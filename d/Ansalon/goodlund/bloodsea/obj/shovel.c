inherit "/std/object";
inherit "/lib/holdable_item";
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"


void
create_object()
{
    set_name("shovel");
    add_adj("iron");
    set_short("iron shovel");
    set_long("This is an iron shovel with a wooden handle. You imagine it " +
       "would be good for digging.\n");

    set_slots(W_ANYH);

    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,2000);
}


void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    holdable_item_leave_env(env, to);
}
