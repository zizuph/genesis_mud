/* created by Aridor 06/19/93 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/sys/money.h"

inherit M_FILE
inherit AUTO_TEAM

string color = "blue";

set_color(string new_color)
{
    color = new_color;
}


#include "arm_me.h"

void
create_krynn_monster()
{
    int k, i, j = random(6)+2; /* j is the level */
    string str;

    set_pick_up_team(({"mercenary"}));

    set_name("mercenary");
    add_name("merc");
    add_name("human");
    set_race_name("human");
    set_adj("human");
    set_short("@@my_adjs@@ mercenary");
    add_prop(OBJ_I_COLORABLE, 1);

#include "level_me.h"

    set_long(BS("This is a mercenary in the dragon army. It seems his "
          +  "money is hard-earned. " + str, SL));


    for(i=0; i<6; i++)
        set_base_stat(i, j * 10 + random(20));
    set_skill(SS_DEFENCE, j * 8 + random(20));
    set_skill(SS_WEP_SWORD, j * 7 + random(20));
    set_skill(SS_WEP_KNIFE, j * 7 + random(20));
    set_skill(SS_WEP_CLUB, j * 7 + random(20));
    set_skill(SS_WEP_POLEARM, j * 7 + random(20));
    set_skill(SS_WEP_JAVELIN, j * 4 + random(20));
    set_skill(SS_WEP_AXE, j * 7 + random(20));

    k = query_average_stat();
    k = k*k/10;
    set_alignment(-k);
    set_knight_prestige(k);

    set_all_attack_unarmed(j * 2, j * 3);
    set_all_hitloc_unarmed(j * 2);


    if (IS_CLONE)
      set_alarm(1.0,0.0,"arm_me", j);

}

string
my_adjs()
{
    return implode(query_adjs()," ");
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
