/* Mortis 01.2006
 *
 * Subloc item given after someone successfully finishes
 * a massage from the Laethorian masseus.
 *
 */

#include "../../local.h"

inherit "/std/object";

#define SUBLOC			"_laethorian_masseus_subloc"

void
create_object()
{
    set_name("_pal_laethorian_masseus");
    set_long("Subloc from massage from the Laethorian masseus in "
	+ "Palanthas' Plaisir district.\n");
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_STEAL, 1);

    set_no_show();
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
	string pro;		// pronoun of carrier
	string pos;		// possessive of carrier
	string rpro = carrier->query_pronoun();
	string rpos = carrier->query_possessive();
	string facial = "body feels youthfully invigorated and your muscles "
	+ "re-energized!\nYou feel refreshed and more relaxed than you've "
	+ "felt in a long time.";

	if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

	if (for_obj == carrier)
	{
		pos = "Your ";
	}
	else
	{
		pro = carrier->query_pronoun();
		pos = carrier->query_possessive();
	}

	if (for_obj != carrier)
	{
		facial = " body appears youthfully invigorated and " + pos
		+ " muscles re-energized!\n" + C(pro) + " seems refreshed and relaxed.";
	}
	
	return C(pos) + facial + "\n";
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
