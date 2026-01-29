/* modified by Milan 30.9.98 (added quiet_arm_me() and removed alarm ) */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
inherit AUTO_TEAM

string color = "green";
int level = 1;

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
    string str;
    int i, j = random(4)+1; /* j is the level of the goblin */
                            /* goblins have only 4 levels   */
    level = j;

    set_name("gob");
    set_race_name("goblin");
    add_prop(OBJ_I_COLORABLE, 1);
    add_prop(LIVE_I_NEVERKNOWN,1);

#include "level_me.h"

    set_adj("foul");

    set_long("This short and ugly creature is a goblin. Its mottled "+
    "black-green skin contrasts its dull yellow eyes. Wiry black hair "+
    "sprouts from its head, while dirty, black fangs poke out from "+
    "its rubbery lips. A foul stink seems to surround it. "+str+"\n");


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

    set_restrain_path(SCITY);
    set_random_move(5);

/* See quiet_arm_me above. Milan
    if (IS_CLONE)
        set_alarm(1.0,0.0,"arm_me", j);
*/
}

