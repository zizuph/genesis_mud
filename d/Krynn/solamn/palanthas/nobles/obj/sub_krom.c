/* Mortis 12.2005
 *
 * Add ability to remove dirt?  Or reserve that for spa baths?
 */

#include "../../local.h"

inherit "/std/object";

#define SUBLOC			"_pal_cologne_krom_subloc"

void
create_object()
{
    set_name("_pal_krom_control");
    set_long("Subloc from Krom cologne sold in Palanthas.\n");
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
	string scent = "wearing Krom, an ancient and mystic scent from "
	+ "Jordesse Parfumerie in Palanthas' trendy Plaisir district.";

	if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

	if (for_obj == carrier)
	{
		pro = "you are ";
	}
	else
	{
		pro = carrier->query_pronoun() + " is ";
		pos = carrier->query_possessive();
	}

	if (for_obj->query_gender() == 0 && for_obj != carrier)
	{
		scent = "wearing an ancient and mystic scent.  The scent of "
		+ "an age past fills your senses with passing memories of the "
		+ "battles of gods and giants and men who lived and died by the "
		+ "mettle of which they were tempered.  Iron, leather, and musk...  "
		+ "no man seems " + pos + " match.";
	}
	if (for_obj->query_gender() != 0 && for_obj != carrier)
	{
		scent = "wearing Krom, an ancient and mystic scents of an "
		+ "age past that fills your senses with passing memories of the "
		+ "battles of gods and giants and men who lived and died by the "
		+ "mettle of which they were tempered.  Iron, leather, and musk...  "
		+ "no man is " + pos + " match under Krom.";
	}

	return C(pro) + scent + "\n";
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
