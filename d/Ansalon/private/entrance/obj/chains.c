/* Chains for Kender Quest, Gwyneth, August 1999 */

inherit "/std/object";

#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_object()
{
    set_name("manacles");
    set_pname("sets of manacles");
    set_adj("rusted");
    set_short("rusted manacles");
    set_pshort("rusted sets of manacles");
    set_long("This is a pair of rusted manacles, with a sturdy chain " + 
        "connecting the two. A lock is set in each manacle.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME, 120);
    add_item("lock", "It is rusted shut.\n");
}

