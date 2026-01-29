/* 
 * Hard-bolied quail egg for Inns
 * Finwe, November 2007
 */

#include "/d/Faerun/defs.h"

inherit "/std/food";

void
create_food()
{
    set_name("egg");
    set_pname("eggs");
    set_short("hard-boiled quail egg");
    set_adj(({"hard-boiled", "quail"}));
    set_long("This is a hard-boiled quail egg. It is small and creme-colored with brown patches. It looks delicious and still warm.\n");
    set_amount(50);
}
