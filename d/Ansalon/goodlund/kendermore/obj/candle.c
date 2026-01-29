/* Beeswax candle by Gwyneth 05/20/99 */

inherit "/std/torch";
#include <stdproperties.h>
#include <macros.h>

#define adjecs query_adjs()

string *adjs=({"white", "beige", "yellow"});

void
create_torch()
{
    set_name("candle");
    set_adj(adjs[random(3)]);
    add_adj("beeswax");
    set_long("This is a large " + adjecs[0] + " beeswax candle.\n");
    set_strength(2);
}

query_recover()
{
    return MASTER + ":" + query_torch_recover();
}

init_recover(string arg)
{
    init_torch_recover(arg);
}

