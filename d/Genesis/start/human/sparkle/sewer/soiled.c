inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "sewer.h"


int covered;    // 2 - finger
				// 1 - hand
				// 0 - whole body
				
public int wipe_clean(string str);


public void
set_body_part(int code = 0)
{
	covered = code;
}

public string
get_body_part()
{
	return(covered == 2 ? "finger" : (covered == 1 ? "hand" :
		"whole body"));
}

public void
create_object()
{
	set_name("faeces");
	set_short("Faeces");
	set_long("Slimy sewage and faeces.\n");
	set_no_show();
	seteuid(getuid(this_object()));
	remove_prop(OBJ_I_VALUE);
	remove_prop(OBJ_I_WEIGHT);
	remove_prop(OBJ_I_VOLUME);
	add_prop(OBJ_M_NO_GIVE, 1);
	add_prop(OBJ_M_NO_DROP, 1);
	add_prop(OBJ_M_NO_SELL, 1);
}
    
/*
 **************************************************************************
 * Function name: enter_env(object to, object from)
 * Description  : adds the subloc when 'picked up'. 
 * Arguments	: object to - normally the carrier player file
 *                object from - the object this_object() comes from
 *
 */
public nomask void
enter_env(object to, object from)
{
    if (living(to))
    {
		to->add_subloc(SUBLOC_SOILED, this_object());
		::enter_inv(to, from);
    }
}   

/*
 **************************************************************************
 * Function name: leave_env(object from, object to)
 * Description  : removes the subloc when this_object() is removed from
 *                ETO.
 * Arguments	: object to - the object to move this_object() to
 *                object from - the 'ex-carrier' player object
 *
 */
public nomask void
leave_env(object from, object to)
{
    if (living(from))
    	from->remove_subloc(SUBLOC_SOILED);
    ::leave_env(from, to);
}


/*
 ************************************************************************
 * Function name: show_subloc
 * Description:   This is called every time someone examines the
 *                bearer of this object
 * Arguments:     subloc - The subloc we are showing
 *                me - the player getting soiled
 *                for_obj - the player looking
 * Returns:       The fancy bit we are adding to the description of the
 *                bearer
 */
public string
show_subloc(string subloc, object me, object for_obj)
{
	if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
		return "";

	if (subloc != SUBLOC_SOILED)
		return me->show_subloc(subloc, me, for_obj);

	return ((for_obj == me ? "Your" : capitalize(me->query_possessive())) +
		" " + get_body_part() + " is covered in faeces!\n");
}

public void
init()
{
	::init();

	add_action("wipe_clean", "wipe");
}

public int
wipe_clean(string str)
{
	object *obs, target;
	string *words;

	words = explode(str, " ");

	if (words[0] != "finger" && words[0] != "hand")
		return notify_fail("Wipe what?\n");
	
	if (parse_command(str, environment(this_player()),
		" [hand] / [finger] 'on' %l", obs))
	{
		target = obs[obs[0]];
		if (get_body_part() != words[0])
		{
			this_player()->catch_msg("Wipe what on " + QCTNAME(target) + "?\n");
			return 1;
		}

		this_player()->catch_msg("You wipe your slimy, beshitted " + words[0] +
			" clean on an enraged " + QCTNAME(target) + ".\n");
		target->catch_msg(QCTNAME(this_player()) + " wipes " +
			this_player()->query_possessive() + " beshitted and stinking " +
			words[0] + " clean on you!\n");
		say(QCTNAME(this_player()) + " wipes " +
			this_player()->query_possessive() + " soiled and stinking " +
			words[0] + " clean on " + QCTNAME(target) + "!\n", ({this_player(),
			target}));
		remove_object();
		return 1;
	}

	notify_fail("Wipe " + words[0] + " on whom?\n");
	return 0;
}

