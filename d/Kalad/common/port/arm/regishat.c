inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("hat");
    set_adj("fancy");
    add_adj("plumed");
    set_long("A large sized hat that has been colorfully decorated with "+
      "a variety of exotic feathers.\n");
    set_ac(10);
    set_am(({-5,-5,5}));
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE,400);
    add_prop(OBJ_I_VOLUME,800);
    add_prop(OBJ_I_WEIGHT,800);
}
