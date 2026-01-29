#include "/d/Krynn/common/defs.h"

inherit M_FILE

create_krynn_monster()
{
    set_name("kid");
    set_short("kid is playing on the road");
    set_pshort("kids are playing on the road");
    set_long("It looks like he enjoys himself.\n");
    set_race_name("human");

    default_config_mobile(7);
    set_all_hitloc_unarmed(5);
    set_all_attack_unarmed(7, 8);
    set_knight_prestige(-1);
    set_alignment(80);

}
