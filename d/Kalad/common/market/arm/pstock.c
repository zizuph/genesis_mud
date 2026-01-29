inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* A Sarr Industries production */
void
create_armour()
{
    ::create_armour();
    set_name("stockings");
    set_pname("stockings");
    set_adj("black");
    add_adj("silk");
    set_short("pair of black silk stockings");
    set_long(
     "These are black silk stockings that feel very sexy to the touch. You\n"+
     "see that they are also attacked to a garter belt.\n");
    set_ac(1);
    set_at(A_LEGS);
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,15);
    add_prop(OBJ_I_VALUE,8);
}

