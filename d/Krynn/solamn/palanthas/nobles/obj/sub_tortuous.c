/* Mortis 12.2005
 *
 * Add ability to remove dirt?  Or reserve that for spa baths?
 */

#include "../../local.h"

inherit "/std/object";

#define SUBLOC			"_pal_perfume_tortuous_subloc"

void
create_object()
{
    set_name("_pal_perfume_tortuous");
    set_long("Subloc from Tortuous perfume sold in Palanthas.\n");
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
	string scent = "wearing Tortuous, a hot, attractive fragrance from "
	+ "Jordesse Parfumerie in Palanthas' chic Plaisir district.";

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
		scent = "wearing Tortuous.  Your body temperature rises "
		+ "as this hypnotic fragrance captures your senses with memories of "
		+ "long nights, the darkest red wine, tight embraces, and passionate "
		+ "dances around a fire under the moon as the music and clapping of "
		+ "the watchers drives you on and a hot wind shakes the leaves from "
		+ "the trees above.  You snap yourself out of your reverie short of "
		+ "breath, your heart beating fiercely, and you smile to yourself as "
		+ "you wipe your brow and catch your breath.";
	}
	if (for_obj->query_gender() !=1 && for_obj != carrier)
	{
		scent = "wearing a captivating fragrance you cannot ignore.  "
		+ "Your body temperature rises as this hypnotic fragrance mesmerizes "
		+ "your senses with memories of long nights, the darkest red wine, "
		+ "tight embraces, and passionate dances around a fire under the "
		+ "moon as the music and clapping of the watchers drives you on and "
		+ "a hot wind shakes the leaves from the trees above.  You snap "
		+ "yourself out of your reverie short of breath, your heart beating "
		+ "fiercely, to find yourself staring at " + pos + " with a strong "
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
