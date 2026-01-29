/* created by Aridor 07/06/93 */

inherit "/std/weapon";

#include "../local.h"
#include <wa_types.h>
#include <stdproperties.h>

create_weapon()
{
    set_name("knife");
    set_pname("knives");
    set_pname("weapons");
    set_adj("small");
    set_adj("sparkling");
    set_short("small sparkling knife");
    set_pshort("small sparkling knives");
    set_long("This knife sparkles in all different colors. "
	     + "It is small, but has a sharp tip.\n");

    set_default_weapon(14, 10, W_KNIFE, W_IMPALE, W_ANYH);

}

