
inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
    set_soft_amount(150);
    set_alco_amount(25);    // nominal value 73 cc
    set_name("juice");
    add_name("gloomjuice");
    add_name("cup");
    set_adj("gloom");
    add_adj("cup of");

    set_short("cup of Gloomjuice");
    set_pshort("cups of Gloomjuice");

    set_long("The drink is cloudy with a drab grey colour. Looking into " +
        "the cup you feel yourself getting depressed.\n");
   
    add_prop(OBJ_I_WEIGHT, 180);
    add_prop(OBJ_I_VOLUME, 150);
}

void
special_effect(int numofdrinks)
{
    write("You down the Gloomjuice, and a black cloud of depression settles " +
        "over you.\n");
}
