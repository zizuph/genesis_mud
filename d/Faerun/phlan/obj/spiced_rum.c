inherit "/std/drink";
#include "/sys/stdproperties.h"

/*
 * Function name: create_drink()
 * Description  : Constructor.  Creates the drink.
 */
create_drink()
{
    set_soft_amount(10);
    set_alco_amount(70);
    set_name("rum");
    set_adj("spiced");
    set_short("spiced rum");
    set_pshort("spiced rums");
    set_long("An aged dark rum with hints of vanilla, clove cinnamon, peppercorn"
        +" star anise, nutmeg, ginger and orange zest. It has a full sensory"
        +" appeal with a strong alcohol effect.\n");
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 80);
}
