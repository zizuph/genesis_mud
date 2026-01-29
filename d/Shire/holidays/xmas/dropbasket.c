/*
 * A square basket with cookies for the holidays
 * Finwe, December 2002
 */

inherit "/std/receptacle";

#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

void
create_receptacle()
{
    int i;

    setuid(); seteuid(getuid());

    set_name("basket");
    add_name("round basket");
    set_pname("round baskets");
    add_pname("baskets");
    set_adj( ({"round", "wooden" }) );
    set_short("round wooden basket");
    set_pshort("round wooden baskets");
    set_long("This is a round wooden basket. It is made of braided, " +
        "flexible, wooden strips of wood. The basket is plain and round shaped.\n");

    clone_object("/d/Shire/holidays/xmas/droppings")->move(this_object(), 1);

    add_prop(CONT_I_WEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 117); 	
    add_prop(CONT_I_RIGID, 1);            /* It is a rigid object   */
    add_prop(OBJ_M_NO_SELL,"@@no_sell");
    add_prop(OBJ_I_VALUE, 150);
    add_prop(CONT_I_CLOSED,0);      /* starts closed */

}


mixed
no_sell()
{
  if(sizeof(all_inventory(this_object())))
    return "The "+short()+" still has something in it.\n";
  return 0;
}
