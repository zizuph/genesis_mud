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

    set_name("leopard");
    set_race_name("leopard");
    if (random(1))
      set_adj("black");
    else
      set_adj("checkered");
    add_adj("mountain");

    set_gender(2);
    set_long("It is an impressive leopard. It is very furry to "
          +  "withstand the cold high up in these mountains. Fort"
          +  "unately, the leopard appears uninterested in you.\n");

    set_stats(({ 50, 120, 60, 10, 10, 50}));

    set_hp(5000);
    set_alignment(-10);
    set_knight_prestige(10);

    NEVERKNOWN;

    set_skill(SS_DEFENCE, 50);
    set_attack_unarmed(1, 20, 10, W_SLASH,  50, "right paw");
    set_attack_unarmed(2, 10, 20, W_IMPALE, 20, "bite");
    set_attack_unarmed(4, 20, 10, W_SLASH , 20, "left paw");

    set_hitloc_unarmed(1,  6, 48, "body");
    set_hitloc_unarmed(2,  4, 10, "left foreleg");
    set_hitloc_unarmed(4,  4, 10, "right foreleg");
    set_hitloc_unarmed(8,  4, 12, "left hindleg");
    set_hitloc_unarmed(16, 4, 12, "right hindleg");
    set_hitloc_unarmed(64,  1,  2, "tail");
    set_hitloc_unarmed(32, 2,  6, "head");


}

