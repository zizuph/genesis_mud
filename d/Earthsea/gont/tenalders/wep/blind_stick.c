/* stick from scarecrow to use as small polearm
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
    set_name("staff");
    set_pname("staves");
    add_adj(({"long", "yew"}));
    set_short("long yew staff");
    set_pshort("long yew staves");
    set_long("A long staff carved from yew, apparently to " +
        "assist in walking.\n");
    set_default_weapon(8, 9, W_POLEARM, W_BLUDGEON, W_ANYH);
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VALUE, 150);
}
