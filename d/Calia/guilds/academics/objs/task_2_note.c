/* 
 * Approval Note for Herb Task
 *
 * This is the note that Lobar gives to the student upon successful
 * completion of the herb task.
 *
 * Created by Petros, December 2009
 */

inherit "/std/object";

#include <stdproperties.h>
#include "../defs.h"

// Global Variables
public string   owner_name;

void
create_object()
{
    set_name("note");
    add_name("academic_lobar_approval_note");
    set_adj( ({ "sealed", "approval" }) );
    set_long("This is a sealed approval note from Lobar indicating that "
        + "you have successfully completed your task. You should give "
        + "this to the Taskmaster Amjal.\n");
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
}

public void
set_owner_name(string name)
{
    owner_name = name;
}

public string
query_owner_name()
{
    return owner_name;
}

public void
destroy_note()
{
    if (objectp(environment(this_object())))
    {
        tell_object(environment(this_object()), "The " + short() + " blows away "
            + "and disappears.\n");
    }
    remove_object();
}

/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    
    if (strlen(owner_name)
        && dest->query_real_name() != "amjal" 
        && dest->query_real_name() != owner_name)
    {
        set_alarm(0.1, 0.0, destroy_note);
    }
}
