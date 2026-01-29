inherit "/std/torch";
#include <stdproperties.h>
#include "../defs.h"

void
create_torch()
{
    set_name("torch");
    set_adj(({"plain", "large"}));
    set_short("large, plain torch");
    set_long(
"A plain, large torch.  It looks as if it might last a long time.\n");
    set_strength(3);
    set_time(1800);
    set_value(90);

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 450);
}
/*

string
query_recover()
{
    return G_OBJ + "torch:" + query_torch_recover();
}

void
init_recover(string arg)
{
int_torch_recover(arg);
}
*/
