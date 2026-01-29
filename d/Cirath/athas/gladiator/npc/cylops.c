/* cylops.c: The pet of the Overseers: Serpine, 5/6/95. */

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
#include <wa_types.h>
#include <const.h>
#include "defs.h"

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2
#define H_HEAD 0
#define H_BODY 1

create_creature() {
    set_short("large gray cilops");
    set_race_name("cilops"); 
    add_name("cylops");
    set_adj("large");
    add_adj("gray");

    set_long("Resembling a five meter long centipede, this cilops is "+
             "of the gray variety found in the Silt Sea. Its wicked "+
             "hooked legs are nothing compared to its meter long "+
             "prehensile antennae. Below its single huge compound "+
             "eye are three sets of mandibles. However, in spite of "+
             "its awesome weaponry, this beast seems downright docile, "+
             "serving peacefully as the guardian to the Overseer "+
             "Sanctum.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_gender(1);
    set_stats(({ 150, 150, 150, 5, 10, 100}));

    set_attack_unarmed(A_BITE,  100, 300, W_IMPALE, 60, "mandibles");
    set_attack_unarmed(A_LCLAW, 75, 150, W_SLASH,  20, "left antenna");
    set_attack_unarmed(A_RCLAW, 75, 150, W_SLASH,  20, "right antenna");

    set_hitloc_unarmed(H_HEAD, 80, 30, "head");
    set_hitloc_unarmed(H_BODY, 70, 70, "body");

    set_act_time(30);
    add_act("emote waves her antennae around.");
    add_act("emote catches an unsuspecting rat.");
    add_act("emote stretches.");
    add_act("emote starts walking along the wall.");
    add_act("emote attempts to walk on the ceiling but instead lands "+
            "on the table with a thud.");
    add_act("emote brushes you with her antennae.");
    add_act("emote pokes around in her nest.");
}
