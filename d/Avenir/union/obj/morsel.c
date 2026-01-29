#pragma strict_types
inherit "/std/food";
#include <macros.h>


public void
special_effect(int amnt)
{
    write("This delightful little morsel tastes uniquely of "+
	"elderberries. Its sweetness is cut by the almond-"+
	"flavour of the marzipan.\n");
    say(QCTNAME(this_player()) +" enjoys "+ short() +".\n");
}

public void
create_food(void)
{
    set_amount(10);
    set_name("morsel");
    add_name(({"food", "treat", "dessert", "delicacy"}));
    set_pname(({"morsels",}));
    set_short("elderberry morsel");
    set_pshort("elderberry morsels");
    add_adj(({"bite-sized", "tiny", "elderberry" }));
    set_long("This little morsel is made of layers of elderberry "+
	"jelly and marzipan baked on a thin pastry crust. For a "+
	"finishing touch, honey made from elderberry flowers "+ 
	"has been drizzled over the top.\n");
}
