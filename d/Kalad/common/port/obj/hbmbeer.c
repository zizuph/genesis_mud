inherit "/std/drink";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_drink()
{
    set_name("quart of stout");
    add_name("triple stout");
    add_name("quart of triple stout");
    add_name("quart of hellish halfing");
    add_name("quart of hellish halfling triple stout");
    add_name("hellish halfling stout");
    add_name("quart of hellish halfling stout");
    add_name("mug of beer");
    add_name("mug");
    add_name("beer");

    set_short("quart of triple stout");
    add_name("stout");
    add_name("quart");
    add_name("hellish halfing");
    add_name("hellish halfing triple stout");

    set_long("It is incredibly thick and dark. The label reads:\n"+
      "    Hellish Halfling\n"+
      "    Triple xxx Stout\n"+
      "Put Some Hair On Your Toes!\n");

    set_soft_amount(906); /* 1 quart */
    set_alco_amount(136);
    add_prop(OBJ_I_WEIGHT,906);
    add_prop(OBJ_I_VOLUME,906);
    add_prop(OBJ_I_VALUE,144);
}
