/* Rat husk, quest item for Kender Rat Quest, Gwyneth, June 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name(({"rat","_ansalon_d_rat_"}));
    add_name("husk");
    add_name("corpse");
    set_adj("dead");
    add_adj("dried");
    add_adj("rat");
    set_short("dead rat husk");
    set_pshort("dead rat husks");
    set_long("This dried out husk of a rat corpse certainly looks " + 
        "disgusting. At least it doesn't smell anymore!\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 220);
    add_prop(OBJ_I_VOLUME, 130);
}

