/* standard bronze spear wielded by kargs in Gont
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
    set_name("spear");
    set_pname("spear");
    set_adj("bronze-tipped");
    set_short("bronze-tipped spear");
    set_pshort("bronze-tipped spears");
    set_long("A bronze-tipped spear. The long haft, "+
        "made from ash wood, is tipped with a razor sharp bronze "+
        "spearhead that has a wicked set of double flanges.\n");
    set_default_weapon(22, 15, W_POLEARM, W_SLASH | W_IMPALE, W_RIGHT);
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VALUE, 1100);
}
