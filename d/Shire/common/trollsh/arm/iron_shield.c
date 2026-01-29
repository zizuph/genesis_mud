/*  Shield
 * Altrus, July 2005
 */
inherit "/std/armour";
inherit "/lib/keep.c";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>  

int ac = 40;

void
create_armour()
{
    set_name("shield");
    set_pname("shields");
    set_adj(({"dented", "iron" }));
    set_short("dented iron shield");
    set_long("This shield looks like it has seen much better days. It is dented in places, and pierced with holes. It is also very heavy.\n");

    set_default_armour(ac, A_SHIELD, ({ 0, 0, 0 }), 0);
    query_keepable();

    add_prop(OBJ_I_WEIGHT, 7500); 
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ac));
}
