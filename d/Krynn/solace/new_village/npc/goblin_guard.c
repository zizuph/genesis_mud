/*
 * A goblin Seeker-guard
 *
 * by Rastlin
 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <macros.h>

inherit M_FILE

public string
goblin_long_desc(string str)
{
    return "He is one of the seeker guards and is dressed in a " +
           "crude uniform. Why does the High Theocrat use goblins to " +
	   "protect the village? He seems to strut with an air of " +
	   "self-importance, and he smells like rotting fish. " + str + "\n";
}

public void
create_krynn_monster()
{
    int i, level = random(4) + 1;

    set_color("red");

    set_race_name("goblin");

    set_name("guard");
    add_name("seeker guard");

    set_long(goblin_long_desc(query_level_desc(level)));

    set_adj(query_level_adj(level));

    for(i = 0; i < 6; i++)
        set_base_stat(i, level * 5 + random(10));      /*5-29*/

    set_skill(SS_DEFENCE, level * 4 + random(20));     /*4-35*/
    set_skill(SS_WEP_SWORD, level * 3 + random(20));   /*3-31*/
    set_skill(SS_WEP_KNIFE, level * 3 + random(20));   /*3-31*/
    set_skill(SS_WEP_CLUB, level * 3 + random(20));    /*3-31*/
    set_skill(SS_WEP_POLEARM, level * 3 + random(20)); /*3-31*/
    set_skill(SS_WEP_JAVELIN, level * 2 + random(20)); /*2-27*/
    set_skill(SS_WEP_AXE, level * 3 +random(20));      /*3-31*/

    i = query_average_stat();
    i = i*i/10;
    set_alignment(-i);
    set_knight_prestige(i);

    set_all_attack_unarmed(level * 2, level * 3);
    set_all_hitloc_unarmed(level * 2);

    set_cact_time(5);
    add_cact("say You utter fool!");
    add_cact("emote croaks: I will have you as dog meat.");
    add_cact("say You fight like my grand-mother, and she is dead.");
    add_cact("laugh evilly");
    add_cact("say What are you slime doing here in Solace?");

    set_random_move(2);

    if (IS_CLONE)
        set_alarm(0.5, 0.0, "npc_arm_me", level);

}

public string
query_nonmet_name()
{
    return ::query_nonmet_name() + " seeker-guard";
}







