/* Goblin, a small and stupid evil creature */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include QUESTH

inherit M_FILE

create_krynn_monster()
{
    int i;

    set_name("chef");
    set_long(BS(
	"This is the chef, he cooks all food for the prisoners. Since there " +
	"are many prisoners and he doesn't like to work they don't get fed " +
	"very often." +
	"", 75));
    set_race_name("goblin");
    set_adj("food");
    add_adj("stained");

    add_act("say Always cooking food :(");
    add_act("grin");
    add_act("moan");
    set_act_time(15);

    for (i = 0; i < 6; i++)
        set_base_stat(i, 15 + random(5));

    set_alignment(-130);
    set_knight_prestige(200);

    set_all_attack_unarmed(15, 10);
    set_all_hitloc_unarmed(5);

    NEVERKNOWN;


    seteuid(getuid(TO));

    if (IS_CLONE)
      set_alarm(1.0,0.0,"get_stuff");
}

get_stuff()
{
    clone_object(OBJ + "d_city13_key")->move(TO);
    clone_object(OBJ + "chef_apron")->move(TO);
    command("wear armour");
}


do_die(object killer)
{
    killer->add_prop(PLAYER_I_HELP_SALAMIC, killer->query_prop(PLAYER_I_HELP_SALAMIC) | 2);
    ::do_die(killer);
}
