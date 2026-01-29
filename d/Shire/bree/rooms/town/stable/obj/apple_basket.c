/*
 * A basket with apples in it, sold in Bree tack shop.
 * Snarfed from Finwe by Palmer Jan 2003
 * Finwe, September 2002
 */

inherit "/std/receptacle";
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

#define FOOD  "/d/Shire/bree/food/"

//void reset_chest();

void
create_receptacle()
{
    setuid(); seteuid(getuid());

    set_name("basket");
    set_pname("basket of apples");
    add_pname("baskets");
    set_adj( ({"sturdy","wooden" }) );
    set_short("wooden basket");
    set_pshort("baskets");
    set_long("This is a brown basket. It is made of braided, " +
        "flexible, wooden strips of wood.\n");
    clone_object(FOOD + "apple")->move(this_object(), 1);
    clone_object(FOOD + "apple")->move(this_object(), 1);
    clone_object(FOOD + "apple")->move(this_object(), 1);
    clone_object(FOOD + "apple")->move(this_object(), 1);
    clone_object(FOOD + "apple")->move(this_object(), 1);
    clone_object(FOOD + "apple")->move(this_object(), 1);
    clone_object(FOOD + "apple")->move(this_object(), 1);
    clone_object(FOOD + "apple")->move(this_object(), 1);
    clone_object(FOOD + "apple")->move(this_object(), 1);
    clone_object(FOOD + "apple")->move(this_object(), 1);
    clone_object(FOOD + "apple")->move(this_object(), 1);
    clone_object(FOOD + "apple")->move(this_object(), 1);

    add_prop(CONT_I_WEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 8000);
    add_prop(CONT_I_RIGID, 1);            /* It is a rigid object   */
    add_prop(OBJ_M_NO_SELL,"@@no_sell");
    add_prop(OBJ_I_VALUE, 150);
    add_prop(CONT_I_CLOSED,1);      /* starts closed */

}


mixed
no_sell()
{
  if(sizeof(all_inventory(this_object())))
    return "The "+short()+" still has something in it.\n";
  return 0;
}
