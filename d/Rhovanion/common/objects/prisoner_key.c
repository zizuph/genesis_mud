inherit "/std/key";
#include <stdproperties.h>

create_key()
{
    set_name("key");
    set_pname("keys");
    set_adj("steel");
    add_adj("small");
    set_short("small steel key");
    set_pshort("small steel keys");
    set_long("It's a small key made out of steel.\n");
    add_prop(OBJ_I_WEIGHT,5); /* 5 grams */
    add_prop(OBJ_I_VOLUME,1); /* 1 ml    */
    add_prop(OBJ_I_VALUE,5);  /* 5 cc    */

    set_key("gcave_cell_no_3");  /* Setting the id of the key. */
}

