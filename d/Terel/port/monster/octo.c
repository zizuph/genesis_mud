/*
 * A terrible octopus
 */

inherit "/std/creature";

inherit "/std/combat/unarmed";
inherit "/std/act/seqaction";
inherit "/std/act/attack";

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include <wa_types.h>
#include <ss_types.h>

#define TO       this_object()
#define TP       this_player()

create_creature()
{
    if (!IS_CLONE) return;
    
    set_name("octopus");
    set_long("It's a giant white octopus. It looks very hungry.\n");
    set_adj("white");
    add_adj("giant");
    set_race_name("octopus");
    set_stats(({90, 90, 90, 50, 50, 90}));
    set_hp(9999);
    set_mana(9999);
    set_gender(2);
    set_aggressive(1);

    set_skill(SS_DEFENCE, 80 + random(10));
    set_skill(SS_PARRY, 80 + random(10));
    set_skill(SS_AWARENESS, 80 + random(10));

    add_prop(OBJ_I_WEIGHT, 300000);
    add_prop(OBJ_I_VOLUME, 250000);
    add_prop(CONT_I_MAX_WEIGHT, 350000);
    add_prop(CONT_I_MAX_VOLUME, 300000);
}


#define H_HEAD 0
#define H_EYE 1
#define H_ARMS 2

public void
cr_configure()
{
    add_attack(35, 85, W_BLUDGEON, 100, A_ARMS);

    add_hitloc( ({34,34,34}), 15, "head", H_HEAD);
    add_hitloc( ({1,1,1}),     5, "eyes", H_EYE);
    add_hitloc( ({72,72,72}), 80, "arms", H_ARMS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_ARMS:return "arms";
    }
}
