/*
 * Subloc item given after someone successfully finishes
 * a morgul fire facial from the Laethorian pamperer.
 *
 * Mortis 01.2007
 */

#include "../../local.h"

inherit "/std/object";

#define SUBLOC			"_pal_facial_morgul_fire_subloc"

void
create_object()
{
    set_name("_pal_facial_morgul_fire");
    set_long("Subloc from morgul fire facial from the Laethorian "
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
		return "Blazing red embers smoulder beneath the skin of your face "
		+ "wreathing it in a veil of roiling smoke through which you gaze "
		+ "unhindered.\nYou feel the power of the flames of Orodruin "
		+ "coursing through you igniting your blood to fire and giving "
		+ "your visage a mask of incendiary preeminence.\n";
	else
		return "Wreathed in a veil of roiling smoke, " + pos +" face is "
		+ "aglow as if blazing red embers smouldered beneath " + pos
		+ " skin.\n" + C(pos) + " visage is a conflagration of searing power "
		+ "and undefiable dominance.\n";
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
