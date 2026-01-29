/*
 *  /d/Gondor/rhovanion/mirkwood/obj/wep/magical_weapon.c
 *
 */
#pragma strict_types

#include "../../defs.h"
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/weapon";

private object effect;

public void 
create_magical_weapon()
{    
    set_name(({"sword"}));
    add_name(({"longsword"}));
    set_short("single-edged longsword");
    set_adj(({"single-edged"}));
    set_long("This is a sword to be described.\n");
            
    set_hit(10);
    set_pen(10);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    set_hands(W_RIGHT);    
}

public int
notify_wield_weapon()
{
    return 0;
}

public int
notify_unwield_weapon()
{
    return 0;
}

public nomask void
create_weapon() 
{
    create_magical_weapon();
    set_wf(this_object());
}

public nomask void
set_effect(object neweffect)
{
    effect = neweffect;
}

public nomask object
query_effect()
{
    return effect;
}

public int
wield(object weapon)
{    
    if (objectp(effect)) 
    {
        // object target = environment(this_object());
        set_alarm(0.0, 0.0, &effect->activate_effect(wielder, this_object()));
    }
    return notify_wield_weapon();
}

public int 
unwield(object weapon)
{
    if (objectp(effect)) 
    {
        object target = this_object()->query_wielded();
        effect->deactivate_effect(target, this_object());
    }
    return notify_unwield_weapon();
}