/* Sarr */
#include "defs.h"
inherit STD_MONSTER;
inherit "/d/Raumdor/lib/intro";

void
create_monster()
{
    ::create_monster();
    set_name("athos");
    add_name("librarian");
    set_race_name("human");
    set_adj("sharp");
    add_adj("blue-eyed");
    set_short("sharp blue-eyed librarian");
    set_long("He walks around, shelving books, writing notes, and doing "+
    "other various librarian duties. His cold blue eyes show much wisdom "+
    "and knowledge behind them.\n");
    set_stats(({40,50,60,90,90,50}));
    set_skill(SS_DEFENCE,30);
    set_title("the Librarian of Drakmere");
    equip(DRAKMERE_ARM_DIR + "l_robe");
}

void
do_die(object who)
{
    who->inc_prop(IS_ENEMY_OF_DRAKMERE,1);
    ::do_die(who);
}
