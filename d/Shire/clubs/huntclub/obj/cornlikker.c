/* Liquor for the hunt club
 * a jug of corn Likker!  -- tomas, dec 2017
 */
#include </stdproperties.h>

inherit "/std/drink";

void
create_drink()
{
        set_name("likker");
        set_pname("likker");
        set_short("corn likker");
        set_pshort("corn likkers");
        set_adj("corn");
        set_long("A jug of corn likker. Careful now!\n");
        set_soft_amount(50);
        set_alco_amount(80);
        add_prop(OBJ_I_VALUE,200); 

}
