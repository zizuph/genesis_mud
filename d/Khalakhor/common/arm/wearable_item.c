/*
 *  /d/Khalakhor/common/arm/wearable_item.c
 *
 *  The standard wearable_item object of khalakhor.  
 *
 *  Example usage: (see ~Khalakhor/std/examples/necklace)
 *  To create a wearable item redefine create_khalakhor_wearable_item.
 *  That's all there is to it. Remember to set the size of the item
 *  by calling set_khalakhor_wearable_item_size. For special checks
 *  when the item is worn or removed redefine wear_khalakhor_item and 
 *  remove_khalakhor_item respectively. 
 *
 *  inherit "/d/Khalakhor/common/arm/wearable_item";
 *
 *  #include "/d/Khalakhor/sys/defs.h"
 *  #include <ss_types.h>
 *  #include <stdproperties.h>
 *  #include <wa_types.h>
 *  #include <macros.h>
 *
 *  // necessary function
 *  public void
 *  create_khalakhor_wearable_item()
 *  {
 *      set_name("necklace");
 *      set_adj(({"golden", "diamond-studded"}));
 *      set_short("golden diamond-studded necklace");
 *      set_long("An expensive necklace.\n");
  *      set_slots(A_NECK);
 *      set_layers(0);
 *      set_looseness(0);
 *
 *      add_prop(OBJ_I_WEIGHT, 200);
 *      add_prop(OBJ_I_VOLUME, 100);
 *      add_prop(OBJ_I_VALUE, 1728);
 *  }
 *
 *  // optional function
 *  public mixed
 *  wear_khalakhor_item(object item)
 *  {
 *      if (TP->query_gender() != 1)
 *          return "You wouldn't look good in that!\n";
 *
 *      write("You fasten the "+TO->short()+" around your neck.\n");
 *      say(QCTNAME(TP)+" wears a "+TO->short()+".\n");
 *      return 1;
 *  }
 *
 *  // optional function
 *  public mixed
 *  remove_khalakhor_item(object item)
 *  { 
 *      if (TP->query_stat(SS_INT) < 20)
 *          return "It's too pretty to take off!\n";
 *
 *      write("You unfasten the "+TO->short()+".\n");
 *      say(QCTNAME(TP)+" removes a "+TO->short()+".\n");
 *      return 1;
 *  }
 *
 * Borrowed from /d/Terel/std/wearable_item.c
 * Tomas  -- June 2000
 */

#pragma strict_types
#pragma save_binary

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include "/d/Khalakhor/sys/defs.h"
#include <wa_types.h>

//** prototypes **//
public void   create_khalakhor_wearable_item();
public mixed  wear_khalakhor_item(object o);
public mixed  remove_khalakhor_item(object o);


public void
create_khalakhor_wearable_item()
{
}


/*
 * Function name: create_object
 * Description  : Allows for centralized control over all
 *                items inheriting this object. You cannot
 *                redefine this function, instead use
 *                create_khalakhor_wearable_item.
 */

public nomask void
create_object()
{
    /* define the location this item is worn at, the layers it occupies, 
     * its looseness, and the object that defines the wear/remove 
     * functions for this item.
     */
    config_wearable_item(A_NO_T, 0, 0, TO);
    set_name("_std_khalakhor_wearable_item");
    create_khalakhor_wearable_item();
}


/*
 * Function name: wear_khalakhor_item
 * Description  : This function is called when someone who can fit this 
 *                item tries to wear it.
 * Arguments    : object item - The item we want to wear.
 * Returns      : int  0 - The item can be worn, use default messages.
 *                     1 - The item can be worn, use your own messages.
 *                string - The item can't be worn, use this message.
 */

public mixed
wear_khalakhor_item(object item)
{
    return 0;
}


/*
 * Function name: wear
 * Description  : This function is called when someone 
 *                tries to wear this item, and it determines if the
 *                potential wearer is a good fit. You cannot redefine
 *                this function, instead use wear_khalakhor_item.
 * Arguments    : object item - The item we want to wear.
 * Returns      : see wear_khalakhor_item
 */

public mixed
wear(object item)
{
    return wear_khalakhor_item(item);
}


/*
 * Function name: remove_khalakhor_item
 * Description  : This function is called when someone tries to 
 *                remove this item.
 * Arguments    : object item - The item we want to remove.
 * Returns      : int  0 - The item can be removed, use default messages.
 *                     1 - The item can be removed, use your own messages.
 *                string - The item can't be removed, use this message.
 */

public mixed
remove_khalakhor_item(object item)
{
    return 0;
}


/*
 * Function name: remove
 * Description  : This function is called when someone 
 *                tries to remove this item. You cannot redefine
 *                this function, instead use remove_khalakhor_item.
 * Arguments    : object item - The item we want to remove.
 * Returns      : see remove_khalakhor_item
 */

public nomask mixed
remove(object item)
{
    return remove_khalakhor_item(item);
}



/*
 * Function name: wearable_item_leave_env
 * Description:   Make sure that the item is removed when it is
 *                moved.  This should normally be called from the
 *                leave_env() function of the inheriting object.
 * Arguments:     object from - the environment left
 *                object to   - the environment entered
 */

public void
wearable_item_leave_env(object from, object to)
{
    if (!worn)
    {
        return;
    }

    if (!wear_func || !wear_func->remove(this_object()) && wearer)
    {
        tell_object(wearer, 
            "You remove the " + this_object()->short() + ".\n");
    }

    do_remove_item();
    this_object()->remove_adj("worn");
    worn = 0;
}


/*
 * Function name: leave_env
 * Description  : When you inherit /lib/wearable.c into any object other
 *                than /std/armour.c you MUST also define the function
 *                leave_env() as copy of this function. It MUST make the
 *                call to wearable_item_leave_env(from, to) as well. If
 *                you omit this, then the item will not be automatically
 *                removed when the player drops it, for instance.
 * Arguments    : object from - the environment we are leaving.
 *                object to   - the environment we are entering.
 */

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    wearable_item_leave_env(from, to);
}
