/*
 * campwarrior.c
 *
 * Used in wild/fd.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 *
 * Updated and moved into new camp by Treacher, Aug 2021
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <ss_types.h>
#include <macros.h>

#define ANT_ARMOURS 6

void
create_monster()
{
    int i;

    set_name("warrior");
    set_long("He's a warrior from the evil island Golbar.\n");
    set_race_name("human");
    set_alignment(-25);
    NEVERKNOWN;

}

int
query_knight_prestige()
{
    return 500;
}

/*
 * Setup the warrior according to level
 * 1 - Base stats around 40, skillevels 35-45, 1 wep + 1 arm
 * 2 - Base stats around 55, skillevels 45-55, 1 wep + 1 arm
 * 3 - Base stats around 70, skillevels 55-65, 1 wep + 2 arm
 */
void
set_me_up(int level)
{
    seteuid(getuid(this_object()));

    object arm, arm2, wep;
    int i, tmp, tmp2;
    int base = 35;
    string *adjs = ({"ugly", "strong", "fierce"});
    int *wep_skills = ({SS_WEP_SWORD, SS_WEP_AXE, SS_WEP_KNIFE, SS_WEP_POLEARM, SS_WEP_CLUB });
    
    if(level < 1 || level > 3)
    {
        level = 1;
    }

    set_adj(adjs[level-1]);
    set_short(adjs[level-1] + " warrior");
    set_skill(SS_DEFENCE, base + level*10);
    set_skill(SS_PARRY, base + level*10);
    for (i = 0; i < sizeof(wep_skills); i++)
        set_skill(wep_skills[i], base + (level-1)*10);

    default_config_npc(base + 5 + (level-1)*15);

    tmp = (2 + random(6)) / 2;
    wep = clone_object(CAMP_WEP + "weapon2");
    wep->set_up(tmp);
    wep->move(this_object());

    tmp = (2 + random(6)) / 2;
    arm = clone_object(CAMP_ARM + "armour2");
    arm->set_up(tmp);
    arm->move(this_object());
    if(level == 3)
    {
        while(arm2 == 0 || arm2->query_at() == arm->query_at())
        {
            tmp2 = (2 + random(6)) / 2;
            arm2 = clone_object(CAMP_ARM + "armour2");
            arm2->set_up(tmp2);
        }
       
        arm2->move(this_object());
    }

    clone_object(CAMP_ARM + "leather-bracelet")->move(TO);

    command("wear all");
    command("wield weapon");
}
