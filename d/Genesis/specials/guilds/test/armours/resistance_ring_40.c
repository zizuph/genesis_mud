/* 
 * Standard Resistance Ring
 * 
 * This ring provides a standard resistance amount to be used
 * for guild testing purposes. Code copied and adapted from the
 * sample code in "man resistance"
 *
 * Created by Petros, April 2010
 */

#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/armour";

public void
create_armour()
{
    set_name("ring");
    set_adj( ({ "resistance" }) );
    set_short("resistance 40 ring");
    set_long("This is a standard resistance ring with 40% magic "
        + "resistance.\n");
    
    set_default_armour(1, A_R_FINGER, 0, this_object());
    
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 10);
    
    add_prop(OBJ_I_VALUE, 2 * 1728);    
}

public mixed
query_magic_protection(string prop, object what)
{
    if (what == query_worn())
    {
        switch (prop)
        {
        case MAGIC_I_RES_MAGIC:
            return ({ 40, 0 });
        }
    }
    
    return ::query_magic_protection(prop, what);
}

public mixed
wear(object ob)
{
    object tp = this_player();
    
    if ((ob != this_object()) || (tp != environment(this_object())))
    {
        return -1;
    }
    
    tp->add_magic_effect(this_object());
    return 0;
}

public mixed
remove(object ob)
{
    object tp = this_player();
    
    if ((ob != this_object()) || (tp != query_worn()))
    {
        return -1;
    }
    
    if (!living(tp))
    {
        return 0;
    }
    
    tp->remove_magic_effect(this_object());
    return 0;    
}

