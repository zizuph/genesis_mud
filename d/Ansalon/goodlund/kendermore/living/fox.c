/* Wandering fox in Kendermore, Gwyneth, June 12, 1999 */

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
    set_name("this_fox");
    add_name("fox");
    set_race_name("fox");
    set_adj("sleek");
    add_adj("red");
    set_gender(G_FEMALE);
    set_long("Clever, intelligent eyes look back at you. Some kender must " +
        "have taken a liking to this wild animal, since foxes don't usually " + 
        "frequent cities. It looks happy and well-fed, though.\n"); 

    set_stats(({23,23,23,16,16,17}));

    set_hp(2400);
    set_alignment(0);
    set_knight_prestige(-5);

    NEVERKNOWN;

    set_act_time(15);
    add_act("emote yaps at you.");
    add_act("emote paces around.");
    add_act("emote curls up in a warm spot to take a brief nap.");

    set_cact_time(15);
    add_cact("emote yaps fiercely.");
    add_cact("emote bares her teeth.");

    set_attack_unarmed(1, 15, 10, W_BLUDGEON, 25, "left paw");
    set_attack_unarmed(1, 15, 10, W_BLUDGEON, 25, "right paw");
    set_attack_unarmed(2, 20, 8, W_IMPALE, 20, "teeth");

    set_hitloc_unarmed(1, 4, 80, "body");
    set_hitloc_unarmed(2, 3, 10, "head");

    set_random_move(20);
    set_restrain_path(KROOM);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(CONT_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(CONT_I_VOLUME, 400);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " backs away slightly from your " + 
        "outstretched hand.\n");
}
