/* 
 * Standard Chainmail Armour for the Eldoral Tunnels
 *
 * Chainmail is made of chain links. As such, it is especially
 * vulnerable to piercing damage.
 *
 * Created by Petros, November 2008
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

public int armour_class = 20;
public string * quality_list = ({
    "dull",
    "rusty",
    "warped",
    "dented",
    "chipped",
    "dirty",
});

create_armour()
{
    string quality;
    set_name( ({"armour"}) );
    add_name( ({ "chainmail" }) );
    quality = one_of_list(quality_list);
    set_short(quality + " iron chainmail");
    set_adj("iron");
    add_adj(quality);
    set_long("This " + query_short() + " has been constructed out of many "
        + "interlocking chain links. the chains are made of simple iron "
        + "and overall the armour looks like it has seen better days. It "
        + "fits like a shirt and covers the chest.\n");
    set_ac(armour_class);
    set_at( A_TORSO );
    set_am( ({ -5, 0, 0 }) ); // vulnerability to impaling attacks.
    
    add_prop(OBJ_I_WEIGHT, 
        F_WEIGHT_DEFAULT_ARMOUR(armour_class, A_TORSO) - random(203)); 
    add_prop(OBJ_I_VOLUME, 3500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(armour_class) + random(303));
}

public string
query_recover() 
{ 
    return MASTER+":"+query_arm_recover(); 
}

public void
init_recover(string arg)
{
    init_arm_recover(arg);
}
