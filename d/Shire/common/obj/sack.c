/*
 * A simple sack
 * Improved listing added by Rhyn. Thanks Rhyn!!
 * -- Finwe, May 2001
 * Suddenly started showing value of items in sack when using Emerald code.
 * Updated sack to not do this.
 * -- Finwe, June 2008
 *
 * 2008/06/21 Last update
 * 2011/07/21 Lavellan - Added wear location.
 */

inherit "/d/Gondor/common/guild/obj/backpack";
inherit "/d/Shire/lib/box_list";
inherit "/lib/shop";
inherit "/lib/keep";
inherit "/d/Shire/common/lib/parse";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <money.h>
#include <filter_funs.h>
#include <wa_types.h>
#include "/d/Shire/common/defs.h"

public void show_list(object for_obj, object *obarr);

/*
 *  Description: Constructor.
 */
public void
create_container()
{
    set_name("sack");
    set_pname("sacks");
    set_adj( ({ "rugged","old" }) );
    set_short("old rugged sack");
    set_pshort("old rugged sacks");
    set_long("This is an old, well-used, rugged sack.\n");
    add_prop(CONT_I_WEIGHT,     1200);          /* 1.2 kg        */
    add_prop(CONT_I_VOLUME,     500);           /* Empty volume. */
    add_prop(CONT_I_MAX_VOLUME, 60*1000);       /* 60 l          */
    add_prop(CONT_I_MAX_WEIGHT, 300*1000);      /* 300 kg        */
    add_prop(CONT_I_CLOSED,     1);
    add_prop(CONT_I_RIGID,      0);
    add_prop(CONT_I_TRANSP,	0);
    add_prop(OBJ_M_NO_SELL,	"@@check_sell@@");
    add_prop(OBJ_I_VALUE,	86);
    set_slots(A_BACK);
}

mixed
check_sell()
{
    if (sizeof(all_inventory(TO)))
	return "There are things in the sack! Empty it first.\n";
    else
	return 0;
}

string
short(object for_obj)
{
    if (query_prop(CONT_I_CLOSED))
	return "closed " + ::real_short(for_obj);
    else
	return "open " + ::real_short(for_obj);
}


/*
 * Function name: describe_contents
 * Description:   Give a description of items in this container
 * Arguments:     object for_obj - To whom to give the description
 *                object *obarr  - The items to describe
 */
public void
describe_contents(object for_obj, object *obarr)
{
    for_obj->catch_tell(show_sublocs(for_obj));

    if (this_object()->query_prop(CONT_I_ATTACH))
    {
        if (sizeof(obarr) > 0)
        {
            for_obj->catch_tell(capitalize(COMPOSITE_DEAD(obarr)) + 
                (sizeof(obarr) > 1 ? " are" : " is") + " on the " +
                this_object()->short() + ".\n");
        }
        else
        {
            for_obj->catch_tell("There is nothing on the " + 
                this_object()->short() + ".\n");
        }
    }
    else if (sizeof(obarr) > 0)
    {
        show_list(for_obj, obarr);
    }
    else
    {
        for_obj->catch_tell("  " + "The " + this_object()->short() +
            " is empty.\n");
    }
}

public void
show_list(object for_obj, object *obarr)
{
    int i, price;

    //obarr = FILTER_DEAD(obarr);
    obarr = unique_array(obarr, "short", 0);
    obarr = sort_array(obarr, "sort_objects_to_list", this_object());

    for_obj->catch_tell(print_shop_list(obarr));
}
