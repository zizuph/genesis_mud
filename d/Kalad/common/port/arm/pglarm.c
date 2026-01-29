inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("coat");
    set_adj("black");
    add_adj("leather");
    set_pname("coats");
    set_short("black leather coat");
    set_pshort("black leather coats");
    set_long("A long coat, complete with a concealing cowl, made of "+
      "a dark, shiny leather. It seems to be of good quality, though a bit "+
      "weatherworn.\n");
    set_ac(15);
    set_am(({-5,-5,5}));
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE,500);
    add_prop(OBJ_I_VOLUME,3000);
    add_prop(OBJ_I_WEIGHT,3000);
}
