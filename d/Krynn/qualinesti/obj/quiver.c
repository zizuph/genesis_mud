inherit "/std/container";
inherit "/d/Genesis/std/wearable_pack";

inherit "/lib/keep";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include <wa_types.h>
#include "../local.h"

string
query_recover()
{
    return MASTER;
}
 
void
init_recover(string arg)
{
    ::init_keep_recover(arg);
}

void
create_container()
{
    set_name("quiver");
    set_adj("silver-laced");
    add_adj( ({ "silver", "laced", "white", "leather" }) );
    set_short("@@short_descr");
    set_long("This is silver-laced quiver of white leather, used " +
        "for holding arrows.\n");
    set_slots(A_ANY_SHOULDER);
    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_VOLUME, 8000);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(CONT_I_MAX_WEIGHT, 10000);
    add_prop(CONT_I_MAX_VOLUME, 10000);
    add_prop(OBJ_M_NO_STEAL, "You can not steal the quiver while it is worn.\n");
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_IS_QUIVER, 1);

    set_keep(1);    
}

public int
prevent_enter(object ob)
{
    if(!ob->id("arrow"))
        return 1;
    else     
        return 0;
}

string
short_descr()
{
    return "silver-laced leather quiver";
}

/*
 * Function name: short
 * Description  : Add the status of the container to it.
 * Arguments    : for_obj - who wants to know the short
 * Returns      : The short description.
 */
public varargs string
short(object for_obj)
{
    return short_descr();
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
}