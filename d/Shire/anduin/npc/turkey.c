/*
 * Wild turkey
 * Coded by Finwe
 * June 2001
 */
 
#include "/d/Shire/sys/defs.h" 
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/sys/ss_types.h"

inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/combat/unarmed";
 
void
create_monster()
{
    set_race_name("turkey");
    set_short("wild turkey");
    set_long("This is a wild turkey. It is rather drab looking " +
        "with a bald red head and dark brown feathers.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_stats(25,5);
    set_skill(SS_DEFENCE, 5+random(10));
    set_skill(SS_PARRY, 10);

    set_m_in("flys in.");
    set_m_out("flys");
    set_random_move(5);

    set_gender(0);

    set_attack_unarmed(0,10,5,W_SLASH,50,"left wing");
    set_attack_unarmed(0,10,5,W_SLASH,50,"right wing");
    set_attack_unarmed(0,10,5,W_IMPALE,50,"beak");

    set_hitloc_unarmed(A_HEAD,20,30,"head");
    set_hitloc_unarmed(A_BODY,25,75,"body");
    set_hitloc_unarmed(A_L_ARM,30,40,"left claw");
    set_hitloc_unarmed(A_L_ARM,30,40,"right claw");
    set_hitloc_unarmed(A_L_ARM,30,60,"left leg");
    set_hitloc_unarmed(A_L_ARM,30,60,"right leg");
}
