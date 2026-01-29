/* Soneshaft ale by Twire */

inherit "/std/drink"
#include <stdproperties.h>
create_drink()
{
    set_name("ale");
    set_short("Stoneshaft ale")
    set_adj("Stoneshaft);
    set_long("An ale brewed by the Stoneshaft dwarves.\n");
    set_soft_amount(330);
    set_alco_amount(16);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}