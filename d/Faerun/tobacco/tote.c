/*
 * A tote to carry tobacco
 * Finwe, May 2006
 */

inherit "/d/Faerun/obj/backpack";
inherit "/d/Faerun/lib/box_list";
inherit "/lib/shop";
inherit "/lib/keep";

#include "/d/Faerun/defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include <wa_types.h>

#define PURSE_I_WEAR    "_tote_i_wear"
#define PACK_ID         "_faerun_tobacco_tote_"
#define BAG_NAME        "tote"

int purse_worn = 0;   /* 0 = not worn, 1 = worn */

void
create_container()
{
    setuid();
    seteuid(getuid());

    set_name(BAG_NAME);
    add_name(PACK_ID);
    set_adj("leather");
    set_short("supple tanned " + BAG_NAME );
    set_long("@@long_func@@");
    set_slots(A_R_SHOULDER);

    add_prop(OBJ_I_VALUE, 100+random(150));
    add_prop(CONT_I_WEIGHT, 7000);
    add_prop(CONT_I_VOLUME, 7000);
    add_prop(CONT_I_MAX_WEIGHT, 100000);
    add_prop(CONT_I_MAX_VOLUME, 100000);
    add_prop(CONT_I_CLOSED, 1);
    set_looseness(15);
    set_layers(0);    
    set_fill_verb("fill" + BAG_NAME);
    set_empty_verb("empty" + BAG_NAME);

}

/*


/* Function name: short_func
 * Description  : Returns a string for the short description depending
 *                on whether or not there are herbs in the pouch.
 * Returns      : string description
 */
string
short_func()
{
//    if (sizeof(all_inventory(TO)))
//        return "leather purse containing some coins";

    return short();
}

/* Function name: long_func
 * Description  : Returns a string for the long description depending
 *                on whether or not the pouch is tied to your belt.
 * Returns      : string description
 */
public string
long_func()
{
    string long_desc = "This is a " + short() + ". It is made from tanned deer leather and is soft. The " + BAG_NAME + " looks like it can hold quite a bit of tobacco.";

    if (query_prop(OBJ_M_NO_SELL))
        long_desc += " The " + short() + " is protected " +
        "from being sold. You may remove this protection by doing <unkeep " + BAG_NAME + ">.";
    else
        long_desc += " You may protect this from being sold by doing " +
        "<keep " + BAG_NAME + ">. This does not protect it from being stolen. You " +
        "will have to wear the " + short() + " to protect it from thieves.";
    return (long_desc + "\n");
}

/* Function name: prevent_enter
 * Description  : Checks if it is tobacco
 * Arguments    : object obj - the object entering
 * Returns      : 1 not tobacco, 0 is tobacco
 */
public int
prevent_enter(object obj)
{
    if (!obj->query_is_tobacco())
    {
        write("You can only put tobacco and pipeweed in the " + query_name() + ".\n");
        return 1;
    }
    return 0;
}
