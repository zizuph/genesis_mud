/*	A nasty flesh-eating ghoul, created by Guido.
	Added hitlocs by Anton 			*/

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Roke/common/defs.h"

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

void
create_creature()
{
    set_name("ghoul");
    set_living_name("_ghoul_");
    set_race_name("ghoul");
    set_adj(({"ugly", "flesh-eating"}));
    set_long(BSS(
        "This is one of the ugliest things you have ever seen,"+
        " the ghouls are eating on eachother, and you would not like "+
        "to become its next dinner!\n"));

    set_stats(({ 60, 55, 55, 55, 60, 75}));
	set_aggressive(1);

    set_hp(100000);

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);

    set_attack_unarmed(A_BITE, 65, 65, W_IMPALE, 20, "teeth");
    set_attack_unarmed(A_LCLAW, 65, 65, W_SLASH, 40, "left claw");
    set_attack_unarmed(A_RCLAW, 65, 65, W_SLASH, 40, "right claw");

	set_hitloc_unarmed(0, 40, 55, "body");
	set_hitloc_unarmed(1, 15, 15, "head");
	set_hitloc_unarmed(2, 15, 15, "legs");
	set_hitloc_unarmed(3, 15, 15, "arms");

    set_act_time(4);
    add_act("emote eats of the ghoul beside it.");
    add_act("emote swings his claws towards you.");

	add_prop(LIVE_I_SEE_DARK, 100);
	add_prop(LIVE_I_NO_CORPSE, 1);
	add_prop(NPC_I_NO_RUN_AWAY, 1);

}

public void attacked_by(object ob)
{
	object *obs;
int i;
	obs = all_inventory(environment());
		for (i=0; i<sizeof(obs); i++)
	if (obs[i] && obs[i]->id("ghoul"))
		obs[i]->attack_object(ob);
}
