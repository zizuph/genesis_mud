inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("shirt");
    set_adj("white");
    add_adj("brocaded");
    set_long("A finely woven shirt that has been decorated with golden "+
      "images of beer mugs and halfling women. Silver lace has been sewn "+
      "onto the shirt's collar into the following words: Regis Rumblebelly.\n");
    set_ac(5);
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE, 600);
    add_prop(OBJ_I_VOLUME,900);
    add_prop(OBJ_I_WEIGHT,900);
}
