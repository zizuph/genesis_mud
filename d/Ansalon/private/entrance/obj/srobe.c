/* Shunar's robe, Gwyneth, August 26, 1999 */

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"


void
create_armour()
{
    set_name("robe");
    set_pname("robes");
    set_adj("dark");
    add_adj("black");
    set_short("dark black robe");
    set_pshort("dark black robes");
    set_long("This robe is dark black and plain.\n");
    set_ac(15);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE, 120);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 300);
}

