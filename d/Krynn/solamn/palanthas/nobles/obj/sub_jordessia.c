/* Mortis 12.2005
 *
 * Add ability to remove dirt?  Or reserve that for spa baths?
 */

#include "../../local.h"

inherit "/std/object";

#define SUBLOC			"_pal_perfume_jordessia_subloc"

void
create_object()
{
    set_name("_pal_perfume_jordessia");
    set_long("Subloc from Jordessia perfume sold in Palanthas.\n");
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
	string scent = "wearing Jordessia, the latest enthralling fragrance "
	+ "from Jordesse Parfumerie in Palanthas' chic Plaisir district.";

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

	if (for_obj->query_gender() == 1 && for_obj != carrier)
	{
		scent = "wearing Jordessia.  The latest fragrance from "
		+ "Jordesse fills your senses with passing memories of the full "
		+ "moon, its reflection blue upon the dark waters beneath your "
		+ "balcony as the night breeze tosses your hair back, and the "
		+ "dark outline of your companion appears from the shadows.  "
		+ "Underneath it all is the fragrance of a flower or musk or blossom "
		+ "you just can't place but cannot stop thinking about.";
	}
	if (for_obj->query_gender() !=1 && for_obj != carrier)
	{
		scent = "wearing an enthralling fragrance you cannot ignore.  "
		+ "The perfume fills your senses with passing memories of the full "
		+ "moon, its reflection blue upon the dark waters beneath a balcony "
		+ "as " + pos + " dark outline appears from the shadows, the night "
		+ "breeze tossing " + pos + " hair back as she draws close.  "
		+ "Underneath it all is the fragrance of a flower or musk or "
		+ "blossom you just can't place but cannot stop thinking about "
		+ "as you find yourself gazing at " + pos + " with a penetrating "
		+ "yearning.";
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
