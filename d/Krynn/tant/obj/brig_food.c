/* Some iron rations on a brigand by Teth Jan 18 1997 */

inherit "/std/food";
#include "../local.h"

public void
create_food()
{
    set_name("rations");
    add_name(({"ration","food"}));
    set_pname("rations");
    add_pname("foods");
    set_adj("iron");
    set_short("iron rations");
    set_pshort("iron rations");
    set_long("This is iron rations, a palatable food that is used by " +
        "travellers, since it stays without decaying over a long period " +
        "of time.\n");
    set_amount(10);
}
