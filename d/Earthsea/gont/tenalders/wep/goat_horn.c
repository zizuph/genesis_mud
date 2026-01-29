/* a goat horn that can be used as a newbie knife
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
    set_name("horn");
    add_name("knife");
    set_pname(({"horns", "knives"}));
    add_adj(({"hard", "sharp"}));
    set_short("goat horn");
    set_pshort("goat horns");
    set_long("A horn from a goat. It is very hard and "+
        "sharp and might be used as a knife.\n");
    set_default_weapon(8, 10, W_KNIFE, W_IMPALE, W_ANYH);
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VALUE, 75);
}
