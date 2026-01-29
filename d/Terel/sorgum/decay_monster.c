inherit "/std/creature";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#define TO this_object()
#define TP this_player()

create_creature()
{
     if (!IS_CLONE) return;
     set_name("decay-monster");
     set_short("decay monster");
     set_long("Long description not finished yet...\n");
     set_race_name("decay monster");
     set_alignment(-100);
     set_aggressive(1);
     set_hp(7000);
     set_mana(7000);
     set_fatigue(7000);
     set_gender(0);
     add_prop(LIVE_I_SEE_DARK,1);

     set_skill(SS_CLIMB, random(50) + 25);
     set_skill(SS_DEFENCE, random(25) + 25);
     set_skill(SS_BLIND_COMBAT, random(10) + 70);
     set_skill(SS_UNARM_COMBAT, random(10) + 70);
     set_skill(SS_AWARENESS, random(10) + 40);
     add_prop("_sorgum_foo_prop_", 1);
     add_prop(CONT_I_WEIGHT, 700000);
     add_prop(CONT_I_VOLUME, 700000);
     add_prop(CONT_I_MAX_WEIGHT, 800000);
     add_prop(CONT_I_MAX_VOLUME, 800000);
     set_whimpy(0);
}

#define A_BITE 0

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id)
{
     mixed hres;
     
     hres = ::hit_me(wcpen, dt, attacker, attack_id);
     say("Calling specialized hit_me\n");
     return hres;
}
