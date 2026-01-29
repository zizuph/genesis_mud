/* created by Aridor 06/19/93 */
/* OOPS, wrong filename :), there are NO orcs in Krynn...
 * this is really a hobgoblin, not an orc...
 */

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
    int i, j = random(3)+1; /* j is the level of the hobgoblin   */
                            /* Hobgoblins can have level 1,2 or 3 */
    string str;

    set_pick_up_team(({"hobgob","goblin","ogre"}));

    set_name("hobgob");
    set_race_name("hobgoblin");
    //set_living_name("hobgob");
    add_prop(OBJ_I_COLORABLE, 1);

#include "level_me.h"

    set_adj("smelly");

    set_long(BS("This hobgoblin smells like he has never seen water in "
         +   "his entire life. " + str, SL));


    for(i=0; i<6; i++)
        set_base_stat(i, j * 10 + random(20));     /*10-49*/
    set_skill(SS_DEFENCE,     j * 8 + random(20));  /*8-43*/
    set_skill(SS_WEP_SWORD,   j * 7 + random(20));  /*7-40*/
    set_skill(SS_WEP_KNIFE,   j * 7 + random(20));  /*7-40*/
    set_skill(SS_WEP_CLUB,    j * 7 + random(20));  /*7-40*/
    set_skill(SS_WEP_POLEARM, j * 7 + random(20));  /*7-40*/
    set_skill(SS_WEP_AXE,     j * 7 + random(20));  /*7-40*/

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
