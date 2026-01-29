/* Holiday wreath of ivy worn on head
 * June 1999 by Finwe
 */

#pragma save_binary

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";


#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <wa_types.h>
#include "/d/Shire/sys/defs.h"

// Global Vars

void
create_object()
{
    set_name("wreath");
    add_adj(({"delicate" ,"festive"}));
    add_name("_shire_ivy_wreath_");
    set_short("delicate festive wreath");
    set_long("This is wreath of ivy. It is a made up of many ivy " +
        "sprigs, delicately woven together. It forms a crown that " +
        "can be worn on the head. Some believe ivy to be symbolic " +
        "of merriment and drinking, hence its holiday popularity.\n");

    add_item(({"ivy", "sprigs of ivy", "ivy sprigs"}),
        "The ivy sprigs are long and flexible. They are woven " +
        "together to form a crown that can be worn on the head. " +
        "The ivy is fresh and green.\n");

    /* The wreath can be worn on the head only*/
    set_slots(A_BROW);

    /* We won't make the wreath take up any space on the head.
     */
    set_layers(0);

    /* We allow layers to be worn under the head */
    set_looseness(2);

    set_keep(1); 

    add_prop(OBJ_I_WEIGHT,  20);
    add_prop(OBJ_I_VOLUME,  50);
}


/*
 * We need to override leave_env() so that we can be sure to remove
 * the anklet if it gets moved from the wearer while it is still worn.
 */
public void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    wearable_item_leave_env(env, to);
}

/*
 * We need to override appraise_object() so that we can be sure that the
 * player can appraise it properly.
 */
void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}


void
enter_env(object inv,object from)
{
    ::enter_inv(inv,from);

    if (!interactive(inv))
	return;
}

/*
 * Function name: show_subloc
 * Description  : Shows the specific sublocation description for a living.
 * Arguments    : string subloc  - the subloc to display.
 *                object on      - the object to which the subloc is linked.
 *                object for_obj - the object that wants to see the subloc.
 * Returns      : string - the subloc description.
 */
public string
show_subloc(string subloc, object on, object for_obj)
{

    if (subloc != file_name(this_object()))
    {
	return "";
    }

    if (for_obj != on)
    {
        return (capitalize(on->query_pronoun()) + " is wearing " +
            "a "+short()+" on "+HIS_HER(TP) + 
            " brow.\n");
    }
    else
    {
        return "You are wearing the " + short()+" on " +
            "your brow.\n";
    }
}
