/* Kendermore berries, Gwyneth May 1999 */
inherit "/std/food";
#include <stdproperties.h>

void
create_food()
{
    set_name("berries");
    set_adj("ripe");
    set_short("bunch of ripe berries");
    set_pshort("bunches of ripe berries");
    set_long("This bunch of ripe berries looks delicious! \n");
    set_amount(20);
}
