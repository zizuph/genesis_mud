
inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_soft_amount(150);
    set_alco_amount(5);     // nominal value 13 cc
    set_name("ale");
    add_name("tankard");
    set_adj("light");
   
    set_short("tankard of light ale");
    set_pshort("tankards of light ale");
    set_long("It is a tankard of light ale, which smells delicious.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}

