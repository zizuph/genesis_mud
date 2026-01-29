/* A small torch - recoded by Tulix III, 07/08/95 */

inherit "/std/torch";
#include "/d/Emerald/defs.h"
 
void
create_torch()
{
    set_name("torch");
    set_pname("torches");
    set_adj("small");
    set_short("small torch");
    set_pshort("small torches");
    set_long("It's a small torch.\n");
    
    add_prop(OBJ_I_WEIGHT,300);
    add_prop(OBJ_I_VOLUME,600);
    
    set_time(250);
    set_strength(1);
}
