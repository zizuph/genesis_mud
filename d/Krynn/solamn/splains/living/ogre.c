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
    int i, j = random(3)+3; /* j is the level of the ogre */
    string str;

    set_name("ogre");
    set_race_name("ogre");
    add_prop(OBJ_I_COLORABLE, 1);

#include "level_me.h"

    set_adj("giant");

    set_long(BS("This ogre looks like a giant. " + str, SL));


    for(i=0; i<6; i++)
        set_base_stat(i, j * 10 + random(20));
    set_skill(SS_DEFENCE, j * 8 + random(20));
    set_skill(SS_WEP_SWORD, j * 7 + random(20));
    set_skill(SS_WEP_KNIFE, j * 7 + random(20));
    set_skill(SS_WEP_CLUB, j * 7 + random(20));
    set_skill(SS_WEP_POLEARM, j * 7 + random(20));
    set_skill(SS_WEP_AXE, j * 7 + random(20));

    i = query_average_stat();
    i = i*i/10;
    set_alignment(-i);
    set_knight_prestige(i);

    set_all_attack_unarmed(j * 2, j * 3);
    set_all_hitloc_unarmed(j * 2);


    if (IS_CLONE)
      set_alarm(1.0,0.0,"arm_me", j);

}

