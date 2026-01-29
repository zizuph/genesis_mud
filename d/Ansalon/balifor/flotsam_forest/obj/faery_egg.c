inherit "/std/food";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

create_food()
{
    set_name("egg");
    add_name("_fairy_dragon_egg");
    set_adj("faery");
    add_adj("dragon");
    set_short("faery dragon egg");
    set_long("This egg is about the size of an ostriches egg, "+
      "but is speckled in colours "+
      "ranging from bright purple to dark green.\n");
    set_amount(212);
}


public void
special_effect(int amnt)
{

    TP->catch_msg("You feel mentally strengthened "+
      "after eating the faery dragon egg.\n");
    TP->add_mana(200);

    if(P("faery_dust",TP))
    {
	P("faery_dust",TP)->remove_object();
    }
}
