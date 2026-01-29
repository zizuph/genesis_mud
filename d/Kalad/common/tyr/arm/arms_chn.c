/* arms_chn: Chitin arm plates. To protect and serve. */
inherit "/d/Kalad/std/armour";
#include <wa_types.h>
#include "defs.h"

void create_armour()
{
    ::create_armour();
    set_name("plates");
    set_short("pair of chitin arm plates");
    set_pshort("pairs of chitin arm plates");
    set_long("The huge insects of Athas can provide all sorts of superb "+
             "armour. Take for instance these fine arm plates.\n");
    set_adj("chitin");
    add_adj("arm");

    set_ac(40);
    set_am(({-1,0,1}));
    set_at(A_ARMS);

    add_prop(OBJ_I_WEIGHT, 6250);
    add_prop(OBJ_I_VOLUME, 3125);
}
