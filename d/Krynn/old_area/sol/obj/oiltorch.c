/* A torch coded by Nick
 * modifed by Teth, Feb15,96
 */

inherit  "/std/torch";
#include <macros.h>

void
create_torch()
{
    set_name("torch");
    set_pname("torches");          /* The plural name. */
    set_adj("oil-dipped");
    set_long("This piece of wood has been dipped in oil, producing a " +
             "longer-lasting flame when it is used as a torch.\n");
    set_strength(3);
    set_short("oil-dipped torch");
    set_pshort("oil-dipped torches");
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
