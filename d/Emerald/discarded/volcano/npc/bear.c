inherit "/std/creature";
inherit "/std/combat/unarmed";
#include "/d/Wiz/triana/defs.h"

#define W_BITE 0
#define W_CLAWS 1

void
create_creature()
{
	set_name("bear");
	set_adj("mean");
	add_adj("old");
	set_race_name("bear");
	set_short("bear");
	set_long("A mean, tough looking old bear.  It might not be wize to mess with him.\n");

	set_stats(({80, 43, 75, 12, 13, 65}));
	set_hp(query_max_hp());
	set_skill(SS_DEFENSE, 44); 
	set_skill(SS_UNARM_COMBAT, 38);
	add_prop(LIVE_I_SEE_DARK, 1);
	set_alignment(90);

	set_attack_unarmed(W_BITE, 20, 40, W_IMPALE, 70, "teeth");
	set_attack_unarmed(W_CLAWS, 15, 30, W_SLASH, 55, "claws");
	set_hitloc_unarmed(A_HEAD, 12, 8, "head");
	set_hitloc_unarmed(A_BODY, 15, 15, "body");
	set_hitloc_unarmed(A_LEGS, 5,4, "front legs");

}
