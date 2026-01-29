/* trident for bridge troll
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
    set_name("trident");
    set_pname("tridents");
    set_adj(({"long", "bronze"}));
    set_short("long bronze trident");
    set_pshort("long bronze tridents");
    set_long("A long bronze trident with three "+
        "sharp prongs.\n");
    set_default_weapon(22, 22, W_POLEARM, W_SLASH | W_IMPALE, W_RIGHT);
    add_prop(OBJ_I_WEIGHT, 4500);
    add_prop(OBJ_I_VALUE, 330);
}
