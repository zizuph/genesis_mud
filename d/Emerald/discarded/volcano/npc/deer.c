inherit "/std/creature";
inherit "/std/combat/unarmed";
#include "/d/Wiz/triana/defs.h"

#define W_BITE 0
#define W_CLAWS 1

void
create_creature()
{
	set_name("deer");
	set_adj("brown");
	add_adj("spotted");
	set_race_name("deer");
	set_short("deer");
	set_long("A large graceful buck.\n");

	set_stats(({16, 29, 9, 10, 15, 14}));
	set_hp(query_max_hp());
	set_skill(SS_DEFENSE, 44); 
	set_skill(SS_UNARM_COMBAT, 38);
	add_prop(LIVE_I_SEE_DARK, 1);
	set_alignment(90);

	set_attack_unarmed(W_BITE, 5, 10, W_BLUDGEON, 50, "kicks you with his hooves");
	set_attack_unarmed(W_CLAWS, 9, 18, W_IMPALE, 20, "sharp antlers");
	set_hitloc_unarmed(A_HEAD, 12, 8, "head");
	set_hitloc_unarmed(A_BODY, 15, 15, "body");
	set_hitloc_unarmed(A_LEGS, 5,4, "front legs");

}
