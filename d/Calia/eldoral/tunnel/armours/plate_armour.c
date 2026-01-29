/* 
 * Standard Plate Armour for the Eldoral Tunnels
 *
 * Created by Petros, November 2008
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

public int armour_class = 25;
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
    quality = one_of_list(quality_list);
    set_short(quality + " plate armour");
    set_adj(quality);
    set_adj("plate");
    set_long("This " + query_short() + " is a very heavy piece of armour "
        + "that covers the chest. The metal looks worn and dented from "
        + "having seen many battles.\n");
    set_ac(armour_class);
    set_at( A_TORSO );

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
