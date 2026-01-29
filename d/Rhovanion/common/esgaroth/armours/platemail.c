inherit "/d/Rhovanion/common/esgaroth/armours/genericarmour";

#include <wa_types.h>

create_armour()
{
    set_name("platemail");
    set_adj("dragon");
    set_long("This looks like a piece of dragonscale that has been forged " +
        "into armour.  It was probably handed down for generations after " +
        "being obtained from one of the dragons rumoured to have haunted " +
        "Esgaroth in times past.\n");
    set_at(A_BODY);
    set_ac(18);
}
