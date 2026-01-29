/* created by Aridor 03/03/94 */

#include "../local.h"

inherit C_FILE
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>


void
create_creature()
{
    int i;

    set_name("bat");
    set_race_name("bat");
    set_adj("giant");
    add_adj("black");

    set_gender(2);
    set_long("It is a giant black bat with leathery wings and a black head " +
	     "with small eyes and a huge nose and large ears. It is about " +
	     "the size of a your head.\n");

    set_stats(({ 20, 130, 50, 2, 1, 50}));

    set_alignment(0);
    set_knight_prestige(0);

    NEVERKNOWN;

    set_skill(SS_BLIND_COMBAT, 100);
    set_attack_unarmed(1,  90, 8, W_IMPALE, 100, "bite");

    set_hitloc_unarmed(1,  ({40,40,40}), 30, "body");
    set_hitloc_unarmed(2,  ({32,51,52}), 32, "right wing");
    set_hitloc_unarmed(4,  ({32,51,52}), 32, "left wing");
    set_hitloc_unarmed(8,  ({31,47,31}),  6, "head");

    set_act_time(10);
    add_act("emote whooshes past your ear.");
    add_act("emote whooshes past your head.");

    add_leftover("/std/leftover","wing",2,"",0,0);
}

