#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <money.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>

#define A_RWING 0
#define A_LWING 1
#define A_BEAK 2
#define H_HEAD 0
#define H_BODY 1

public void
create_creature()
{
    set_name("chicken");
    set_living_name("_chicken_");
    set_short("little red hen");
    set_long("This is one of the farmer's chickens. It is "+
        "small and has reddish feathers.\n");
    add_name("hen");
    set_adj(({"little", "red"}));
    set_gender(G_FEMALE);
    default_config_creature(5);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_WEIGHT, 2500+random(2500));
    add_prop(CONT_I_VOLUME, 1500);
    add_prop(OBJ_M_HAS_MONEY, ({ 0, random(5), 0, 0}));
    set_skill(SS_UNARM_COMBAT, 5);
    set_skill(SS_DEFENCE, 5);
    set_attack_unarmed(A_BEAK, 10, 20, W_IMPALE, 30, "beak");
    set_attack_unarmed(A_LWING, 10, 20, W_BLUDGEON, 35, "left wing");
    set_attack_unarmed(A_RWING, 10, 20, W_BLUDGEON, 35, "right wing");
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");
    set_act_time(45);
    add_act("emote pecks at something on the floor.");
    add_act("emote flaps its wings.");
    add_act("emote clucks loudly.");
    add_act("peer all");
    remove_prop(OBJ_M_NO_GET);
}
