/* /d/Terel/mountains/ghastly_keep/npc/g_blackbird.c
 *
 * An apparition in the ghastly keep
 *
 * Znagsnuf
 *
 * - Language tweak complete (Gorboth)
 */
inherit "/std/monster";
inherit "/std/combat/unarmed";

#include "defs.h"
#include <wa_types.h>
#include "../npc_stats.h";

/*
 * Function name: create_monster()
 * Description  : Constructor, redefine this to configure your monster
 */
void create_monster()
{
    seteuid(getuid());

    set_race_name("blackbird");
    set_name("bird");
    add_name("_ghastly_keep_npc");
    add_name("blackbird");

    add_adj("blackbird");

    set_short("blackbird");

    set_gender(G_MALE);

    set_long("His head is iridescent as a puddle of oil, and "
         + "his beak shines like polished orange amber as he moves "
         + "leaves and sticks around in his nest.\n");

    add_prop(LIVE_S_EXTRA_SHORT, ", is sitting in his nest");
    add_prop(CONT_I_WEIGHT, 1100);
    add_prop(CONT_I_HEIGHT, 10);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_stats (({ 30, 30, 30, 30, 30, 30}));

    set_hitloc_unarmed(1, 5, 15, "head");
    set_hitloc_unarmed(2, 5, 10, "right wing");
    set_hitloc_unarmed(3, 5, 10, "left wing");
    set_hitloc_unarmed(4, 5, 45, "body");
    set_hitloc_unarmed(5, 5, 20, "breast");

    /*               hit/pen           %% on usage per c-round */
    set_attack_unarmed(0, 5, 5, W_SLASH, 50, "small beak");
    set_attack_unarmed(1, 5, 5, W_SLASH, 50, "small claws");

    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    set_act_time(60);
    add_act("say pook-pook-pook!");
    add_act("say chink-chink!");
}
