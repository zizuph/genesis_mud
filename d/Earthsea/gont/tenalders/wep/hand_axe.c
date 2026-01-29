/* small axe for beach scavengers on Gont
 *  for use with npcs in /d/Earthsea/gont/beach
 *  Amelia 5/3/97
*/

#pragma strict_types

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

public void
create_weapon()
{
    set_name("axe");
    set_pname("axes");
    set_adj(({"iron", "beard"}));
    set_short("iron beard axe");
    set_pshort("iron beard axes");
    set_long("A small axe, wielded in one hand, " +
        "with a sharp axehead made from iron.\n");
    set_default_weapon(16, 22, W_AXE, W_IMPALE | W_SLASH | W_BLUDGEON, W_RIGHT);
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VALUE, 300);
}
