inherit "/std/creature";
inherit "/std/combat/unarmed";
#include "/d/Wiz/triana/defs.h"

#define W_BITE 0
#define W_CLAWS 1

void
create_creature()
{
	set_name("wolf");
	set_adj("grey");
	add_adj("menacing");
	set_race_name("wolf");
	set_short("wolf");
	set_long("A large grey wolf. He looks like he has been in a few fights in his time.  His ears miss small chunks and there are patches where his fur does not grow due to scars.\n");

	set_stats(({50, 50, 43, 45, 48, 45}));
	set_hp(query_max_hp());
	set_skill(SS_DEFENSE, 44); 
	set_skill(SS_UNARM_COMBAT, 38);
	add_prop(LIVE_I_SEE_DARK, 1);
	set_alignment(90);

	set_attack_unarmed(W_BITE, 15, 30, W_IMPALE, 50, "sharp teeth");
	set_attack_unarmed(W_CLAWS, 10, 20, W_SLASH, 30, "sharp claws");
	set_hitloc_unarmed(A_HEAD, 12, 8, "head");
	set_hitloc_unarmed(A_BODY, 15, 15, "body");
	set_hitloc_unarmed(A_LEGS, 5,4, "front legs");

}
