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

    set_name("wolf");
    set_race_name("wolf");
    set_adj("white");
    add_adj("snow");
    set_pname("wolves");
    set_short("white snow wolf");
    set_pshort("white snow wolves");
    
    set_gender(2);
    set_long("It is an huge white wolf. It is very furry to "
          +  "withstand the cold high up in these mountains. Fort"
          +  "unately, there is no snow around now so you can distinguish "
          +  "the wolf clearly from the rocks.\n");

    set_stats(({ 30, 40, 60, 10, 10, 30}));

    set_hp(5000);
    set_alignment(-50);
    set_knight_prestige(50);

    NEVERKNOWN;

    set_skill(SS_DEFENCE, 20);
    set_attack_unarmed(1, 10, 10, W_SLASH,  25, "right claws");
    set_attack_unarmed(2, 30, 30, W_IMPALE, 50, "bite");
    set_attack_unarmed(4, 10, 8, W_BLUDGEON , 5, "left paw");

    set_hitloc_unarmed(1,  10, 50, "body");
    set_hitloc_unarmed(2,  10, 10, "left paw");
    set_hitloc_unarmed(4,  10, 10, "right paw");
    set_hitloc_unarmed(8,  10, 12, "left leg");
    set_hitloc_unarmed(16, 10, 12, "right leg");
    set_hitloc_unarmed(32,  5,  6, "head");


}

