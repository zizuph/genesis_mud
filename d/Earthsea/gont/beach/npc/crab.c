/*
 * Crabs for the beach
 * Coded by Finwe
 * June 1997
 */

#pragma strict_types

inherit "/d/Earthsea/std/monster";

#include "default.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

public void
create_earthsea_monster()
{
    string color = ({"brown", "grey", "splotched", "red", "blue"})[random(5)],
        size = ({"large", "medium", "small"})[random(3)],
        type = ({"fiddler", "horseshoe", "common", "hermit"})[random(4)];

    add_adj(size);
    add_adj(color);
    add_adj(type);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("crab");
    set_short(size + " " + color + " " + type + " crab");
    set_long("A " + size + " " + color + " " + type + " "+
      "crab. These small creatures live on the sea shore, "+
      "and make their living from even smaller creatures.\n");

    set_stats(({ 3 + random(5), 4 + random(5), 5 + random(5),
        4+random(20), 10+random(5), 5}));
    set_skill(SS_DEFENCE, 5+random(10));
    set_skill(SS_PARRY, 10);

    set_m_in("scampers in");
    set_m_out("scampers");
    set_gender(0);
    set_random_move(5);
    set_restrain_path(BEACH);

    set_attack_unarmed(0,10,5,W_SLASH,50,"left claw");
    set_attack_unarmed(0,10,5,W_SLASH,50,"right claw");

    set_hitloc_unarmed(A_HEAD,20,30,"head");
    set_hitloc_unarmed(A_BODY,25,75,"body");
    set_hitloc_unarmed(A_L_ARM,30,40,"left claw");
    set_hitloc_unarmed(A_L_ARM,30,40,"right claw");
    set_hitloc_unarmed(A_L_ARM,30,60,"left leg");
    set_hitloc_unarmed(A_L_ARM,30,60,"right leg");

    set_act_time(90);
    add_act("emote tries to hide behind a rock.");
    add_act("emote bites your big toe.");
}
