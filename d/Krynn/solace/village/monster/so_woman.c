#include "/d/Krynn/common/defs.h"

inherit M_FILE
#include <money.h>

create_krynn_monster()
{
    set_name("woman");
    set_adj("smiling");
    set_pshort("dark-haired smiling women");
    set_extra_long("It looks like she thinks she is beautiful.\n");
    set_race_name("human");
    set_adj("dark-haired");

    default_config_mobile(15);
    set_all_hitloc_unarmed(3);
    set_all_attack_unarmed(10, 7);
    set_knight_prestige(-1);
    set_alignment(120);

    set_gender(1);

    set_random_move(100);

    seteuid(getuid(TO));
    MONEY_MAKE_SC(20)->move(this_object());

}
