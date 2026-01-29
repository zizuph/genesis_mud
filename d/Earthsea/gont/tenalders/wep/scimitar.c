/* standard bronze scimitar wielded by kargs in Gont
 *  Ten Alders 
 *  Amelia 5/3/97
*/

#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

public void
create_weapon()
{
    set_name("scimitar");
    add_name("sword");
    set_adj(({"bloody", "razor-edged", "bronze"}));
    set_short("razor-edged bronze scimitar");
    set_pshort("razor-edged bronze scimitars");
    set_long("Honed to a sharp razor edge, this "+
        "scimitar is crafted from fine mirror-like bronze. Its curved "+
        "blade looks thirsty for the blood of its next victim, "+
        "even though still dripping from the blood of its last.\n");
    set_default_weapon(31, 21, W_SWORD, W_SLASH | W_IMPALE, W_BOTH);
    add_prop(OBJ_I_WEIGHT, 3800);
    add_prop(OBJ_I_VALUE, 630);
}
