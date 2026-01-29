/* by Teth, Dec 6 1996 */
inherit "/std/drink";
#include "../local.h"

public void
create_drink()
{
    set_soft_amount(200);
    set_name("water");
    add_name("drink");
    set_adj(({"crystal","clear"}));
    set_pname("waters");
    add_pname("drinks");
    set_short("crystal clear water");
    set_pshort("crystal clear waters");
    set_long("This crystal clear water is imported from the springs " +
        "of meltwater that run off the Vingaard Mountains. " +
        "Considering the cost of shipping, only small amounts are " +
        "apportioned out.\n");
    set_drink_msg("The sweet water rolls in your mouth and soothes " +
        "you.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}

