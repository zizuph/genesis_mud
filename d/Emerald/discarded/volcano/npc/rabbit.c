inherit "/std/creature";
inherit "/std/combat/unarmed";
#include "/d/Wiz/triana/defs.h"

#define W_BITE 0

void
create_creature()
{
	set_name("rabbit");
	set_adj("small");
	add_adj("brown");
	set_race_name("rabbit");
	set_short("rabbit");
	set_long("A cute furry little rabbit.\n");

	set_stats(({7, 7, 8, 3, 3, 9}));
	set_hp(query_max_hp());
	set_skill(SS_DEFENSE, 44); 
	set_skill(SS_UNARM_COMBAT, 38);
	add_prop(LIVE_I_SEE_DARK, 1);
	set_alignment(90);

	set_attack_unarmed(W_BITE, 2, 4, "scratches you with his nails", 50);
	set_hitloc_unarmed(A_HEAD, 12, 8, "head");
	set_hitloc_unarmed(A_BODY, 15, 15, "body");
	set_hitloc_unarmed(A_LEGS, 5,4, "front legs");

}
