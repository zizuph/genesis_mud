/* Sleepy human, by Nick */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <ss_types.h>

inherit M_FILE

create_krynn_monster()
{
    int i;
    set_name("sleepy");
    set_short("sleepy human");
    set_adj("sleepy");
    set_long("He falls asleep leaning against the table.\n");
    set_race_name("human");

    for (i = 0; i < 6; i++)
	set_base_stat(i, 5 + random(20));
    set_skill(SS_DEFENCE, 10);

    set_all_hitloc_unarmed(3);
    set_all_attack_unarmed(10, 6);

}
