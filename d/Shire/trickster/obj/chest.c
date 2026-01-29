/*
 * Box for holding donated items
 * Finwe, January 2001
 * 
 * Rhyn coded improved listing of containers. 
 * Thanks Rhyn!!
 * Added improved listing
 * Finwe, May 2001
 *
 * 2002/09/12 ? Previous update
 * 2010/11/09 Lavellan  Update for new saving rack system
 * 2010/11/08 Previous update (?)
 * 2011/07/20 Removed FILTER_DEAD (why was it there?) which hid livings inside
 * 2011/07/21 Fixed saving
 */

inherit "/std/container";
inherit "/d/Shire/lib/box_list";
inherit "/lib/shop";
inherit "/d/Genesis/specials/lib/item_recovery_lib";
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
    set_short("wooden chest");
    set_name("chest");
    set_adj("wooden");
    set_long("This is a large, rectangular chest. It is made of wood " +
        "and scratched from constant use. The chest is designed to " +
        "hold items lifted by fellow Tricksters, and for the use of " +
        "other guildmembers.\n");

    add_prop(OBJ_M_NO_GET, "The "+short()+" cannot be taken.\n");
    add_prop(CONT_I_MAX_VOLUME, 500000);
    add_prop(CONT_I_MAX_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME,  50000);
    add_prop(CONT_I_WEIGHT, 30000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);

    if (!IS_CLONE)
    {
        return;
    }

    set_enable_logging(0);
    set_enable_recovery(1);

    init_database();
    set_alarm(0.0, 0.0, &recover_objects_from_database());
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

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (from == this_object())
    {
        return;
    }

    add_rack_entry(ob);
}


public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (to == this_object())
    {
        return;
    }

    remove_rack_entry(ob);
}