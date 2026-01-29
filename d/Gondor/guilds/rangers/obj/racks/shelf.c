/*
 *      /d/Gondor/guilds/rangers/obj/shelf.c
 *
 *      Alto, 29 June 2001
 *
 *      Note: This was written using /d/Gondor/common/guild/obj/rack.c
 *            as an example.
 *      Altered to allow sorting
 *
 * ?   , 15 February 2005: previous update?
 * Lavellan, 29 October 2010: changed to use new saving rack system
 *
 */
inherit "/std/container";
inherit "/d/Gondor/guilds/rangers/rack_list";
inherit "/lib/shop";
inherit "/d/Genesis/specials/lib/item_recovery_lib";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#pragma no_clone

public void show_list(object for_obj, object *obarr);

public void
create_container()
{
    set_short("large shelf");
    set_name("shelf");

    /* Do not remove. This is needed for sorting purposes! */
    add_name("potion_shelf");

    set_adj("large");
    set_long( "This large shelf is made of sturdy oak. It is used primarily "
       + "for the storage of items not appropriate for the racks.\n");

    add_prop(OBJ_M_NO_GET, "The shelf is mounted firmly on the wall.\n");
     add_prop(CONT_I_MAX_VOLUME, 400000);
     add_prop(CONT_I_MAX_WEIGHT, 800000);
    add_prop(CONT_I_VOLUME,     5000);
    add_prop(CONT_I_WEIGHT,     25000);
    add_prop(CONT_I_ATTACH,     1);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     0);
    add_prop(CONT_I_CLOSED,     0);

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

    obarr = FILTER_DEAD(obarr);
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

    if (to == this_object() || !objectp(to))
    {
        return;
    }

    remove_rack_entry(ob);
}