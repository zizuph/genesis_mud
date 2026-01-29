inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("dress");
    set_adj("shimmering");
    add_adj("white");
    set_short("shimmering white dress");
    set_long("The dress is made of white silk and satin, and feels very "+
    "smooth to the touch. It is covered with glittering little white "+
    "scales, that seem to made of mother-of-pearl. It makes the whole "+
    "dress glow with a strange light.\n");
    set_ac(2);
    set_at(A_ROBE);
    add_prop(OBJ_I_WEIGHT,400);
    add_prop(OBJ_I_VOLUME,300);
    add_prop(OBJ_I_VALUE,900);
}

