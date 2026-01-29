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
    set_adj("silent");
    add_adj("black");

    set_gender(2);
    set_long("It is a silent black bat with leathery wings and a black head " +
	     "with small eyes and a huge nose and large ears. It is about " +
	     "the size of both your fists.\n");

    set_stats(({ 10, 100, 20, 2, 1, 30}));

    set_alignment(0);
    set_knight_prestige(0);

    NEVERKNOWN;

    set_skill(SS_BLIND_COMBAT, 100);
    set_attack_unarmed(1,  90, 5, W_IMPALE, 100, "bite");

    set_hitloc_unarmed(1,  ({30,30,30}), 30, "body");
    set_hitloc_unarmed(2,  ({22,41,42}), 32, "right wing");
    set_hitloc_unarmed(4,  ({22,41,42}), 32, "left wing");
    set_hitloc_unarmed(8,  ({21,37,21}),  6, "head");

    set_act_time(10);
    add_act("emote whooshes past your ear.");
    add_act("emote whooshes past your nose.");
    add_act("emote sends out a high pitched signal, sounding like 'mmmmap'.");
    add_act("emote sends out a high pitched signal, sounding like 'ttttthhhhiiiittthhh'.");
    add_act("emote sends out a high pitched signal, sounding like 'ttthhhhiiieppphhh'.");
    add_act("emote sends out a high pitched signal, sounding like 'aaaaaaarrrrrEEEa'.");
    add_act("emote sends out a high pitched signal, sounding like 'iiiiiin'.");
    add_act("emote sends out a high pitched signal, sounding like 'zzzzzennnnTerrrrr'.");

    add_leftover("/std/leftover","wing",2,"",0,0);
}

