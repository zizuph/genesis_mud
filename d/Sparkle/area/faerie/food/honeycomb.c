/* A piece of honeycomb for honey quest in Faerie
 * Finwe, May 2005
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

 
create_food()
{
    set_name("honeycomb");
    add_name("honey");
    set_pname("honeycombs");
    set_short("comb of golden honey");
    set_pshort("combs of golden honey");
    set_adj("comb");
    set_long("This is a comb of golden honey. It is fresh and recently " +
        "cut from a beehive.\n");
    set_amount(200);
}
