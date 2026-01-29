/* created by Aridor 06/19/93 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/sys/money.h"


inherit M_FILE


string color = "blue";

set_color(string new_color)
{
    color = new_color;
}

#include "arm_me.h"

void
create_krynn_monster()
{
    int i, j = random(5)+1; /* j is the level of the bandit */
    string str;

    set_name("bandit");
    set_race_name("human");
    add_prop(OBJ_I_COLORABLE, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

#include "level_me.h"
    
    set_short(query_adj(0) + " bandit");
    set_long("This human has been hired by the dragonarmy. " + str + "\n");


    for(i=0; i<6; i++)
        set_base_stat(i, j * 10 + random(20));
    set_skill(SS_DEFENCE, j * 8 + random(20));
    set_skill(SS_WEP_SWORD, j * 7 + random(20));
    set_skill(SS_WEP_KNIFE, j * 7 + random(20));
    set_skill(SS_WEP_CLUB, j * 7 + random(20));
    set_skill(SS_WEP_POLEARM, j * 7 + random(20));
    set_skill(SS_WEP_AXE, j * 7 +random(20));

    i = query_average_stat();
    i = i*i/10;
    set_alignment(-i);
    set_knight_prestige(i);

    set_all_attack_unarmed(j * 2, j * 3);
    set_all_hitloc_unarmed(j * 2);


    if (IS_CLONE)
        set_alarm(1.0,0.0,"arm_me", j);

}


