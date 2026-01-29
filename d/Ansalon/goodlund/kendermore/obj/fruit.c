/* Generic piece of fruit from Kendermore, Gwyneth, May 1999 */

inherit "/std/food";
#include <stdproperties.h>

void
create_food()
{
    set_name("fruit");
    set_adj("ripe");
    set_short("piece of ripe fruit");
    set_pshort("pieces of ripe fruit");
    set_long("This piece of fruit looks delicious. \n");
    set_amount(20);
}

