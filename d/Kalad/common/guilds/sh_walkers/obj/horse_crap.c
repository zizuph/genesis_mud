inherit "/std/heap";
#include "/d/Kalad/defs.h"
 /* Sarr */

void
create_heap()
{
    set_name("crap");
    add_name("pile");
    set_adj("horse");
    set_short("pile of horse crap");
    set_long("This is a small pile of horse crap. It "+
    "really stinks!\n");
    add_name("_kalad_horse_crap");
    add_prop(HEAP_S_UNIQUE_ID,query_short()+"_");
    add_prop(HEAP_I_IS,1);
    add_prop(HEAP_I_UNIT_VOLUME,90);
    add_prop(HEAP_I_UNIT_WEIGHT,100);
    set_heap_size(1);
}
