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

    set_name("eagle");
    set_race_name("eagle");
    set_adj("huge");
    add_adj("whitish");

    set_gender(2);
    set_long("It is an impressive eagle. Fort"
          +  "unately, it doesn't pay any attention to you. Better "
          +  "not draw any attention to you either.\n");

    set_stats(({ 50, 50, 90, 20, 10, 60}));

    set_hp(5000);
    set_alignment(50);
    set_knight_prestige(-150);

    NEVERKNOWN;

    set_attack_unarmed(1, 18, 33, W_SLASH,  45, "claws");
    set_attack_unarmed(2, 22, 26, W_IMPALE, 45, "beak");
    set_attack_unarmed(4, 17, 4, W_BLUDGEON, 5, "left wing");
    set_attack_unarmed(8, 17, 4, W_BLUDGEON, 5, "right wing");


    set_hitloc_unarmed(1,  10, 50, "body");
    set_hitloc_unarmed(2,  4, 10, "left wing");
    set_hitloc_unarmed(4,  4, 10, "right wing");
    set_hitloc_unarmed(8,  8, 12, "left leg");
    set_hitloc_unarmed(16,  8, 12, "right leg");
    set_hitloc_unarmed(32,  1,  6, "head");


}

