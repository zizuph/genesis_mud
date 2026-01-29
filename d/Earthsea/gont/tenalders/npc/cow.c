#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

#define A_BUTT 0
#define A_LHORN 1
#define A_RHORN 2
#define H_HEAD 0
#define H_BODY 1

public void
create_creature()
{
    set_name("cow");
    add_name("holstein");
    set_race_name("cow");
    set_short("black and white milk cow");
    set_adj((({"black and white", "black", "white", "milk"})));
    set_long("This is a medium-sized black and white spotted "+
        "milk cow. It looks like a holstein.\n");
    set_gender(G_FEMALE);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_stats(({10, 10, 10, 5, 5, 35 }));
    set_skill(SS_DEFENCE, 15);
    set_skill(SS_UNARM_COMBAT, 25);
    set_attack_unarmed(A_BUTT, 10, 20, W_BLUDGEON, 20, "head");
    set_attack_unarmed(A_LHORN, 10, 20, W_IMPALE, 40, "left horn");
    set_attack_unarmed(A_RHORN, 10, 20, W_IMPALE, 40,"right horn");
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");
    set_act_time(80);
    add_act("emote looks at you gently with big brown eyes.");
    add_act("say Mooooo!");
    add_act("emote swings her tail to shoo away some flies.");
}
