inherit "/std/drink";
#include "/d/Kalad/defs.h"

create_drink()
{
    set_name("pint of stout");
    add_name("triple stout");
    add_name("pint of triple stout");
    add_name("pint of hellish hobbit");
    add_name("pint of hellish hobbit triple stout");
    add_name("hellish hobbit stout");
    add_name("pint of hellish hobbit stout");

    set_short("pint of triple stout");
    add_name("stout");
    add_name("hellish hobbit");
    add_name("hellish hobbit triple stout");

    set_long("It is incredibly thick and dark. The label reads:\n"+
      "     Hellish Hobbit\n"+
      "    Triple xxx Stout\n"+
      "Put Some Hair On Your Toes!\n");

    set_soft_amount(453);   /* 1 pint */
    set_alco_amount(32);   /* 7% alcohol */
    add_prop(OBJ_I_WEIGHT,453);
    add_prop(OBJ_I_VOLUME,453);
    add_prop(OBJ_I_VALUE,96);
    /* suggested price: 96cc */
}
