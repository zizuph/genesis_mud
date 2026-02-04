/*
 * /d/Terel/mountains/ghastly_keep/obj/g_potion_cooldown.c
 *
 * The cooldown object for the potions.
 *
 * No emotes, to prevent triggers.
 *
 * Znafsnuf
 *
 * modified from Olorin's Ipotion.c, by Teth Jan 1997
 *
 * - Language tweak complete (Gorboth)
 */

inherit "/std/object";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

#define SUBLOC "_gkeep_brew_subloc"

int time;
object target;

/*
 * Function name: set_duration()
 * Description  : Sets the duration of the cooldown.
 */
void
set_duration(int i)
{
    time = i;
}

/*
 * Function name: query_duration()
 * Description  : Return the duration.
 */
int
query_duration(int i)
{
    return time;
}

/*
 * Function name: create_object
 * Description  : Set up default values for parts of the ship
 */
void
create_object()
{
    set_name("_gkeep_throw_cooldown");
    
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(MAGIC_AM_MAGIC, ({"enchantment", 50}));
    add_prop(OBJ_S_WIZINFO, "Keep track of the cooldown.");
    set_no_show();
}

void
end_effect()
{
    remove_object();
}

/*
 * Function name: set_target
 * Description  : The consumer.
 */
void
set_target(object obj)
{
    target = obj;
}

/*
 * Function name: enter_env
 * Description  : When we enter an interactive environment, add a subloc to
 *                indicate that the person is writing something.
 * Arguments    : object to - the object we are entering.
 *                object from - the object we come from.
 */
void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(to) || !living(to))
    {
      remove_object();
      return;
    }
    to->add_subloc(SUBLOC, this_object());
    set_alarm(itof(time), 0.0, end_effect);
}

/*
 * Function name: leave_env
 * Description  : When you inherit /lib/holdable_item.c you MUST also define
 *                the function leave_env() as copy of this function. It MUST
 *                make the call to holdable_item_leave_env(from, to) as well.
 *                If you omit this, then the item will not be automatically
 *                released when the player drops it, for instance.
 *                PS: This is just a dummy function. It does not exist. You
 *                    must write your own as copy of this one.
 * Arguments    : object from - the environment we are leaving.
 *                object to   - the environment we are entering.
 */
void
leave_env(object old, object dest)
{
    old->remove_subloc(SUBLOC);
    ::leave_env(old, dest);
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
show_subloc(string subloc, object on, object for_obj)
{
    string str;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    return "";

    if (for_obj == on)
    str = "You look ";
    else
    str = CAP(on->query_pronoun()) + " looks ";
    return str + "drenched with oozing liquid.\n";
}
