/* Weapon coded by Arren, September 93 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

create_weapon()
{
    set_name("knife");
    set_adj("cooking");
    set_short("cooking knife"); 
    set_long(BS("A knife used while cooking.\n"));

    set_default_weapon(8, 8, W_KNIFE, W_IMPALE, W_ANYH, 0);
}
