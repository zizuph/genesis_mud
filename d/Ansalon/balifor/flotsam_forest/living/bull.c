/* created by Aridor 10/12/93 */


#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>

inherit AC_FILE
inherit "/std/act/attack";


void
create_creature()
{
    int i;

    set_name("bull");
    set_race_name("bull");
    set_adj("brown");

    set_gender(0);
    set_long("It is a big brown bull. It seems enraged that " +
      "you are in its paddock!\n");

    set_stats(({40,50,40,1,1,90}));

    set_hp(5000);
    set_alignment(0);
    set_knight_prestige(0);
    set_aggressive(1);

    NEVERKNOWN;

    set_attack_unarmed(1, 6, 22, W_SLASH,  50, "horns");
    set_attack_unarmed(2, 40, 5, W_IMPALE, 20, "bite");

    set_hitloc_unarmed(1,  4, 90, "body");
    set_hitloc_unarmed(2, 3, 10, "head");


}

