/*
 * Based on the Kalad dirtiness code
 * This code shows the bruises a player receives when hit
 * with the smith's ring.
 * - Finwe, January 2001
 */

#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include "/d/Shire/sys/defs.h"

#define SUBLOC "_smith_ring_hit"
#define BRUISED_OBJECT_ID "_smith_ring_bruised"
string bruised (object carrier);

void
create_object()
{
    set_name(BRUISED_OBJECT_ID);
    add_name("bruised"); // old name, kept for compatibility.

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

    if( (carrier->query_prop(LIVE_I_BRUISES) / 10) < 1)
	return "";
    else
	return capitalize(pro) + bruises(carrier);
}

string
bruises(object carrier)
{
    switch(carrier->query_prop(LIVE_I_BRUISES) / 10)
    {
    case 0:
	return "very few bruises.\n";
    case 1:
	return "lightly bruised.\n";
    case 2:
	return "bruised and with some tender marks.\n";
    case 3:
	return "discolored and bruised.\n";
    case 4:
	return "bruised with some yellow and green marks.\n";
    case 5:
	return "favouring one side of the body with fewer bruises.\n";
    case 6:
	return "red and sore looking with bruises.\n";
    case 7:
	return "red and sore looking with bruises.\n";
    case 8:
	return "throbbing in pain from some bruises.\n";
    case 9:
	return "wincing in pain from some bruises.\n";
    case 10:
	return "black and blue from being slapped.\n";
    default :
	return "nearly disabled from being slapped.\n";
    }
}
