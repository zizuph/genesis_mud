/*
 *  ~paddle_marks.c
 *
 */
#pragma strict_types

inherit "/std/object";

#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "zigg.h"

#define SUBLOC "_paddle_mark_"
#define TIME 300.0

public static int mark;

public void
create_object(void)
{
    set_no_show();
    set_name(({"paddle mark", "mark", "Zig::PMark",}));
}

public void
remove_object(void)
{
    if (IS_CLONE)
	ENV()->remove_subloc(SUBLOC);

    ::remove_object();
}

public int
query_mark(void)	{ return mark; }

public void
set_blows(void)		{ mark += 1; }

public string
show_subloc(string subloc, object carrier, object for_obj)
{
    string color;
    object *cover = ({ });

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (mark < 5)
	return "";

    switch(mark)
    {
    case 51..60:  color = "scarlet";			break;
    case 41..50:  color = "crimson";			break;
    case 31..40:  color = "bright red";			break;
    case 21..30:  color = "rosy red";			break;
    case 11..20:  color = "rosy pink";			break;
    case  5..10:  color = "lightly pink";		break;
    default:      color = "scarlet red and glowing";	break;
    }

    foreach(int slot : ({ TS_LHIP, TS_RHIP, TS_ROBE }))
	cover += carrier->query_clothing(slot);

    foreach(object ob : cover)
    {
	if (ob->id("shoes") || ob->id("boots") || ob->id("greaves"))
	{
	    cover -= ({ ob });
	}
    }

    subloc = "";

    if (for_obj == carrier)
    {
	if (sizeof(cover))
	{
	    subloc = "Your covered bottom feels tender and "+ color +
		" beneath the "+ one_of_list(cover)->short() +".\n";
	}
	else
	{
	    subloc = "Your bottom is tender and "+ color +".\n";
	}
    }
    else if (!sizeof(cover))
    {
	subloc = capitalize(HIS(carrier)) +" bottom is "+ color +".\n";
    }

    return subloc;
}

public void
heal_mark(void)
{
    mark -= 1;

    if (!mark)
	set_alarm(0.0, 0.0, remove_object);
    else
	set_alarm(TIME, 0.0, heal_mark);
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    to->add_subloc(SUBLOC, TO);
    set_alarm(TIME, 0.0, heal_mark);
}
