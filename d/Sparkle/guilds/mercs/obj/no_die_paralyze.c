/* player is paralyzed for a while instead of Dead! */

#include "/d/Krynn/common/defs.h"

inherit "/std/paralyze";

void
my_stop_obj()
{
    set_stop_object(E(TO));
}

void
create_paralyze()
{
    set_no_show_composite(1);
    set_standard_paralyze("paralyze");
    set_stop_verb("");
    set_alarm(3.0,0.0,my_stop_obj);
    set_stop_fun("wake_up_again");
    set_stop_message("You slowly regain consciousness.\n");
    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_M_NO_GIVE,1);
    set_fail_message("You are unconscious, you cannot do anything!\n");
}

/*
void
revive_thing()
{
    find_player("aridor")->catch_msg(file_name(E(TO)));
    if (E(TO))
    {
	E(TO)->remove_prop(LIVE_S_EXTRA_SHORT);
	E(TO)->wake_up_again();
    }
}
*/

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *                me      - I
 *                for_obj - The looker
 * Returns:  The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    string str;
    if (subloc != "unconscious_subloc")
      return "";
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
    if (for_obj == me)
      str = "You are ";
    else
      str = capitalize(me->query_pronoun()) + " is ";
    return str + "unconscious.\n";
}

void
leave_env(object from, object to)
{
    if (living(from) && !living(to))
      set_alarm(1.0,0.0,"remove_object");
    ::leave_env(from,to);
}

/*
 * Function name: stop
 * Description:   Here all commands the player gives comes.
 * Argument:	  str - The extra string the player sent.
 */
varargs int
stop(string str)
{
    /* Only paralyze our environment */
    if (environment(this_object()) != this_player())
	return 0;

    if (query_verb() == "commune" || query_verb() == "quit")
      return 0;

    if (stop_verb && query_verb() == stop_verb)
    {
    /* If a stop_fun is defined it MUST return 1 to not stop the paralyze */
	if (stop_object && call_other(stop_object, stop_fun, str))
	    return 1;

	set_alarm(1.0,0.0,"remove_object");

	if (stop_message)
	    this_player()->catch_msg(stop_message);

	return 1;
    }

    if (fail_message)
	this_player()->catch_msg(fail_message);

    if (!this_player()->query_wiz_level())
	return 1;

    write("Since you are a wizard this paralyze won't affect you.\n");
    return 0;
}
