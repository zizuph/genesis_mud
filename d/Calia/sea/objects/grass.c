
 /* A long blade of black grass for sale in Thalassia */

#include "defs.h"
inherit FRUIT;

void
create_fruit()
{
    set_name("grass");
    set_short("long blade of black grass");
    set_pshort("long blades of black grass");
    set_adj(({"long","black"}));
    set_long("This is a rather long blade of grass, black in "+
        "colour. It is about eight inches long, and about one inch "+
        "wide at the bottom, tapering to about one eighth of an inch "+
        "at the top. It smells delicious, and you can hardly wait "+
        "to eat it. ");
    set_fruit_amount(0);
    set_mana_add(0);
    set_hp_add(20);
    set_fatigue_add(0);
}
