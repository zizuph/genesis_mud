/* 
 * Roasted pheasant for an inn
 * Finwe, November 2007
 */

#include "/d/Faerun/defs.h"

inherit "/std/food";

void
create_food()
{
    set_name("pheasant");
    set_pname("pheasants");
    set_short("roasted pheasant");
    set_adj(({"fresh", "roasted"}));
    set_long("This is a fresh roasted pheasant. It's plump and a golden color from roasting for a fire.\n");
    set_amount(300);
}
