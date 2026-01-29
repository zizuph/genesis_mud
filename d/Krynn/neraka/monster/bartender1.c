/* Bartender 1, by Nick */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <money.h>
#include <macros.h>

inherit M_FILE

init_living()
{
    ADA("buy");
}

create_krynn_monster() 
{
    int i;

    set_name("bartender");
    set_adj("lazy");
    set_long("It looks like the bartender is sleeping at the bar.\n");
    set_race_name("bartender");

    for (i = 0; i < 6; i++)
        set_base_stat(i,80);

    set_alignment(-100);
    set_knight_prestige(400);
    set_gender(0);

    NEVERKNOWN;

    set_all_attack_unarmed(20, 43);
    set_all_hitloc_unarmed(32);

    MONEY_MAKE_SC(5 + random(10))->move(TO);
}

buy() 
{
    write("The bartender moans: Let me sleep.\n");
    say(QCTNAME(TP) + " tries to buy something.\n");
    return 1;
}
