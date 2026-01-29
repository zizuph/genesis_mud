/*
 * OBSOLETE, use /d/Gondor/common/obj/herbpouch.c instead
 * Eowul, Februari 2009
 */

inherit "/d/Gondor/common/obj/herbpouch.c";

/*
inherit "/d/Gondor/common/guild/obj/backpack";
inherit "/d/Shire/common/obj/herb_pouch";
inherit "/lib/shop";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <money.h>
#include <filter_funs.h>
#include "/d/Shire/sys/defs.h"
#include <cmdparse.h>

public void show_list(object for_obj, object *obarr);

void
create_container()
{
    set_name("pouch");
    set_pname("pouches");
    set_short("small leather pouch");
    set_pshort("small leather pouches");
    set_adj("small");
    set_adj("leather");
    set_long("The small leather pouch is used to hold herbs. It is made of " +
        "leather and looks well worn.\n");

    add_prop(CONT_I_WEIGHT, 300);
    add_prop(CONT_I_VOLUME, 5000);
    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(CONT_I_MAX_VOLUME, 6000);
    add_prop(CONT_I_CLOSED,     0);

    add_prop(OBJ_I_VALUE, 48); 		/* Worth 48 cc */
//    set_keep();
//}

/*
 * Function name: describe_contents
 * Description:   Give a description of items in this container
 * Arguments:     object for_obj - To whom to give the description
 *                object *obarr  - The items to describe
 */

/*
public void
describe_contents(object for_obj, object *obarr)
{
//for_obj->catch_tell ("[describe contents]\n");

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
//for_obj->catch_tell ("[show list]\n");

    int i, price;

//for_obj->catch_tell ("[show list] filter dead\n");
    obarr = FILTER_DEAD(obarr);
//for_obj->catch_tell ("[show list] unique array\n");
    obarr = unique_array(obarr, "short", 0);
//for_obj->catch_tell ("[show list] sort array\n");
    obarr = sort_array(obarr, "sort_objects_to_list", this_object());
    // obarr = filter(obarr, query_id_herb);
//for_obj->catch_tell ("[show list] print shop list\n");
    for_obj->catch_tell(print_shop_list(obarr));
}

*/