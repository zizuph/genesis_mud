/* Ripe Kendermore strawberry, Gwyneth, June 1999 */

inherit "/std/food";
#include <stdproperties.h>

void
create_food()
{
    set_name("strawberry");
    add_name("fruit");
    set_adj("red");
    add_adj("ripe");
    set_short("strawberry with whipped cream");
    set_pshort("strawberries");
    set_long("This is a freshly picked red strawberry topped with whipped cream.\n");
    set_amount(30);
}
