inherit "/std/object";
inherit "/lib/wearable_item";

#include "../local.h"
#include <cmdparse.h>
#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

public void 
create_object()
{
    set_name(({"club", "brooch", "_club_sup_guru_"}));
    set_adj(({"silver", "small"}));
    set_short("small silver club");
    set_long("This is a nice silver brooch in the shape of a club. It has " +
        "a silver handle two inches long with a pin attached to it so you " +
        "can wear it on your clothes. At the end of the handle is a silver " +
        "chain with a small spiked silver ball so the whole brooch looks " +
        "like a morning-star. When you move, the ball swings on the chain " +
        "and gives a nice lively effect.\n");

    add_prop(OBJ_I_VOLUME,  23);
    add_prop(OBJ_I_WEIGHT,  57);
    add_prop(OBJ_I_VALUE,   100000);
    add_prop(OBJ_M_NO_SELL, "No! This brooch is so nice that you would " +
        "rather starve to death than sell it!\n");
    add_prop(OBJ_M_NO_DROP, "No! You would never give such a beauty out of " +
        "your hands!\n");

    set_slots(A_CHEST);
    set_layers(1);
    set_looseness(20);
    wear_func = this_object();
}

/*
 * Function name: wear
 * Description  : This function is called when someone tries to wear
 *                this item. 
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int  0 - The item can be worn normally.
 *                     1 - The item can be worn, but print no messages.
 *                    -1 - The item can't be worn, use default messages.
 *                string - The item can't be worn, use this message.
 */
public mixed
wear(object obj)
{
    if (wearer != environment(this_object()))
    {
        return 0;
    }

    write("You pin the " + short() + " on your chest.\n");
    say(QCTNAME(this_player()) + " pins a " + short() + " on " +
        this_player()->query_possessive() + " chest.\n");

    worn = 1;
    this_player()->add_subloc(file_name(this_object()), this_object());
    return 1;
}

/*
 * Function name: remove
 * Description  : This function is called when someone tries to remove
 *                this item.
 * Arguments    : object obj - The item to remove.
 * Returns      : int  0 - Remove the item normally.
 *                     1 - Remove the item, but print no messages.
 *                    -1 - Do not remove the item, print default message.
 *                string - Do not remove the item, use this message.
 */
public mixed
remove(object obj)
{
    if (wearer != environment(this_object()))
    {
        return 0;
    }

    write("You remove the " + short() + " from your chest.\n");
    say(QCTNAME(this_player()) + " removes a " + short() + " from " +
        this_player()->query_possessive() + " chest.\n");

    worn = 0;
    this_player()->remove_subloc(file_name(this_object()));
    return 1;
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
            "a small silver club-brooch on " + on->query_possessive() +
            " chest. The small spiked ball on the chain swings with " +
            on->query_possessive() + " every move.\n");
    }
    else
    {
        return "You are wearing the small silver club-brooch on " +
            "your chest.\n";
    }
}

/*
 * Function name: query_auto_load
 * Description  : Return the filename of this module to allow it to be
 *                autoloadable.
 * Returns      : string - the filename of this module.
 */
public string 
query_auto_load() 
{
    return MASTER + ":"; 
}

public int 
id_aa_sup_guru_club()
{ 
    return 1; 
}

/* 
 * Function name: enter_env
 * Description  : Prevents a player from carrying more than one
 *                of these items.
 * Arguments    : object dest - destination environment
 *                object old  - original environment
 */
public void
enter_env(object dest, object old)
{
    object *obs;
    int i, change, size;

    ::enter_env(dest, old);

    obs = all_inventory(dest);

    change = 0;
    for (i = 0, size = sizeof(obs); i < size; i++)
    {
	if (obs[i]->id_aa_sup_guru_club() && 
          obs[i] != this_object())
	{
	    obs[i]->remove_object();
	    change++;
	}
    }

    if (change)
    {
        dest->catch_tell("You have lost something!\n");
    }
}

/*
 * Function name: leave_env
 * Description  : When you inherit /lib/wearable_item.c into any object other
 *                than /std/armour.c you MUST also define the function
 *                leave_env() as copy of this function. It MUST make the
 *                call to wearable_item_leave_env(from, to) as well. If
 *                you omit this, then the item will not be automatically
 *                removed when the player drops it, for instance.
 *                PS: This is just a dummy function. It does not exist. You
 *                    must write your own as copy of this one.
 * Arguments    : object from - the environment we are leaving.
 *                object to   - the environment we are entering.
 */
public void
leave_env(object from, object to)
{
    wearable_item_leave_env(from, to);
    ::leave_env(from, to);
}

/*
 * Function name: appraise_object
 * Description  : When you inherit /lib/wearable_item.c into any object
 *                other than /std/armour.c you MUST also define the function
 *                appraise_object() as copy of this function. It MUST make
 *                the call to appraise_wearable_item() as well. If you omit
 *                this, then the player will not be able to appraise this
 *                item properly.
 *                PS: This is just a dummy function. It does not exist. You
 *                    must write your own as copy of this one.
 * Arguments    : int num - the semi-randomised appraise skill.
 */
public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}
