/* spiked club for kargs in Gont
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
    set_name("club");
    set_adj(({"ebony", "spiked"}));
    set_short("ebony spiked club");
    set_pshort("ebony spiked clubs");
    set_long("A solid ebony club implanted with "+
        "needle-keen bronze spikes. An evil-looking weapon made to "+
        "crush and impale at the same time.\n");
    set_default_weapon(21, 27, W_CLUB, W_IMPALE | W_BLUDGEON, W_ANYH);
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VALUE, 200);
}
