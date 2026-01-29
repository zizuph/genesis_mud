
inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_soft_amount(150);
    set_alco_amount(20);    // nominal value 50 cc
    set_name("squire");
    add_name("glass");
    set_adj("bloody");
   
    set_short("glass of Bloody Squire");
    set_pshort("glasses of Bloody Squire");
    set_long("It is a glass of opaque, blood-red liquid. It smells faintly " +
        "of tomatoes.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}

