/*  Imported from Old Roke, for the marshal at the jailhouse
 *  Also, some typos corrected and pname added
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
    set_name("bracers");
    set_adj("steel");
    add_adj("green");    
    set_short("pair of green steel bracers");
    set_pshort("pairs of green steel bracers");
    set_pname("pairs of green steel bracers");
    set_long("They are green steel bracers with the emblem of "+
        "two crossed axes over a map of the world on each "+
        "bracer.\n");
    set_keep(1);
    set_ac(30);
    set_am(({ 0, 2, -2}));
    set_at(A_ARMS);
    add_prop(OBJ_I_VALUE, 775);
}
