/* standard bronze axe wielded by kargs in Gont
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
    set_name("axe");
    set_pname("axes");
    set_adj(({"broadheaded","bronze"}));
    set_short("broadheaded bronze axe");
    set_pshort("broadheaded bronze axes");
    set_long("A broadheaded bronze axe, whose blade "+
        "is double-sided, and terribly sharp. You notice the weight of "+
        "it is balanced for an effective swing.\n");
    set_default_weapon(21, 37, W_AXE, W_SLASH | W_BLUDGEON, W_ANYH);
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VALUE, 500);
}
