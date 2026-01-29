/*

  12 Aug 2006 - Palmer
  Prize for Blacksmiths of Bree Design Contest 
  The winner was Nome.
  This is a simple hat that lets you shout through it.

*/

inherit "/d/Shire/guild/smiths/obj/megaphone";

inherit "/lib/wearable_item";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#define SUBLOC "smith_hat"

public int
wear(object item)
{
    write("You smile proudly at your prize then slip the " + short() + " on your head.\n");
    say(QCTNAME(this_player()) + " smiles proudly at his prize then slips the " + short() + " on his head.\n");
    return 1;
}


void
enter_env(object to, object from)
{
    if (living(to))
        to -> add_subloc(SUBLOC, this_object());
    ::enter_inv(to, from);
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    if (living(from))
        from -> remove_subloc(SUBLOC);
    wearable_item_leave_env(from, to);
}

/*
 * Function name: show_subloc
 * Description  : Shows the specific sublocation description for a living.
 * Arguments    : string subloc  - the subloc to display.
 *                object on      - the object to which the subloc is linked.
 *                object for_obj - the object that wants to see the subloc.
 * Returns      : string - the subloc description.
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    string str;
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "You are the proud winner of the Smiths Guild design contest.\n";

    if (for_obj == me)
        return "You are the proud winner of the Smiths Guild design contest.\n";

    else
	  return "He is the proud winner of the Blacksmiths of Bree Design Contest.\n";
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


void
init()
{
    set_name("hat");
    set_short("red conical hat");
    add_adj("red");
    add_adj("conical");
    remove_name("megaphone");
    remove_name("iron megaphone");
    set_long("This conical shaped hat has a hollow tip. It will let you <project> your voice very far.\n");
    set_wf(this_object());
    set_slots(A_HEAD);
    set_layers(0);
    set_looseness(20);

    add_prop(OBJ_I_WEIGHT,  40);
    add_prop(OBJ_I_VOLUME,  50);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_GIVE,  1);
    add_prop(OBJ_M_NO_DROP,  1);
    add_action("project", "project");

}


int
project(string str)
{
    if (objectp(query_worn()))
    {
        notify_fail("You can't project while your hat is on your head.\n", 0);
        return 0;

    }
    ::do_project(str);
    return 1;
}
