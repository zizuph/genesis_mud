/* Mongoose pie from Kendermore, Gwyneth, May 1999 */

inherit "/std/food";
#include <stdproperties.h>

void
create_food()
{
    set_name("stew");
    set_adj("mongoose");
    add_adj("delicious");
    set_short("mongoose stew");
    set_pshort("stews");
    set_long("A delicious aroma rises from the mongoose stew. \n");
    set_amount(300);
}

