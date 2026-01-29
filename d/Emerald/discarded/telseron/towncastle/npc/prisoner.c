/* towncastle/npc/prisoner.c is cloned by towncastle/cell_2.c */
inherit "/std/monster";
 
#include "../default.h"
#include "/d/Emerald/lib/prestige.h"
 
void
create_monster()
{
    set_name("prisoner");
    set_race_name("prisoner");
    set_adj("pale");
    set_short("pale prisoner");
    set_long("He looks like he has been here for a long time.\n");
 
    set_stats(({ 15, 10, 5, 50, 60, 30 }));
    set_hp(query_max_hp());

    add_prop(CONT_I_VOLUME, 55000);
    add_prop(CONT_I_WEIGHT, 55000);
 
    add_chat("Don't leave me here!");
}
