/*
 * A bag with oats in it, sold in Bree tack shop.
 * Snarfed from Finwe by Palmer Jan 2003
 * Finwe, September 2002
 */

inherit "/std/receptacle";
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

#define BREE_STABLES_DIR "/d/Shire/bree/rooms/town/stable/"

void
create_receptacle()
{
    setuid(); seteuid(getuid());

    set_name("bag of oats");
    add_name("bag");
    set_pname("bags of oats");
    add_pname("bags");
    set_adj( ({"thin","leather" }) );
    set_short("bag of oats");
    set_pshort("bags of oats");
    set_long("This is a brown leather bag, made for holding oats.\n");
    clone_object(BREE_STABLES_DIR + "obj/oats")->move(this_object(), 1);
    clone_object(BREE_STABLES_DIR + "obj/oats")->move(this_object(), 1);
    clone_object(BREE_STABLES_DIR + "obj/oats")->move(this_object(), 1);
    clone_object(BREE_STABLES_DIR + "obj/oats")->move(this_object(), 1);
    clone_object(BREE_STABLES_DIR + "obj/oats")->move(this_object(), 1);
    clone_object(BREE_STABLES_DIR + "obj/oats")->move(this_object(), 1);
    clone_object(BREE_STABLES_DIR + "obj/oats")->move(this_object(), 1);
    clone_object(BREE_STABLES_DIR + "obj/oats")->move(this_object(), 1);
    clone_object(BREE_STABLES_DIR + "obj/oats")->move(this_object(), 1);
    clone_object(BREE_STABLES_DIR + "obj/oats")->move(this_object(), 1);
    clone_object(BREE_STABLES_DIR + "obj/oats")->move(this_object(), 1);
    clone_object(BREE_STABLES_DIR + "obj/oats")->move(this_object(), 1);

    add_prop(CONT_I_WEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 117);
    add_prop(CONT_I_RIGID, 1);            /* It is a rigid object   */
    add_prop(OBJ_M_NO_SELL,"@@no_sell");
    add_prop(OBJ_I_VALUE, 30);
    add_prop(CONT_I_CLOSED,1);      /* starts closed */

}


mixed
no_sell()
{
  if(sizeof(all_inventory(this_object())))
    return "The "+short()+" still has something in it.\n";
  return 0;
}
