/* Modified by Teth, for new VK, Dec 6 1996 */
inherit "/std/food";
#include "../local.h"

public void
create_food()
{
    set_name("steak");
    add_name("food");
    set_adj("venison");
    set_pname("steaks");
    add_pname("foods");
    set_short("venison steak");
    set_pshort("venison steaks");
    set_long("This steak is the result of some fortunate hunting " +
        "on the plains and forests in Solamnia. Solamnian deer " +
        "are known for their rich game flavour, and are thus " +
        "sought out for food. This steak appears delicious.\n");
    set_amount(357);
}

