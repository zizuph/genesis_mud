/* Basic wand... no powers.
 * 
 * Based on Base Wand by Petros, March 2009
 */
 
inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solace/poolbottom/local.h"

public void
create_wand()
{
    if(TO->query_prop(OBJ_I_BROKEN))
    {
        TO->set_long("A broken wand, useful for little more than tinder.\n");
    }
    // Mask this function to customize the wand.
}

public string
query_wand_short()
{
    if(TO->query_prop(OBJ_I_BROKEN))
        return "broken wand";
    else
        return "wand";
}

public nomask void
create_object()
{
    set_name("wand");
    set_short(query_wand_short());
    set_long("This is a plain wand carved from wood. Little distinguishes " +
       "this instrument of the Magi from a common stick.\n");

    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 100);
        
    set_slots(W_ANYH);
    set_keep(1);

    add_cmd_item("wand","wave","@@wave_wand");
    
    //Enable default item expiration
    set_item_expiration();
    // Call the create_wand function for customization purposes
    // Give it a moment to load props before calling
    set_alarm(1.0, 0.0, &create_wand());
}

/*
 * Function name: release
 * Description  : Called when the person wants to release the item. This
 *                function may allow or disallow the object to be released,
 *                and it may print its own messages.
 * Returns      : string / int -
 *                 0 - The item can be relased, print default messages.
 *                 1 - The item can be relased, print no messages.
 *                     Messages were printed within the function.
 *                -1 - The item cannot be released. Print default messages.
 *                string - The item cannot be relased. The string contains the
 *                         fail message.
 */
public mixed
release()
{
    if(TO->query_prop(OBJ_I_BROKEN))
    {
        TO->add_adj("broken");
        TO->set_short("broken wand");
        TO->set_long("A broken wand, useful for little more than tinder.\n");
    }

    return 0;
}

string
wave_wand()
{
    if(!TO->query_held())
    {
        write("You have to be holding the wand to wave it.\n");
        return "";
    }

    write("You wave the " + short() + " around, but nothing happens.\n");
    say(QCTNAME(TP) + " waves the " + short() + " around and " +
      "makes some mystical gestures. Nothing seems to " +
      "happen.\n");
        return "";

}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    holdable_item_leave_env(env, to);
}

/*
 * Function name: query_recover
 * Description  : Called to check whether this herb is recoverable. If you
 *                have variables you want to recover yourself, you have to
 *                redefine this function, keeping at least the filename and
 *                the herb recovery variables, like they are queried below.
 *                If, for some reason, you do not want your herb to
 *                recover, you should define the function and return 0.
 * Returns      : string - the default recovery string.
 */
string
query_recover()
{
    return MASTER + ":" + query_item_expiration_recover();
} /* query_recover */

void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
    create_wand();
}