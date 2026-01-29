/* Skeleton helmet by Teth, April 5, 1996 */

inherit "/std/armour";
#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_armour()
{
    set_name("helmet");
    add_name(({"armour","helm"}));
    set_pname("helmets");
    add_pname(({"armours","helms"}));
    set_ac(5);
    set_am( ({ 0, 1, -1 }) );
    set_at(A_HEAD);
    add_adj( ({ "hard", "leather" }) );
    set_short("hard leather helmet");
    set_pshort("hard leather helmets");
    set_long("This helmet is of decent quality. It is made of hardened "+
             "leather, which would surely offer more protection than "+
             "wearing nothing on your head at all. Brown and well-oiled, "+
             "this hard leather helm is hardly fashionable, but it gets "+
             "the job done.\n");
    add_prop(OBJ_I_VOLUME, 2150);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(5, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5));
}

