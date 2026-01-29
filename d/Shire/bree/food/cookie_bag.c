/*
 * A sack of cookies for the Prancing Pony
 * Finwe, October 2005
 */

inherit "/std/receptacle";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/bree/defs.h"
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>


//void reset_chest();

void
create_receptacle()
{
    setuid();
    seteuid(getuid());

    set_name("bag");
    set_pname("bags");
    set_adj( ({"brown", "paper" }) );
    set_short("brown paper bag");
    set_pshort("brown paper bags");
    set_long("This is a brown paper bag from the Prancing Pony in Bree. It " +
        "rectangular shaped and has creases near the top where it was " +
        "folded over. Near the bottom of the bag are square shaped " +
        "stains from food that was in it. When you are done with the bag, " +
        "you may <crumple bag> to get rid of it.\n");

    clone_object(FOOD_DIR + "cookie")->move(this_object(), 1);
    clone_object(FOOD_DIR + "cookie")->move(this_object(), 1);
    clone_object(FOOD_DIR + "cookie")->move(this_object(), 1);
    clone_object(FOOD_DIR + "cookie")->move(this_object(), 1);
    clone_object(FOOD_DIR + "cookie")->move(this_object(), 1);
    clone_object(FOOD_DIR + "cookie")->move(this_object(), 1);
    clone_object(FOOD_DIR + "cookie")->move(this_object(), 1);
    clone_object(FOOD_DIR + "cookie")->move(this_object(), 1);
    clone_object(FOOD_DIR + "cookie")->move(this_object(), 1);
    clone_object(FOOD_DIR + "cookie")->move(this_object(), 1);
    clone_object(FOOD_DIR + "cookie")->move(this_object(), 1);
    clone_object(FOOD_DIR + "cookie")->move(this_object(), 1);

    add_prop(CONT_I_WEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 117);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_SELL,"@@no_sell");
    add_prop(OBJ_I_VALUE, 150);
    add_prop(CONT_I_CLOSED,1);

}

void
init()
{
    ::init();

    add_action("do_crumple", "crumple");
}


int do_crumple(string str)
{
    if(!str || str != "bag")
    {
        write("Crumple what?\n");
        return 1;
    }
    if(sizeof(all_inventory(this_object())))
    {
        write("The "+short()+" still has something in it.\n");
        return 1;
    }
    else
    {
        write("You crumple up the " + short() + " and throw it away.\n");
        remove_object();
    }
    return 1;
}


mixed
no_sell()
{
  if(sizeof(all_inventory(this_object())))
    return "The "+short()+" still has something in it.\n";
  return 0;
}
