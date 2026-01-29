inherit "/std/drink";
#include "/sys/stdproperties.h"


/*
 * Function name: create_drink()
 * Description  : Constructor.  Creates the drink.
 */
create_drink()
{
    set_soft_amount(200);
    set_alco_amount(20);
    set_name("grog");
    set_adj("jugular");
    add_adj("vein");
    set_short("jugular vein grog");
    set_pshort("jugular vein grogs");
    set_long("This is a Jugular Vein grog, a favourite of the "
    +"thieves and assassins of Faerun. The taste isn't much, but it "
    +"promises to knock you on your tail.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}
