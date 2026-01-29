// file name:    Millipede
// creator(s):   Cirion, April 1996
// last update:
// purpose:      Newbie Monster
// note:         Icky bug for the newbie area
// bug(s):
// to-do: 
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "../outpath.h"

#define A_TEETH      0
#define A_LEG        1

#define H_HEAD       0
#define H_THORAX     1
#define H_LEGS       2
#define H_TAIL       3

void create_creature()
{
    string *adjs = ({ "ugly", "hideous", "many-legged", "sharp-jawed",
                      "revolting", "sickly" });

    set_name("millipede");
    add_name("insect");
    set_race_name("millipede");

    set_adj( adjs[random(sizeof(adjs))] );
    set_gender(G_NEUTER);

    set_long("It is a very long and grotesque creature with "
            +"hundreds of legs. Its sharp mandibles click together "
            +"nervously.\n");

    set_stats(({ 8, 10, 15, 1, 1, 20 }));

    set_skill(SS_UNARM_COMBAT,  10);
    set_skill(SS_DEFENCE,        5);
    set_skill(SS_AWARENESS,     50);

    set_alignment(0);

    set_attack_unarmed(A_TEETH, 8, 8, W_IMPALE, 40, "mandibles");
    set_attack_unarmed(A_LEG, 2, 2, W_BLUDGEON, 60, "tiny legs");

    set_hitloc_unarmed(H_HEAD,   ({ 10, 10, 2 }), 5,   "head");
    set_hitloc_unarmed(H_THORAX, ({ 2, 2, 8 }),   50,  "body");
    set_hitloc_unarmed(H_LEGS,   ({ 5, 5, 5 }),   15,  "legs");
    set_hitloc_unarmed(H_TAIL,   ({ 10, 10, 10 }), 30, "tail");

    add_prop(CONT_I_WEIGHT, 5);
    add_prop(CONT_I_VOLUME, 25);
    add_prop(CONT_I_HEIGHT, 5); // 5 cm tall :)

    add_prop(LIVE_I_SEE_DARK,    2);
    add_prop(LIVE_I_NEVERKNOWN,  1);
    add_prop(NPC_I_NO_LOOKS,     1);

    add_leftover("/std/leftover", "leg", -1, 0, 0, 0);
    add_leftover("/std/leftover", "tail", 1, 0, 1, 0);
    add_leftover("/std/leftover", "mandible", 2, 0, 1, 0);

    set_act_time(10);
     add_act("emote clicks its mandibles together.");

    set_cact_time(10);
     add_cact("emote clicks its mandibles together.");
     add_cact("jump");
}
