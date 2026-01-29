/* Some blood ... just for effect */
/*
 * Revisions:
 * 	Lucius, Jul 2017: Re-Code
 */
#pragma strict_types
inherit "/std/object";

#include <composite.h>
#include <stdproperties.h>

#include "../defs.h"

#define BLOOD   "_union_bloody_subloc"

public int heal_alarm;
public string *hits = ({ });

public void
create_object()
{
    set_name("wounds");
    add_name("avenir_fling_blood");

    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    add_prop(OBJ_M_NO_DROP, 1);

    set_no_show();

    add_item(({"wound","wounds"}),"It is a long gash on your "
      + "@@query_hits@@, caused by being struck with a knife.\n");
}

public string
query_hits()
{
    if (sizeof(hits) > 7)
	return COMPOSITE_WORDS(hits[0..6]);
    else
	return COMPOSITE_WORDS(hits);
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!living(to))
	return;

    to->add_subloc(BLOOD, TO);
}

public void
leave_env(object to, object from)
{
    ::leave_env(to, from);
    from->remove_subloc(BLOOD);
}

public string
show_subloc(mixed subloc, object on, object for_obj)
{
    string str;

    if (for_obj->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
	subloc != BLOOD || !sizeof(hits))
	return "";

    if (for_obj != on)
    {
	str = (sizeof(hits) > 1 ? "Wounds" : "A wound") +
	    " on " + HIS(on) + " " + query_hits() + " " +
	    (sizeof(hits) > 1 ? "are" : "is") + " bleeding.\n";
    }
    else
    {
	str = (sizeof(hits) > 1 ? "Wounds" : "A wound") +
	    " on your " + query_hits() + " " +
	    (sizeof(hits) > 1 ? "are" : "is") + " bleeding.\n";
    }

    return str;
}

public void
heal(void)
{
    if (!sizeof(hits) <= 1)
    {
	remove_alarm(heal_alarm);
	set_alarm(0.0, 0.0, remove_object);
	return;
    }

    hits -= ({ hits[0] });
}

public void
add_hurt(string where)
{
    if (member_array(where, hits) == -1)
	hits += ({ where });

    if (!heal_alarm)
	heal_alarm = set_alarm(200.0, 500.0, heal);
}
