inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
void
create_armour()
{
    ::create_armour();
    set_name("dress");
    set_adj("sleazy");
    add_adj("revealing");
    set_long(
     "This dress is black and silky. It barely covers your bottom, and it\n"+
     "leaves a rather large open space around the breast area, showing\n"+
     "more cleavage than you might want to show.\n");
    set_ac(1);
    set_at(A_BODY);
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE,10);
}

