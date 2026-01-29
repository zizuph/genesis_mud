inherit "/std/drink";
#include "/d/Kalad/defs.h"
/* modified by Antharanos */
create_drink()
{
    set_name("pint of stout");
    add_name("triple stout");
    add_name("pint of triple stout");
    add_name("pint of hellish halfing");
    add_name("pint of hellish halfing triple stout");
    add_name("hellish halfling stout");
    add_name("pint of hellish halfing stout");

    set_short("pint of triple stout");
    add_name("stout");
    add_name("pint");
    add_name("hellish halfing");
    add_name("hellish halfing triple stout");

    set_long("It is incredibly thick and dark. The label reads:\n"+
      "    Hellish Halfling\n"+
      "    Triple xxx Stout\n"+
      "Put Some Hair On Your Toes!\n");

    set_soft_amount(453);   /* 1 pint */
    set_alco_amount(68);
    add_prop(OBJ_I_WEIGHT,453);
    add_prop(OBJ_I_VOLUME,453);
    add_prop(OBJ_I_VALUE,96);
}
