/* Stralle @ Genesis 020721
 *
 */

#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>
#include <composite.h>

void
create_container()
{
    set_name("desk");
    set_long("The desk is large and made of dark stained oak. " +
        "A pile of scrolls lie stacked on it and beside the " +
        "piles is an inkpot and quill. ");
    
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(CONT_I_MAX_VOLUME, 5000);
    add_prop(CONT_I_MAX_WEIGHT, 3500);
    set_no_show_composite(1);
}

void
describe_contents(object for_obj, object *obarr)
{
    for_obj->catch_tell(show_sublocs(for_obj));
    
    if (sizeof(obarr) > 0)
    {
        for_obj->catch_tell("Other than that you notice " +
            COMPOSITE_DEAD(obarr) + ".\n");
    }
    else
    {
        for_obj->catch_tell("\n");
    }
}
