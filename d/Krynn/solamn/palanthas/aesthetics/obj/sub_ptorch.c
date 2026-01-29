/*
 * Subloc given from blowing yourself up with a phosphentus
 * torch from Palanthas.
 *
 * Mortis 05.2006
 *
 */

#include "../../local.h"

inherit "/std/object";

#define SUBLOC			"_pal_ptorch_blastmark_subloc"

void
create_object()
{
    set_name("_pal_ptorch_blastmark");
    set_long("Subloc from blowing up a ptorch in your hands.\n");
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

	if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

	if (for_obj == carrier)
	{
		pro = "Your ";
	}

	else
	{
		pro = carrier->query_pronoun() + " is ";
		pos = carrier->query_possessive();
	}

	if (for_obj != carrier)
	{
		return C(pos) +  " face is completely blackened with blast marks and "
		+ pos + " hair blown back as if something blew up in " + pos
		+ " hands.\n";
	}

	return C(pro) + "face is completely blackened and your hair blown back "
	+ "from an explosion that occured right in front of you.\n";
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
