
/* A spell component for the Elemental Worshippers of Calia. */ 

inherit "/std/heap";
#include <stdproperties.h>
#include "defs.h"

void
create_heap()
{
    set_name("vial");
    set_pname("vials");
    add_name("water"); 
    set_adj("water"); 
    set_short("water vial");
    set_pshort("water vials"); 
    set_long("A small vial filled with water.\n");
    add_prop(OBJ_M_NO_STEAL,1);
    add_prop(HEAP_I_UNIT_VOLUME,50);
    add_prop(HEAP_I_UNIT_WEIGHT,50);
    add_prop(HEAP_I_UNIT_VALUE,0);
    add_prop(HEAP_S_UNIQUE_ID, "water vial");
    add_prop(OBJ_I_CONTAIN_WATER,1);

    set_heap_size(1); 
}

