/* created by Aridor 06/19/93 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/sys/money.h"

inherit M_FILE
inherit AUTO_TEAM

string color = "blue";

void
set_color(string new_color)
{
    color = new_color;
}

#include "arm_me.h"

void
create_krynn_monster()
{
    int i, j = random(4)+1; /* j is the level of the goblin */
                            /* goblins have only 4 levels   */

    string str;

    set_pick_up_team(({"hobgoblin","goblin"}));
    
    set_name("gob");
    set_race_name("goblin");
    add_prop(OBJ_I_COLORABLE, 1);

#include "level_me.h"

    set_adj("greedy");

    set_long(BS("This goblin is a soldier in the dragonarmy. " + str, SL));


    for(i=0; i<6; i++)
        set_base_stat(i, j * 5 + random(10));      /*5-29*/
    set_skill(SS_DEFENCE, j * 4 + random(20));     /*4-35*/
    set_skill(SS_WEP_SWORD, j * 3 + random(20));   /*3-31*/
    set_skill(SS_WEP_KNIFE, j * 3 + random(20));   /*3-31*/
    set_skill(SS_WEP_CLUB, j * 3 + random(20));    /*3-31*/
    set_skill(SS_WEP_POLEARM, j * 3 + random(20)); /*3-31*/
    set_skill(SS_WEP_JAVELIN, j * 2 + random(20)); /*2-27*/
    set_skill(SS_WEP_AXE, j * 3 +random(20));      /*3-31*/

    i = query_average_stat();
    i = i*i/10;
    set_alignment(-i);
    set_knight_prestige(i);

    set_all_attack_unarmed(j * 2, j * 3);
    set_all_hitloc_unarmed(j * 2);


    if (IS_CLONE)
      set_alarm(1.0,0.0,"arm_me", j);

}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
