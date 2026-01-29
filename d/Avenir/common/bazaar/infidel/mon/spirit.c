
// Spirits to help Nahquatil
// creator(s): Ilyian, May 1995
// purpose:
// note:
// bug(s):
// to-do:

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/domove";
inherit "/std/act/action";

#include "/d/Avenir/common/common.h"
#include <formulas.h>
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/sys/ss_types.h"
#include "/sys/macros.h"

#define A_SOMETHING 0

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

void
create_creature()
{

        set_name("spirit");
        add_name("avenir_spirit_id");
        set_race_name("spirit");
        set_gender(G_NEUTER);
        set_adj("white");

        set_long("This vague outline of a spirit shimmers in "+
                "the light.\n");

        set_stats(({ 10+random(20), 20+random(20), 20+random(30),
                     10+random(10), 50+random(10), 10+random(30) }));

        set_skill(SS_DEFENCE, 60 + random (30));
        set_skill(SS_AWARENESS, 87);
        set_skill(SS_UNARM_COMBAT, 60 + random (30));
        set_skill(SS_BLIND_COMBAT, 100 );

        add_prop(LIVE_I_NO_CORPSE, 1);
        add_prop(LIVE_I_SEE_DARK, 10);
        add_prop(LIVE_I_QUICKNESS, 95);
        add_prop(LIVE_I_SEE_INVIS, 10);
        add_prop(LIVE_I_UNDEAD, 3);
        add_prop(OBJ_I_INVIS, 2);
        add_prop(NPC_I_NO_RUN_AWAY, 1);
        add_prop(LIVE_I_NEVERKNOWN, 1);
        add_prop(OBJ_I_RES_FIRE, 20 + random(10));

        set_attack_unarmed(A_SOMETHING,35,25,W_BLUDGEON,100,"translucent something");

        set_hitloc_unarmed(H_HEAD, 35, 10,"upper region");
        set_hitloc_unarmed(H_BODY, 60, 60,"middle");
        set_hitloc_unarmed(H_LEGS, 40, 30,"lower region");


}

