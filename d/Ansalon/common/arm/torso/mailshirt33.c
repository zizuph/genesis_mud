inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("shirt");
    add_name("mail");
    add_name("chainmail");
    set_adj("mail");
    add_adj("chainmail");
    set_short("chainmail shirt");
    
    set_ac(33);
    set_at(A_TORSO);
    
    set_long("The shirt is made of chainmail with strips of metal woven " +
        "through the links. A layer of cloth is fastened on the inside " +
        "of the shirt.\n");

    add_prop(OBJ_I_VOLUME, 2500);
}
