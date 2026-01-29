/* created by Aridor 06/19/93 */

#include <ss_types.h>
#include <macros.h>
#include "/sys/money.h"
#include "/d/Krynn/common/defs.h"

inherit M_FILE;
inherit AUTO_TEAM

string color = "green";

int ca1 = 1230;
int ca2 = 120;
int ca3 = 0;
int ca4 = 0;

set_color(string new_color)
{
    color = new_color;
}


#include "arm_me.h"

void
create_krynn_monster()
{
    int k, i, j = 2; /* j is the level */
    string str;

    set_pick_up("mercenary");

    set_name("mercenary");
    add_name("merc");
    add_name("human");
    set_race_name("human");
    set_adj("human");
    set_short("@@my_adjs@@ mercenary");
    add_prop(OBJ_I_COLORABLE, 1);

#include "level_me.h"

    set_long("A cruel and barbaric human from the northern lands of "+
    "Nordmaar, this mercenary seems to care for only himself. His "+
    "cold eyes gaze at you, seemingly calculating your worth. "+
    str+"\n");

    set_stats(({50,10,50,10,10,60}));
    set_skill(SS_DEFENCE, j * 8 + random(20));
    set_skill(SS_WEP_SWORD, j * 7 + random(20));
    set_skill(SS_WEP_KNIFE, j * 7 + random(20));
    set_skill(SS_WEP_CLUB, j * 7 + random(20));
    set_skill(SS_WEP_POLEARM, j * 7 + random(20));
    set_skill(SS_WEP_JAVELIN, j * 4 + random(20));
    set_skill(SS_WEP_AXE, j * 7 + random(20));

    MONEY_MAKE_PC(ca1)->move(TO,1);
    MONEY_MAKE_GC(ca2)->move(TO,1);
    MONEY_MAKE_SC(ca3)->move(TO,1);
    MONEY_MAKE_CC(ca4)->move(TO,1);


    k = query_average_stat();
    k = k*k/10;
    set_alignment(-k);
    set_knight_prestige(k);

    set_all_attack_unarmed(j * 2, j * 3);
    set_all_hitloc_unarmed(j * 2);

    start_patrol();
    set_patrol_time(30);
    set_patrol_path(({"n","n","s","s"}));



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
