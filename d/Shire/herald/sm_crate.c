/*
 * Crate to hold forging stuff in Forge
 * Finwe, July 2001
 * 
 * Rhyn coded improved listing of containers. 
 * Thanks Rhyn!!
 * Added improved listing
 * Finwe, May 2001
 */


inherit "/std/receptacle";
inherit "/d/Emerald/lib/shop_list";
inherit "/lib/shop";

#include "/d/Shire/sys/defs.h"
#include "smiths.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <money.h>
#include <filter_funs.h>

public void show_list(object for_obj, object *obarr);


public void
create_container()
{
    set_short("large steel box");
    set_name("box");
    set_adj("steel");
    set_long("This is a "+short()+" for Smiths to drop " +
        "items they have forged and forging supplies.\n");

    add_prop(OBJ_M_NO_GET, "The "+short()+"is too heavy to take.\n");
    add_prop(CONT_I_MAX_VOLUME, 500000);
    add_prop(CONT_I_MAX_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME,  50000);
    add_prop(CONT_I_WEIGHT, 30000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);

}

 
public void
init()
{
    ::init();

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

/*
int
access_crate(string str) 
{
    seteuid(getuid());
    if (TP->query_wiz_level())
        return 0;

    if (IS_MEMBER(TP))
        return 0;

    TP->catch_tell("Only Smiths may access the "+short()+".\n");
    return 1;
}
*/

public int
do_default_open(string str)
{

    if(str == "box" || str == "large steel box" || str == "steel box")
    {
	if(!IS_MEMBER(TP) && !TP->query_wiz_level())
	{
	    write("Only Smiths may close the large steel box.\n");
	    return 1;
	}

    }
    ::do_default_open(str);

    return 1;
}
