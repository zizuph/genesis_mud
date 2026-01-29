/* Priest, by Nick */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <money.h>

inherit M_FILE

create_krynn_monster()
{
    int i;
    object money;

    set_name("rorak");
    set_adj("black");
    add_name("priest");
    set_living_name("rorak");
    set_short("black priest");
    set_long("He must be a servant of an evil God. This one doesn't look " +
	"very experienced.\n");
    set_race_name("human");

    for (i = 0; i < 6; i++)
        set_base_stat(i, 14 + random(10));
    set_skill(SS_DEFENCE, 20);
    set_knight_prestige(200);
    set_alignment(-100);

    set_all_hitloc_unarmed(19);
    set_all_attack_unarmed(16, 15);


    seteuid(getuid(TO));

    money = clone_object("/std/coins");
    money->set_name("coin");
    money->set_pname("coins");
    money->set_heap_size(random(200) + 100);
    money->set_typ(MONEY_TYPES[0]);
    money->move(TO);
}
