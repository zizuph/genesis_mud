/* Mortis 12.2005
 *
 * Add ability to remove dirt?  Or reserve that for spa baths?
 */

#include "../../local.h"

inherit "/std/object";

#define SUBLOC			"_pal_cologne_whitehammer_subloc"

void
create_object()
{
    set_name("_pal_whitehammer_control");
    set_long("Subloc from White Hammer cologne sold in Palanthas.\n");
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
	string scent = "wearing White Hammer, a crisp, clean scent from "
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
		scent = "wearing a scent that is clean and crisp.  The "
		+ "scents of White Hammer fill your senses reminding you of starlit "
		+ "nights illuminating the fresh, white snow on the slopes before "
		+ "you as a cold wind blows through your hair.  " + C(rpro) + " seems "
		+ " as if " + rpro + " can do no wrong.";
	}
	if (for_obj->query_gender() != 0 && for_obj != carrier)
	{
		scent = "wearing White Hammer, a clean, crisp, and "
		+ "attractive scent that fills your senses with vistas of starlit "
		+ "nights illuminating the fresh, white snow on the slopes before "
		+ "you as a cold wind blows through your hair, and you feel as if "
		+ "you can do no wrong in " + rpos + " enchanting eyes.";
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
