/*
 * Base for citizens around Jems Court who pay protection
 * to the Brix gang.  Occasionally when attacked, the
 * Brix will defend them... if for no other reason than
 * an excuse to fight someone.
 *
 * Mortis 10.2006
 *
 */

#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <language.h>
#include "../../local.h"

// Three types:  man, woman, child
#define WHAT_BRIX_AM_I		"_what_brix_citizen_am_i"
// Dozens of occupations listed in jemsdad.
#define WHAT_OCCU_AM_I		"_what_palanthas_occupation_am_i"

inherit M_FILE
inherit AUTO_TEAM

int help_counter = 1; // Cannot call more than one hoodlum.

public void
create_brix_citizen()
{
}

void
create_krynn_monster()
{
    set_pick_up_team("_brix_citizen");
    set_max_team_size_auto_join(9);

	create_brix_citizen();
}

void
attacked_by(object ob)
{
	string swhat,
		   brixprop = TO->query_prop(WHAT_BRIX_AM_I),
		   occuprop = TO->query_prop(WHAT_OCCU_AM_I),
		   whoname  = ob->query_nonmet_name();

	switch (brixprop)
	{
		case "man":
			swhat = one_of_list(({"asay frantic I'm just a " + one_of_list(({
			"poor", "lowly", "destitute"})) + " " + occuprop + ".  Why kill me?",
			"asay desperat Please!  Spare my family!", "asay confident "
			+ "Constable Hagen will have your head for this!", "shout Help!  "
			+ "Somebody help me!", "shout My family is being murdered!  HELP!",
			"asay loud I have protection.  You won't get away with this!",
			"asay angri The Brix will take care of you now!"}));
			break;
		case "woman":
			swhat = one_of_list(({"scream", "shout Murderer, no!  Leave us be!",
			"shout MURDERER!  Leave my family be!", "asay frantic Spare my "
			+ "children!  At least spare the children!!!", "asay desperat "
			+ "I'll do anything, please!  Just leave my family be!", "asay "
			+ "fearful The constable will put you away for the rest of your "
			+ "life for this.  Flee while you still can!", "asay spite The "
			+ "Brix will do things to you for this that even a murderer like "
			+ "you never imagined!"}));
			break;
		case "child":
			swhat = one_of_list(({"shout Mommy!", "asay tearful Mommy, I "
			+ "don't wanna die!", "asay fearful Help me, daddy!", "asay "
			+ "painful It hurts!  Please make the murderer stop!",
			"cringe", "panic"}));
			break;
		default:
			break;	
	}

	TO->command(swhat);

	// 10% chance a lowly Brix ganger assists.
	if (random(10) == 1 && help_counter == 1)
	{
		string attwho = ob->query_name();
		string saywha = one_of_list(({"asay eager So, you like picking on "
		+ "peons, huh?  Then taste brick!", "asay hung Someone wants a "
		+ "fight?  Come get some!", "shout Die, whore!", "shout You're in "
		+ "Brix territory now.  Time to pay up!", "asay evil I've been "
		+ "waiting for a tiff.  Let's get it on."}));

		object cprot = clone_object(MONKS + "living/brix_ganger_low");
		cprot->move(E(TO));
		cprot->command("emote bursts in the door!");
		cprot->command("kill " + attwho);
		cprot->command(saywha);
		cprot->command("wield all");
	}

	help_counter = 0;

	::attacked_by(ob);
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
