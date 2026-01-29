/* a smoked herring */

inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("herring");
    add_name("fish");
    set_adj("barbecued");
    set_short("barbecued herring");
    set_pshort("barbecued herrings");
    set_long("The herring smells wonderful, as all food in Roke.\n");
    add_prop(OBJ_I_WEIGHT, 64);
    add_prop(OBJ_I_VOLUME, 80);
    set_amount(50);
}

/* 50 g => 5 + (50*50 / 600) = 10 cc (approx.)
