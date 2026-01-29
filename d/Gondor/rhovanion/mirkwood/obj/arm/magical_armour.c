/*
 *  /d/Gondor/rhovanion/mirkwood/obj/arm/magical_armour.c
 *
 *  Override create_magical_armour and use set_effect to determine the magical
 *  effect when wearing this armour.
 *
 *  Created by Eowul, November 15th, 2015
 *
 */
#pragma strict_types

#include "../../defs.h"
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/armour";

private object effect;

public void 
create_magical_armour()
{   
    set_name("belt");
    set_pname("belts");
    set_short("worn, leather belt");
    set_long("This is a worn leather belt.\n");
            
    add_adj("worn");
    add_adj("leather");
    
    set_at(A_WAIST);
    set_ac(1);
    set_am(({ 2, 2, -2 }));
}

public int
notify_wear_armour()
{
    return 0;
}

public int
notify_remove_armour()
{
    return 0;
}

public nomask void
create_armour() 
{
    create_magical_armour();
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
wear(object armour)
{    
    if (objectp(effect)) 
    {
        object target = environment(this_object());
        set_alarm(0.0, 0.0, &effect->activate_effect(target, this_object()));
    }
    return notify_wear_armour();
}

public int 
remove(object armour)
{
    if (objectp(effect)) 
    {
        object target = environment(this_object());
        effect->deactivate_effect(target, this_object());
    }
    return notify_remove_armour();
}