/* created by Aridor 06/19/93
 * modified by Milan 30.9.98 (added quiet_arm_me() and removed alarm )
 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
inherit AUTO_TEAM

string color = "green";
int level;

set_color(string new_color)
{
    color = new_color;
}


#include "arm_me.h"

/* This is to be called after cloned and before moving into room
 * We get rid of all annoying messages to player and mercenary enters room equipped
 */
void
quiet_arm_me()
{
    arm_me(level);
}

void
create_krynn_monster()
{
    int k, i, j = random(6)+2; /* j is the level */
    string str;

    level = j;

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

    /*
	set_restrain_path(SCITY);
	set_random_move(7);
    */

    /* See quiet_arm_me above. Milan
	if (IS_CLONE)
	  set_alarm(1.0,0.0,"arm_me", j);
    */
}

string
my_adjs()
{
    return implode(query_adjs()," ");
}


