inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <ss_types.h>;
#include <wa_types.h>;
#include <stdproperties.h>;
#include <macros.h>;

#define A_BITE 0
#define A_TALONS 1

#define H_HEAD 0
#define H_BODY 1
#define H_LWING 2
#define H_RWING 3

void
create_creature()
{
    if (!IS_CLONE)
	return;

    set_name("eagle");
    add_name("mother eagle");
    
    add_prop(LIVE_I_NEVERKNOWN,1);
    set_race_name("eagle");
    set_adj("large");
    set_long("An adult eagle, protecting her young.  "+
	"She has a large beak, and viscious looking talons, making "+
    "her an effective guardian.\n");

    set_stats(({35,40,38,20,20,20}));

    set_skill(SS_DEFENCE,20);

    set_hp(10000);


    set_gender(1);
    set_attack_unarmed(A_BITE,20,15,W_SLASH,70,"beak");
    set_attack_unarmed(A_TALONS,15,15,W_SLASH,30,"talons");

    set_hitloc_unarmed(H_BODY,1,10,"head");
    set_hitloc_unarmed(H_HEAD,1,60,"body");
    set_hitloc_unarmed(H_LWING,5,15,"left wing");
    set_hitloc_unarmed(H_RWING,5,15,"right wing");

    add_prop(CONT_I_WEIGHT,30000);
    add_prop(CONT_I_VOLUME,30000);

}
