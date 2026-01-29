inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_short("pair of buskins");
    set_pshort("pairs of buskins");
    set_name(({"boots","pair","boot","buskins"}));
    set_pname(({"boots", "pairs", "pairs of buskins"}));
    set_adj(({"pair","low","leather","laced"}));
    set_long("These buskins are leather boots that lace "+
        "halfway to the knees. They are extremely comfortable "+
        "and the thick soles are well broken-in.\n");
    set_ac(30);
    set_at(A_FEET);
}

