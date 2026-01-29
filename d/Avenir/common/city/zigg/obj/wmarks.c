/*
 *  ~marks.c
 *
 * Revisions:
 *   Lucius, May 2016: Add cover blocking to subloc.
 *   Lucius, May 2016: Added locations support.
 */
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "zigg.h"

#define SUBLOC "_lash_marks_"

public static mapping marks = ([]);


public void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_no_show();
    set_name(({"lash marks", "marks", "Zig::WMark",}));

    add_prop(OBJ_M_NO_DROP, 1);
}

public void
add_lashes(string where)
{
    switch(where)
    {
    case "chest":
    case "bosom":
    case "tummy":
    case "stomach":
	where = "torso";
	break;
    case "arm":
    case "hand":
    case "shoulder":
	where = "arm";
	break;
    case "leg":
    case "foot":
    case "thigh":
	where = "leg";
	break;
    case "bottom":
	where = "back";
	break;
    }
		  
    ++marks[where];
}

private static mapping slots = ([
    "arm"   : ({ A_ANY_ARM, TS_ROBE }),
    "leg"   : ({ TS_LEGS,   TS_ROBE }),
    "back"  : ({ TS_BACK,   TS_ROBE }),
    "torso" : ({ TS_CHEST,  TS_ROBE }),
]);

public string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str = "";

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    foreach(string where, int count: marks)
    {
	object *cover = ({ });

	foreach(int slot : slots[where])
	    cover += carrier->query_clothing(slot);

	if (count == 1)
	{
	    subloc = "a";
	}
	else
	{
	    if (count > 9)
		subloc = "many";
	    else
		subloc = LANG_NUM2WORD(count);

	    if (where == "arm" || where == "leg")
		where += "s";
	}

	if (sizeof(cover))
	    where += ", hidden from sight";

	if (for_obj == carrier)
	{
	    str += "You have " + subloc +" tender lash mark"+
		(count > 1 ? "s criss-crossing your " :
		    " streaked across your ") + where + ".\n";
	}
	else if (!sizeof(cover))
	{
	    str += capitalize(HE(carrier)) + " has " + subloc +
		" red lash mark" + (count > 1 ?
		    "s criss-crossing " : " streaked across ") +
		HIS(carrier) + " " + where + ".\n";
	}
    }

    return str;
}

public int
heal_marks(object ob)
{
   ob->remove_subloc(SUBLOC);
   set_alarm(0.0, 0.0, remove_object);
   return 1;

}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    to->add_subloc(SUBLOC, this_object());
    set_alarm(3600.0, 0.0, &heal_marks(to));
}
