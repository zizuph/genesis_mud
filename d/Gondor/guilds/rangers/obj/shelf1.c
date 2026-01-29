/*
* RoI shelf in ranger treetop to hold items
* Finwe, November 2004
*/

inherit "/std/container";
inherit "/d/Shire/lib/box_list";
inherit "/lib/shop";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <money.h>
#include <filter_funs.h>

#include "/d/Gondor/defs.h"

public void show_list(object for_obj, object *obarr);


public void
create_container()
{   
    set_short("large green shelf");
    set_name("shelf");
    set_adj(({"large", "green"}));
    set_long("It is a large, green shelf, designed to hold supplies donated " +
        "to the Rangers of Ithilien and for those who patrol the area. It " +
        "is hidden in a large branch on the treetrop.\n");

    add_prop(OBJ_M_NO_GET, "The shelf cannot be taken.\n");
    add_prop(CONT_I_MAX_VOLUME, 5000000);
    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_VOLUME,  50000);
    add_prop(CONT_I_WEIGHT, 30000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_ATTACH,     1);

//    set_no_show_composite(1);


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

    obarr = FILTER_DEAD(obarr);
    obarr = unique_array(obarr, "short", 0);
    obarr = sort_array(obarr, "sort_objects_to_list", this_object());

    for_obj->catch_tell(print_shop_list(obarr));
}
