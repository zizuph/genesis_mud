/*
 * Strange doglike creatures living with hobgoblins in
 * their cave along the road south of Palanthas.
 *
 * Mortis 10.2006
 */
// Give it wander and check attack + defense.

#include "../local.h";
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>

inherit C_FILE
inherit "/d/Krynn/std/act/actions";
inherit "/std/act/domove";
inherit "/std/act/attack";

// Prototypes
int my_aggression();

void
create_creature()
{
	int mygen = G_MALE;
	string adj2 = one_of_list(({"stoney", "grey", "black"}));

	set_name("rockdog");
	add_name("dog");
	set_race_name("rockdog");
	set_adj("scabbrous");
	add_adj(({adj2, "rock"}));

	if (random(3) == 1)
		mygen = G_FEMALE;

	set_gender(mygen);

	set_short("scabbrous " + adj2 + " rockdog");
	set_long("A sharp, focused intelligence glares hungrily back at you from "
	+ "this dog creature's small, oblong eyes.  Though shaped like a dog, "
	+ "its skin is covered in scabbrous patches like cracked and weathered "
	+ adj2 + " stone.  Its taut muscles ripple as it bears greenish-black "
	+ "fangs from its thick, pointed jaws.");

	set_stats((({10, 25, 30, 42, 40, 35})), 20);

	set_alignment(0);
	set_knight_prestige(0);

	set_aggressive(my_aggression);

	set_skill(SS_DEFENCE, 10);
	set_attack_unarmed(2,  5,  5, W_IMPALE, 50, "bite");

	set_hitloc_unarmed(1,  2, 50, "body");
	set_hitloc_unarmed(2,  1, 10, "left foreleg");
	set_hitloc_unarmed(4,  1, 10, "right foreleg");
	set_hitloc_unarmed(8,  1, 12, "left hindleg");
	set_hitloc_unarmed(16, 1, 12, "right hindleg");
	set_hitloc_unarmed(32, 1,  6, "head");
}

int
my_aggression()	// Doesn't attack hobgoblins.
{
	if (QRACE(TP) == "hobgoblin")
		return 0;

	return 1;
}
