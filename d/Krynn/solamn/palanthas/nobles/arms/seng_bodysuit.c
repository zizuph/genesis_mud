/* Mortis 02.2006
 *
 * Bodysuit worn by Seng, Masseus in Laethorian
 * dayspa of Palanthas' Plaisir district.
 *
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <std.h>
#include "../../local.h"

inherit "/cmd/std/command_driver";

#define VK_NOBUY                    "_vkeep_shop_no_buy"

// Prototypes
void set_up_props();

public void
create_armour()
{
	set_name("bodysuit");
	set_pname("bodysuits");
	add_name(({"suit"}));
	add_pname(({"suits"}));
	set_adj("skin-tight");
	add_adj(({"white", "elfwyr", "body"}));
	set_short("skin-tight white elfwyr bodysuit");
	set_pshort("skin-tight white elfwyr bodysuits");
	set_long("The bodysuit covers its wearer from the wrists to the neck "
	+ "to the ankles in skin-tight elfwyr, a fabric so light and delicate "
	+ "to the touch that it can hardly be felt when worn.  Elfwyr is the "
	+ "rarest of materials in Palanthas and rarely seen in the possession "
	+ "of any but the elven nobility of a select few reclusive clans.  The "
	+ "secrets of its production are virtually unknown.  The material is "
	+ "perfectly form fitting revealing every curve beneath.\n");

	set_ac(15);
	set_at(A_TORSO | A_ARMS | A_LEGS);

	set_alarm(0.5, 0.0, "set_up_props");
}

void
init()
{
    ::init();
    ADA("bow");
	ADD("bow", "curtsey");
	ADA("stretch");
}

int bow(string str)
{
	int gender = TP->query_gender();
	string *how;
	string genderstyle = "muscular build";
	string bow = query_verb();
	string bows = query_verb() + "s";
	string oshort = short();
	object *oblist;
	how = parse_adverb_with_space(str, "slowly", 1);
	oblist = parse_this(how[0], "%l");

	if (gender == G_FEMALE)
		genderstyle = "lithe muscles";

	if (TO->query_worn())
	{
		if (!sizeof(oblist))
		{ 
			write("You " + bow + how[1] + ", your " + genderstyle + " visible "
			+ "beneath your " + oshort + ".\n");
			allbb(" " + bows + how[1] + ", " + HIS(TP) + " " + genderstyle
			+ " visible beneath " + HIS(TP) + " " + oshort + ".");
			return 1;
		}

		actor("You " + bow + how[1] + " to", oblist, ", your " + genderstyle
		+ " visible beneath your " + oshort + ".");
		target(" " + bows + how[1] + " to you, " + HIS(TP) + " " + genderstyle
		+ " visible beneath " + HIS(TP) + " " + oshort + ".", oblist);
		all2act(" " + bows + how[1] + " to", oblist,  ", " + HIS(TP) + " "
		+ genderstyle + " visible beneath " + HIS(TP) + " " + oshort + ".");
		return 1;
	}
	return 0;
}

void
set_up_props()
{
	 add_prop(OBJ_I_VOLUME, 50);
	 add_prop(OBJ_I_WEIGHT, 400 + random(50));
	 add_prop(OBJ_I_VALUE, 9250 + random(750));
	 add_prop(VK_NOBUY, 1);
}

int stretch(string str)
{
	int gender = TP->query_gender();
	string *how;
	string genderstyle = "muscular build";
	string bod = "manly";
	string oshort = short();
/*	string bod = TP->query_prop(WEIGHTDESC);  If anyone ever makes someone's
	width queryable, this can be uncommented and string bod used to
	describe someone's body in this emote. */
	how = parse_adverb_with_space(str, "in an athletic manner", 0);

	if (gender == G_FEMALE)
	{
		genderstyle = "lithe muscles";
		bod = "shapely";
	}

	if (TO->query_worn())
	{
		write("You stretch your " + bod + " body out" + how[1] + ", the "
		+ genderstyle + " of your midriff visible beneath your " + oshort
		+ ".\n");
		say(QCTNAME(TP) + " stretches " + HIS(TP) + " " + bod + " body out"
		+ how[1] + ", the " + genderstyle + " of " + HIS(TP) + " midriff "
		+ "visible beneath " + HIS(TP) + " " + oshort + ".\n");
		return 1;
	}
	return 0;
}
