
#pragma strict_types

inherit "/d/Genesis/ship/captain";

#include <ss_types.h>




public void
create_captain()
{
    set_name("Londo");
    add_name("captain");
    set_living_name("Londo");
    set_race_name("human");
    add_adj("arrogant");
    add_adj("proud");


    set_stats(({ 120, 180, 120, 180, 150, 190 }));
    set_skill(SS_SWIM, 100);
    set_title("the Emperor of the seas");
    set_ticket("/d/Faerun/ships/route1/ticket");
    set_price(24);
    refresh_mobile();

}
