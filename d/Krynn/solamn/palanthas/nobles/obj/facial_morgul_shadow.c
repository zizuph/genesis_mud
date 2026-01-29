/*
 * Subloc item given after someone successfully finishes
 * a morgul shadow facial from the Laethorian pamperer.
 *
 * Mortis 01.2007
 */

#include "../../local.h"

inherit "/std/object";

#define SUBLOC			"_pal_facial_morgul_shadow_subloc"

void
create_object()
{
    set_name("_pal_facial_morgul_shadow");
    set_long("Subloc from morgul shadow facial from the Laethorian "
	+ "pamperer in Palanthas' Plaisir district.\n");
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
	string pro = carrier->query_pronoun();		// pronoun of carrier
	string pos = carrier->query_possessive();	// possessive of carrier

	if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

	if (for_obj == carrier)
		return "Icy tendrils of shadow undulate from beneath the hood of "
		+ "your robe concealing your face in their darkness.\nYou feel a "
		+ "calming invigoration spreading through your veins as if rivers "
		+ "from the Shadows coursed inside turning your blood to ice and "
		+ "giving your visage a mask of emotionlessness and supreme "
		+ "control.\n";
	else
		return "Icy tendrils of shadow undulate searchingly from beneath "
		+ "the hood of " + pos + " robe concealing " + pos + " face in "
		+ "their darkness.\nThe tendrils appear to be reaching for you as "
		+ pro + " gazes back at you, " + pos + " visage as cold and "
		+ "unflinching as ice leaving no doubt of " + pos + " mastery.\n";
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
