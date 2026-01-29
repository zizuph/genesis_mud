/*
 * /d/Gondor/guilds/rangers/obj/cloak_lpocket.c
 *
 * This is the left pocket sewn into the inside of the mottled cloak
 * -- Finwe, February 2005
 */
#pragma save_binary
#pragma strict_types

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

inherit "/std/container";
inherit "/d/Gondor/guilds/rangers/rack_list";
inherit "/lib/shop";

public void show_list(object for_obj, object *obarr);

void
create_container()
{
    ::create_container();

    setuid(); 
    seteuid(getuid());

    set_name("left pocket");
    add_name("pocket");

    set_short("left pocket");
    set_long("This is the left pocket sewn into the cloak. It can hold " +
        "items that the wearer does not want lost.\n");

    add_prop(CONT_I_WEIGHT, 300);
    add_prop(CONT_I_VOLUME, 2200);
    add_prop(CONT_I_MAX_WEIGHT, 3000);
    add_prop(CONT_I_MAX_VOLUME, 3000);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(OBJ_I_NO_GET, 1); 
//    add_prop(CONT_I_TRANSP, 0);
    add_prop(CONT_I_CLOSED, 0); 
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
            for_obj->catch_tell("There is nothing in the " + 
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
