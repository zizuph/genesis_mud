/* Fishing gaff to help land the big sports fish!
 *
 * Arman - March 2021
 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

void
create_weapon()
{
    set_name("gaff");
    set_pname("gaffs");
    add_name("_fishing_gaff");
    set_adj("fishing");
    set_short("fishing gaff");
    set_pshort("fishing gaffs");
    set_long("This is a long pole with a sharp hook on the end that is used by " +
        "fisherman to stab large fish too heavy for fishing line and lift them " +
        "onto the shore or into a boat.\n");

    set_default_weapon(20, 15, W_POLEARM, W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 5000);
}

