inherit "/d/Rhovanion/common/esgaroth/armours/genericarmour";

#include <wa_types.h>

create_armour()
{
    set_name("shield");
    set_adj("turtleshell");
    set_long("This shield is made from the shell of a turtle caught in " +
        "water near Esgaroth.\n");
    set_at(A_SHIELD);
    set_ac(19);
}
