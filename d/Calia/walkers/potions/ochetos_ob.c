
inherit "/std/object";

#include <stdproperties.h>
#include "defs.h"

int gTime;

set_remove_time(int i)
{
    if(!gTime)
        set_alarm(itof(i),0.0,"remove_object");
}


void
create_object()
{
    set_name("_ochetos_potion_object_");
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    set_no_show();
    add_prop(OBJ_M_NO_DROP,1);
}

void
enter_env(object to, object from)
{
    ::enter_env(to,from);
    tell_object(to,"You feel the effects of the watery green potion.\n");
}

void
remove_object()
{
    tell_object(environment(this_object()),"You feel the effects of the "+
        "watery green potion fade away.\n");
    ::remove_object();
}

