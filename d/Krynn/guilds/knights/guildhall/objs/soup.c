/* modified by Teth, Dec 6 1996 */
inherit "/std/food";
#include "../../local.h"

public void
create_food()
{
    set_name("soup");
    add_name("food");
    set_pname("soups");
    add_pname("foods");
    set_adj(({"steaming","Palanthian"}));
    add_adj("palanthian");
    set_short("steaming Palanthian soup");
    set_pshort("steaming Palanthian soups");
    set_long("This soup is made from a Palanthian recipe, " +
        "a concoction made with fresh vegetables and herbs. " +
        "It is best eaten while still steaming.\n");
    set_amount(182);
}

