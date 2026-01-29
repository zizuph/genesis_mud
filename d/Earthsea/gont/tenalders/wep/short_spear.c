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
    set_pname("spears");
    set_adj(({"short", "flint"}));
    set_short("short flint spear");
    set_pshort("short flint spears");
    set_long("A short spear with a knapped flint "+
        "spearhead. It is not worth much, but still has some "+
        "usefulness.\n");
    set_default_weapon(15, 10, W_POLEARM, W_SLASH | W_IMPALE, W_RIGHT);
    add_prop(OBJ_I_WEIGHT, 1900);
    add_prop(OBJ_I_VALUE, 320);    
}
