/* 
 * Squirrel stew for an inn
 * Finwe, November 2007
 */

#include "/d/Faerun/defs.h"

inherit "/std/food";

void
create_food()
{
    set_name("stew");
    set_pname("stews");
    set_short("squirrel stew");
    set_pshort("squirrel stews");
    set_adj(({"squirrel", "squirrel"}));
    set_long("This is a bowl of squirrel stew. It's a rich broth of with chopped carrots, potatoes, and chunks of squirrel meat. The stew looks filling and delicious.\n");
    set_amount(200);
}
