inherit "/d/Rhovanion/common/esgaroth/armours/genericarmour";

#include <wa_types.h>

create_armour()
{
    set_name("boots");
    set_pname("boots");
    set_adj("high");
    set_long("These are boots designed for walking through all kinds of " +
        "terrain.  They are made of leather, and sealed to keep water out.\n");
    set_at(A_FEET);
    set_ac(11);
}
