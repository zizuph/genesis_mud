inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define A_BITE 0
#define A_TALONS 1

#define H_HEAD 0
#define H_BODY 1
#define H_LWING 2
#define H_RWING 3

void create_creature() {
    if (!IS_CLONE)
	return;

    set_name("eagle");
    add_name("large eagle");
    
    add_prop(LIVE_I_NEVERKNOWN,1);
    set_race_name("eagle");
    set_adj("strong");
    set_long(break_string("An enormous eagle, that looks a formidable "+
        "opponent.  It eyes you carefully as you look at it.\n",75));

    set_stats(({50,55,53,25,25,40}));

    set_skill(SS_DEFENCE,35);

    set_hp(10000);


    set_gender(0);
    set_attack_unarmed(A_BITE,25,20,W_SLASH,70,"beak");
    set_attack_unarmed(A_TALONS,18,18,W_SLASH,30,"talons");

    set_hitloc_unarmed(H_BODY,1,10,"head");
    set_hitloc_unarmed(H_HEAD,1,60,"body");
    set_hitloc_unarmed(H_LWING,5,15,"left wing");
    set_hitloc_unarmed(H_RWING,5,15,"right wing");

    add_prop(CONT_I_WEIGHT,45000);
    add_prop(CONT_I_VOLUME,50000);

}
