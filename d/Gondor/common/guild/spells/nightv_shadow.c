#pragma save_binary
#pragma strict_types

inherit "/std/shadow.c";

#include <macros.h>
#include <stdproperties.h>

int     strength;

mixed 
query_prop(string propname)
{
    mixed    ret = shadow_who->query_prop(propname);

    if (propname == LIVE_I_SEE_DARK)
    {
        if (!environment(shadow_who)->query_prop(ROOM_I_INSIDE))
            ret += strength;
        else if (shadow_who->query_company() == "Gondor")
            ret += MAX(1, strength/2);
    }
    return ret;
}

void
set_strength(int i)
{
    strength = i;
}

void
remove_nightv_shadow()
{
    remove_shadow();
}

