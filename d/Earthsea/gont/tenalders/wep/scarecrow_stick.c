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
    set_name("stick");
    set_pname("sticks");
    add_adj(({"wooden", "pine"}));
    set_short("wooden pine stick");
    set_pshort("wooden pine sticks");
    set_long("A medium-length pine stick.\n");
    set_default_weapon(15, 10, W_POLEARM, W_BLUDGEON, W_ANYH);
    add_prop(OBJ_I_WEIGHT, 900);
    add_prop(OBJ_I_VALUE, 100);
}
