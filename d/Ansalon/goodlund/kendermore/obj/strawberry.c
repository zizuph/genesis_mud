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
    set_short("ripe red strawberry");
    set_pshort("strawberries");
    set_long("This is a freshly picked red strawberry. \n");
    set_amount(30);
}
