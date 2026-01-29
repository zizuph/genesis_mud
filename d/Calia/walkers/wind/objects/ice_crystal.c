
inherit "/std/heap";
#include <stdproperties.h>
#include "defs.h"

create_heap()
{
    set_name("ice crystal");
    add_name("ice");
    add_name("crystal");
    add_pname("crystals");
    add_pname("ice crystals");
    set_short("ice crystal");
    set_pshort("ice crystals");
    set_long("It is a perfectly formed ice crystal.\n");
    set_heap_size(1);
    add_prop(OBJ_M_NO_STEAL,1);
    add_prop(HEAP_I_UNIT_VOLUME,0);
    add_prop(HEAP_I_UNIT_WEIGHT,0);
    add_prop(HEAP_I_UNIT_VALUE,0);
    add_prop(HEAP_S_UNIQUE_ID, "ice crystal");
}
