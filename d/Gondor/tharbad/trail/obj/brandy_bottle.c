/* Alcoholic Beverage--Raymundo, dec 2018
 */
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
#include "/d/Shire/eastroad/western/local.h"
inherit "/std/drink";
#define NO_OLIVE "_i_have_no_olive"
#define DRINK EAST_R_DIR + "supplies/martini.c"
void
create_drink()
{
        set_name("bottle");
        add_name("brandy");
        add_name("drink");
        add_adj("of");
        add_adj("brandy");
        set_pname("bottles");
        
        
        set_short("bottle of brandy");
        set_pshort("bottles of brandy");
        set_long("This is a bottle of brandy. There is no label on it, so "
            + "you have no way of knowing who made it or how strong it "
            + "is. But it looks like the kind of thing a corsair would "
            + "drink. Avast!\n");
            
        
        set_soft_amount(50);
        set_alco_amount(80);
        add_prop(OBJ_I_VALUE,20);
}
