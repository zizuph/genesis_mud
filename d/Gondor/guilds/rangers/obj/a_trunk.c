/*
 *  /d/Gondor/guilds/rangers/obj/a_trunk.c
 *
 *  An arrow trunk for the armories
 *
 *  Based on the wracks originally coded by Elessar
 *  by Finwe, February 2005
 */

#pragma strict_types

inherit "/std/container";
inherit "/d/Gondor/guilds/rangers/rack_list";
inherit "/lib/shop";

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
#include "../rangers.h"

static string 
    f_categ,
    endlin = "+-------------------------------------------------+\n",
    blklin = "|                                                 |\n",
    toplin = "|                    Arrows                       |\n",
    reglin = "| %-=30s                  |\n";



//object  gWepRack;

//int check_glow_rack();
public void show_list(object for_obj, object *obarr);

public void
create_container()
{
    set_short("arrow trunk");
    set_name("trunk");
    add_name("arrow trunk");

    set_adj("trunk");
    set_long("This is a iron large trunk. It sits alongside the racks and " +
    "is designed to hold arrows that rangers have gathered from their travels.\n\n");

    add_prop(OBJ_M_NO_GET, "It is too heavy, you cannot take it.\n");
     add_prop(CONT_I_MAX_VOLUME, 400000);
     add_prop(CONT_I_MAX_WEIGHT, 800000);
    add_prop(CONT_I_VOLUME,  5000);
    add_prop(CONT_I_WEIGHT, 25000);
    add_prop(CONT_I_RIGID,     1);
    add_prop(CONT_I_TRANSP,    0);
    add_prop(CONT_I_CLOSED,    0);

//    set_alarm(0.1, 0.0, &check_glow_rack());
}

public int
prevent_enter(object obj)
{
    if(!function_exists("create_arrow", obj))
    {
        write("Only arrows may be put in the " + short() + ".\n");
        return 1;
    }

    return 0;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    return;
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    return;

}

public string
print_shop_list(mixed *list)
{
    string ret;
    int i, j;
    i = sizeof(list);
    if (!i)
    {
        return "";
    }
    ret = endlin + toplin + endlin;
    prev_categ = "";
    for (j = 0; j < i; j++)
        ret += print_item(list[j]);
    ret += endlin;
    return ret;
}



/*
 * Function name: print_item
 * Description:   Format a listing of *ob
 * Arguments:     *ob - an array of identical objects
 * Returns:       A string describing the objects, for use in listing
 */
 
public string
print_item(object *ob)
{
    string ret = "", categ, short_descr;
    int qty, price, start_pt;

    ob -= ({ 0 });

//    prev_categ = categ;
    ret += sprintf(reglin, extract(ob[0]->short(), 0));

    return ret;
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
                (sizeof(obarr) > 1 ? " are" : " is") + " in the " +
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
