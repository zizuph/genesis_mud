/*
 */

inherit "/d/Ansalon/guild/pot/obj/living/npc";

#include <const.h>

void
create_pot_monster()
{
    set_name("terwed");
    set_race_name("human");
    set_adj("dark-eyed");
    add_adj("slender");
    
    set_stats(({ 40, 40, 40, 50, 50, 30 }));
    set_gender(G_MALE);
}
