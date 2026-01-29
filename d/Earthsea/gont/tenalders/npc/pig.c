#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#define A_BUTT 0
#define SNOUT 1
#define HOOF 2
#define H_HEAD 0
#define H_BODY 1

public void
create_creature()
{
    set_name("sow");
    add_name("pig");
    set_race_name("pig");
    set_short("huge fat sow");
    set_adj(({"huge", "fat"}));
    set_long("This female pig is huge and fat.\n");
    set_gender(G_FEMALE);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_stats(({10, 10, 10, 5, 5, 35 }));
    set_skill(SS_DEFENCE, 15);
    set_skill(SS_UNARM_COMBAT, 25);
    set_attack_unarmed(A_BUTT, 10, 20, W_BLUDGEON, 25, "head");
    set_attack_unarmed(SNOUT, 10, 20, W_BLUDGEON, "pig snout");
    set_attack_unarmed(HOOF, 10, 20, W_BLUDGEON, "hoof");
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");
    set_act_time(80);
    add_act("emote wallows in the dirt.");
    add_act("emote squeals loudly.");
    add_act("snort");
    add_act("emote eyes you with its little piggy eyes.");
}
