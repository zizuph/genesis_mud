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

    set_name("bear");
    set_race_name("bear");
    set_adj("brown");
    add_adj("mountain");

    set_gender(2);
    set_long("It is an impressive brown bear. It is very furry to "
          +  "withstand the cold high up in these mountains. Fort"
          +  "unately, the bear appears very peaceful.\n");

    set_stats(({ 100, 70, 60, 20, 10, 100}));

    set_hp(5000);
    set_alignment(-50);
    set_knight_prestige(50);

    NEVERKNOWN;

    set_skill(SS_DEFENCE, 50);
    set_attack_unarmed(1, 40, 40, W_SLASH,  50, "right claws");
    set_attack_unarmed(2,   20, 20, W_IMPALE, 20, "bite");
    set_attack_unarmed(4, 30, 20, W_SLASH , 20, "left claws");
    set_attack_unarmed(8,  20, 10, W_SLASH , 10, "right hindleg");

    set_hitloc_unarmed(1,  20, 50, "body");
    set_hitloc_unarmed(2,  20, 10, "left paw");
    set_hitloc_unarmed(4,  20, 10, "right paw");
    set_hitloc_unarmed(8,  20, 12, "left leg");
    set_hitloc_unarmed(16,  20, 12, "right leg");
    set_hitloc_unarmed(32,  10,  6, "head");


}

