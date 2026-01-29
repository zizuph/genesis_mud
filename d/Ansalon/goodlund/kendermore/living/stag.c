/* Stag in the forest outside of Kendermore, Gwyneth June 14, 1999 */

#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/act/domove";
inherit "/std/act/action";
inherit AC_FILE
inherit "/std/act/attack";

void
create_creature()
{
    set_name("stag");
    add_name("deer");
    set_race_name("stag");
    set_adj("proud");
    set_gender(G_MALE);
    set_long("This glorious animal looks to be in the prime of life by " + 
        "his enormous antlers. His fur is sleek and healthy looking, and " + 
        "he walks confidently.\n");

    set_stats(({50,50,50,6,6,50}));

    set_hp(4400);
    set_alignment(0);
    set_knight_prestige(0);

    NEVERKNOWN;

    set_attack_unarmed(1, 15, 10, W_BLUDGEON, 23, "left hoof");
    set_attack_unarmed(1, 15, 10, W_BLUDGEON, 23, "right hoof");
    set_attack_unarmed(2, 20, 8, W_IMPALE, 25, "antlers");

    set_hitloc_unarmed(1, 4, 80, "body");
    set_hitloc_unarmed(2, 3, 10, "head");

    set_random_move(20);
    set_restrain_path(KROOM);

    set_act_time(15);
    add_act("emote paces around.");
    add_act("emote looks at you with big brown eyes.");
    add_act("emote searches around for food.");

    set_cact_time(15);
    add_cact("emote lowers his antlers and charges.");
    add_cact("emote kicks out with his hooves.");
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " backs away slightly as you offer your " + 
        "gift.\n");
}
