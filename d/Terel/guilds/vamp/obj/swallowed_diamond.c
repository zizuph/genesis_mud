
#include "../guild.h"

inherit "/std/object";

#include <stdproperties.h>

int charges;

public void remove_gem()
{
    ENV(TO)->catch_msg("You feel the effects of the diamond fade.\n");
    remove_object();
}


public void create_object()
{
    set_name("_swallowed_diamond");
    
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "A swallowed diamond");

    set_no_show();
    set_alarm(600.0,0.0,remove_gem);
    charges=4+random(6);
}

public int reduce_charges()
{
    charges--;
    if (charges<=0)
    {
        remove_gem();
    }
}

