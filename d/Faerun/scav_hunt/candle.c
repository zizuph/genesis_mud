/*
 * A small candle
 * Finwe, September 2015
 */

inherit "/std/torch";

#include <macros.h>
#include "/d/Faerun/defs.h"
/*
 * Function name: create_object
 * Description:   The standard create routine.
 */
void
create_torch()
{
    set_name("candle");
    set_pname("candles");          /* The plural name. */
    set_adj("small");
    set_long("This is a half-burned candle. It is made from beeswax and is caramel colored. The candle's wick is black and curled from recent use. It looks like it could still provide some light.\n");
    set_strength(1);
    set_short("small candle");
    set_pshort("small candles");
}

string
query_recover()
{
    return MASTER + ":" + query_torch_recover();
}

void
init_recover(string arg)
{
    init_torch_recover(arg);
}
