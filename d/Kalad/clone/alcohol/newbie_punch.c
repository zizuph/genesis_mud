inherit "/std/drink";
#include "/d/Kalad/defs.h"

create_drink()
{
    set_name("newbie punch");
    add_name("punch");
    add_name("cup of punch");
    add_name("cup of newbie punch");
    add_name("small cup of newbie punch");
    add_name("very small cup of newbie punch");
    add_name("small cup of punch");
    add_name("very small cup of punch");


    set_short("cup of Newbie Punch");
    set_long(BS("This is weak stuff - good for those with "+
      "low tolerances.\n"));

    set_soft_amount(140);   /* very small cup - 5 ounces */
    set_alco_amount(4);   /* 3% alcohol */
    add_prop(OBJ_I_WEIGHT,140);
    add_prop(OBJ_I_VOLUME,140);

    /* suggested price: 12cc */
}
