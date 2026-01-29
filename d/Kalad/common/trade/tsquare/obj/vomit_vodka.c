inherit "/std/drink";
#include "/d/Kalad/defs.h"

create_drink()
{
    set_name("vomit vodka");
    add_name("vodka");
    add_name("shot of vodka");
    add_name("shot of vomit vodka");

    set_short("shot of Vomit Vodka");
    set_long(BS("This is some of the strongest liquor you've ever had. "+
      "It tastes vile and smells like it's namesake. The label reads:\n"+
      "Vomit Vodka - We always do!\n"));

    set_soft_amount(50);   /* shot */
    set_alco_amount(50);   /* 100% alcohol */
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,50);
    add_prop(OBJ_I_VALUE,150);
    /* suggested price: 150cc */
}
