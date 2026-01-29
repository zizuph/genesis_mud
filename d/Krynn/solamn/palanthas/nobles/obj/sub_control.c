/* Mortis 12.2005
 *
 * Add ability to remove dirt?  Or reserve that for spa baths?
 */

#include "../../local.h"

inherit "/std/object";

#define SUBLOC			"_pal_cologne_control_subloc"

void
create_object()
{
    set_name("_pal_cologne_control");
    set_long("Subloc from Control cologne sold in Palanthas.\n");
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
	string scent = "wearing Control, a commanding scent from "
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
		scent = "wearing a commanding scent that rises to your "
		+ "nostrils.  " + C(rpro) + " seems filled with the essence of "
		+ "confidence, reliance, and cool resolve.  " + C(rpos) + " every "
		+ "word is chosen well and well received, and everything seems "
		+ "within " + rpos + " grasp.  " + C(pro) + " in... Control.";
	}
	if (for_obj->query_gender() != 0 && for_obj != carrier)
	{
		scent = "wearing Control, a commanding fragrance you can't "
		+ "seem to ignore.  The scent rises to your nose as your mind is "
		+ "filled with " + rpos + " essence of confidence, reliance, and cool "
		+ "resolve.  " + C(rpos) + " every word is crafted well and you sense "
		+ rpos + " deepest desires are within " + rpos + " grasp.  " + C(rpro)
		+ "is in... Control, as you find yourself gazing with an "
		+ "inexplicable yearning.";
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
