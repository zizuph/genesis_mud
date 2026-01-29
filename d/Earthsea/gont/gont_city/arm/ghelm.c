/*  Imported from Roke for Alexander
 *  Amelia, 3/24/98
 */

#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>

public void
create_armour()
{
    set_name("helm");
    set_pname("helms");
    set_adj("steel");
    add_adj("green");
    set_short("green steel helm");
    set_pshort("green steel helms");
    set_long("It is a green steel helm that has padding "+
        "on the inside. On the right side of the helm "+
        "is an emblem of two crossed axes over a map of the world.\n");
    set_ac(27);
    set_am(({ 0, 0, 0}));
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE, 500);
}
