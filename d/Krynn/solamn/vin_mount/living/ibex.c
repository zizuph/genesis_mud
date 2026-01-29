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

    set_name("ibex");
    set_race_name("ibex");
    set_adj("brown");
    add_adj("mountain");

    set_gender(2);
    set_long("It is a brown ibex with huge horns. It seems totally "
          +  "unaware of your presence.\n");

    set_stats(({ 20, 70, 30, 1, 1, 20}));

    set_hp(5000);
    set_alignment(5);
    set_knight_prestige(-5);

    NEVERKNOWN;

    set_attack_unarmed(1, 6, 22, W_SLASH,  50, "horns");
    set_attack_unarmed(2, 40, 5, W_IMPALE, 20, "bite");

    set_hitloc_unarmed(1,  4, 90, "body");
    set_hitloc_unarmed(2, 3, 10, "head");


}

