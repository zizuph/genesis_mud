/* 
 * Hard-bolied quail egg for Inns
 * Finwe, November 2007
 */

#include "/d/Faerun/defs.h"

inherit "/std/food";

void
create_food()
{
    set_name("sausage");
    set_short("cooked sausage");
    set_adj(({"cooked"}));
    set_long("This is a cooked sausage. It is made from fresh meat and spices. The sausage has been smoke-cooked and looks delicious.\n");
    set_amount(70);
}
