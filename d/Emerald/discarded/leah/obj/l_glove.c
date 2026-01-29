inherit "/std/armour";

#include "../default.h"
#include <wa_types.h>

void
create_armour()
{
    set_name("glove");
    set_short("gardening glove");
    add_adj(({"left-handed", "gardening"}));
    set_long("This glove appears to be fairly worn yet it "+
       "looks like it would do it's job of protecting the hand "+
       "better than skin would.\n");
    set_ac(8);
    set_at(A_L_HAND);
}
