/* Goodlund red wine for Kendermore, Gwyneth, June 1999 */

inherit "/std/drink";
#include <stdproperties.h>

void
create_drink()
{
    set_soft_amount(180);
    set_alco_amount(20);
    set_name("wine");
    set_pname("wines");
    set_adj("goodlund");
    add_adj("red");
    set_short("Goodlund red wine");
    set_pshort("Goodlund red wines");
    set_long("This wine is a beautiful deep red, with the colour tapering " +
             "to a light brick red around the rim of the glass.  This and " +
             "the mouth-watering scent of the wine convince you that " +
             "Goodlund must produce the finest wines of Krynn, and that " +
             "this glass must be from an excellent vintage, aged to its " + 
             "peak.\n");
    add_prop(OBJ_I_WEIGHT, 180);
    add_prop(OBJ_I_VOLUME, 180);
}
    
