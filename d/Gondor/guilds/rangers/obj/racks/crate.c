/*
 *      /d/Gondor/guilds/rangers/obj/crate.c
 *
 *      Opus, July 1997
 *
 *      Copyright (c) 1997 by Robert Miller
 *
 *      Note: This was written using /d/Gondor/common/guild/obj/rack.c
 *            as an example.
 * 
 *      Modified by Gwyneth, 3/24/02, to add support for recording. See
 *      w_rack.c for more details.
 *
 *      Modified by Gorboth, Sept. 2012. Increased capacity to other guild
 *                                       standards.
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

#include "../../rangers.h"
#include "/d/Gondor/defs.h"

#pragma no_clone

object gWepRack;

int check_glow_rack();
public void show_list(object for_obj, object *obarr);

public void
create_container()
{
    set_short("vast wooden crate");
    set_name("crate");

    /* Must have this name for listing reference. Do not remove. */
    add_name("non_glowing_crate");

    set_adj("wooden");
    add_adj( ({ "vast" }) );
    set_long("This large crate is made of sturdy oak. Nicks and scratches "
        + "can be seen from where Rangers have hastily thrown in "
        + "miscellaneous items. It is unbelievably huge.\n");

    add_prop(OBJ_M_NO_GET, "The crate is too heavy. All you manage to do " +
         "is hurt your back.\n");
    add_prop(CONT_I_MAX_VOLUME, 5000000);
    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_VOLUME,     500000);
    add_prop(CONT_I_WEIGHT,     500000);
    add_prop(CONT_I_RIGID,      1);
    add_prop(CONT_I_TRANSP,     0);
    add_prop(CONT_I_CLOSED,     0);
    add_prop(CONT_I_REDUCE_WEIGHT, 100);
    add_prop(CONT_I_REDUCE_VOLUME, 100);

    set_alarm(0.1, 0.0, &check_glow_rack());

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
 * Function name: check_glow_rack
 * Description  : Make sure the rack with the sorting code is
 *                present and set it to gWepRack global variable.
 */
int
check_glow_rack()
{
    if (!objectp(gWepRack))
        gWepRack = present("glowing_rack", environment(this_object()));

    if (!objectp(gWepRack))
        return 0;
    else
        return 1;
}

/*
 * Function name: enter_inv
 * Description  : Mask enter_inv to keep track of items put in.
 * Arguments    : object ob - the object entering
 *                object from - where it came from
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (from != this_object())
    {
        add_rack_entry(ob);
    }

    if (!interactive(from))
        return;

    if (query_verb() == "return")
        return;

    if (!check_glow_rack())
    {
        from->catch_tell("Something went wrong! Please bug report.\n");
        return;
    }

    gWepRack->enter_racks(ob, from->query_real_name());
    return;
}
/*
 * Function name: leave_inv
 * Description  : Mask leave_inv to keep track of items taken out.
 * Arguments    : object ob - the object leaving
 *                object from - where it's going to
 */
void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (to != this_object() && objectp(to))
    {
        remove_rack_entry(ob);
    }

    if (!interactive(to))
        return;

    if (!check_glow_rack())
    {
        to->catch_tell("Something went wrong! Please bug report.\n");
        return;
    }

    gWepRack->leave_racks(ob, to);
    return;

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
