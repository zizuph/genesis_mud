#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include "/d/Kalad/sys/properties.h"

#define SUBLOC "_kalad_dirty_subloc"

string dirtiness(object carrier);

void
create_object()
{
    set_name(DIRTY_OBJECT_ID);
    add_name("dirty"); // old name, kept for compatibility.

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_STEAL, 1);

    set_no_show();
}

void
enter_env(object to, object from)
{
    if (living(to))
	to->add_subloc(SUBLOC, this_object());
    ::enter_inv(to, from);
}

void
leave_env(object from, object to)
{
    if(living(from))
	from->remove_subloc(SUBLOC);
    ::leave_env(from, to);
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    string pro;   /*pronoun of carrier*/
    string pos;   /*possessive of carrier*/

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (for_obj == carrier)
    {
	pro = "you are ";
    }
    else
    {
	pro = carrier->query_pronoun() + " is ";
    }

    if( (carrier->query_prop(LIVE_I_DIRTY) / 10) < 1)
	return "";
    else
	return capitalize(pro) + dirtiness(carrier);
}

string
dirtiness(object carrier)
{
    switch(carrier->query_prop(LIVE_I_DIRTY) / 10)
    {
    case 0:
	return "spanking clean.\n";
    case 1:
	return "slightly sweaty.\n";
    case 2:
	return "sweaty and slightly dirty.\n";
    case 3:
	return "dirty and sweaty.\n";
    case 4:
	return "dirty and unpleasant smelling.\n";
    case 5:
	return "very dirty and sour smelling.\n";
    case 6:
	return "very dirty and smelling wretched.\n";
    case 7:
	return "filthy and completely reeking.\n";
    case 8:
	return "filthy and smelling like vomit.\n";
    case 9:
	return "disgustingly filthy and smelling like feces.\n";
    case 10:
	return "sickeningly filthy and unbearably putrid.\n";
    default :
	return "so filthy it can't be described with words.\n";
    }
}
