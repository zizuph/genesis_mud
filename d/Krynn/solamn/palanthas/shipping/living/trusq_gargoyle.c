/* 
 * Mortis 02.2006
 *
 * Gargoyle protecting the ledge outside the master suite
 * of the merchant house Trusq.
 *
 * Possible leftover can be made into dagger in Arms district?
 * Learn about creature armour.
 */

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "../../local.h"

inherit C_FILE
inherit "/std/act/attack";

void
create_creature()
{
	string adj1 = one_of_list(({"hunched", "gray-skinned", "marble-skinned",
	"black-clawed"}));
	string adj2 = one_of_list(({"wingless", "large-eyed", "great-winged"}));

    set_name("gargoyle");
    set_race_name("gargoyle");
    set_adj(adj1);
    add_adj(adj2);
    set_gender(G_NEUTER);
	set_short(adj1 + " " + adj2 + " gargoyle");
    
	set_m_in("stands up from its hunched crouch atop the roof");

	add_prop(LIVE_I_NEVERKNOWN, 1);
	set_aggressive(1);

	set_alignment(0);
	set_knight_prestige(-1);
    
	if (adj2 == "great-winged")
	{
		set_long("Even hunched, this stoney skinned gargoyle is still nearly "
		+ "eight feet tall with great, veined wings ending in long, piercing "
		+ "claws.  Its spindly arms and legs are rock hard with dark, "
		+ "sculpted muscle and end in sharp, curved, black claws.  A wide "
		+ "maw filled with twisted marble teeth opens from ear to ear in its "
		+ "long face, and its glowing, solid yellow eyes glare out from "
		+ "their large, round sockets with focused intensity at you.\n");

		set_stats(({95, 77, 115, 40, 100, 120}), 3);

		set_skill(SS_DEFENCE, 60);
		set_attack_unarmed(1, 10, 10, W_IMPALE,  25, "clawed wings");
		set_attack_unarmed(2, 30, 30, W_SLASH, 50, "claws");
		set_attack_unarmed(4, 10, 8, W_BLUDGEON , 5, "stone-like backhand");
		
		set_hitloc_unarmed(1,  10, 50, "body");
		set_hitloc_unarmed(2,  10, 10, "left paw");
		set_hitloc_unarmed(4,  10, 10, "right paw");
		set_hitloc_unarmed(8,  10, 12, "left leg");
		set_hitloc_unarmed(16, 10, 12, "right leg");
		set_hitloc_unarmed(32,  5,  6, "head");
	}

	else
	{
		set_long("Hunching slightly, this stoney skinned gargoyle is nearly "
		+ "six feet tall with spindly arms and legs ending in curved, black "
		+ "claws, a long spiked tail, and a marbled pot belly.  A wide maw "
		+ "filled with short, jagged marble teeth opens from ear to ear in "
		+ "its long face, and its glowing, solid yellow eyes glare out at "
		+ "you from their large, round sockets.\n");

		set_stats(({70, 48, 90, 30, 60, 100}), 9);

		set_skill(SS_DEFENCE, 60);
		set_attack_unarmed(1, 10, 10, W_IMPALE,  25, "long spiked tail");
		set_attack_unarmed(2, 30, 30, W_SLASH, 50, "claws");
		set_attack_unarmed(4, 10, 8, W_BLUDGEON , 5, "stone-like backhand");
		
		set_hitloc_unarmed(1,  10, 50, "body");
		set_hitloc_unarmed(2,  10, 10, "left paw");
		set_hitloc_unarmed(4,  10, 10, "right paw");
		set_hitloc_unarmed(8,  10, 12, "left leg");
		set_hitloc_unarmed(16, 10, 12, "right leg");
		set_hitloc_unarmed(32,  5,  6, "head");
	}
    
}

