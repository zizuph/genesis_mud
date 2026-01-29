/* created by Aridor 10/12/93 */


#include "../local.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>

inherit C_FILE


void
create_creature()
{
    int i;

    set_name("marmot");
    set_race_name("marmot");
    set_adj("little");
    add_adj("brown");

    set_gender(2);
    set_long("It is a small brown marmot. It is furry to "
          +  "withstand the cold high up in these mountains. "
          +  "The marmot appears very peaceful.\n");

    set_stats(({ 10, 40, 20, 2, 1, 10}));

    set_hp(5000);
    set_alignment(0);
    set_knight_prestige(0);

    NEVERKNOWN;

    set_skill(SS_DEFENCE, 1);
    set_attack_unarmed(2,   5, 5, W_IMPALE, 50, "bite");

    set_hitloc_unarmed(1,  2, 50, "body");
    set_hitloc_unarmed(2,  1, 10, "left foreleg");
    set_hitloc_unarmed(4,  1, 10, "right foreleg");
    set_hitloc_unarmed(8,  1, 12, "left hindleg");
    set_hitloc_unarmed(16, 1, 12, "right hindleg");
    set_hitloc_unarmed(32, 1,  6, "head");


}

