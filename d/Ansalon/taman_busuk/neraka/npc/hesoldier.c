/* Ashlar, 5 May 97  - half-elf soldier */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/sys/money.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
inherit AUTO_TEAM

string color = "green";
int level;

set_color(string new_color)
{
    color = new_color;
}

void
set_colour(string c)
{
    set_color(c);
}

int
query_level() { return level; }

#include "arm_me.h"

void
create_krynn_monster()
{
    int k, i, j = random(5)+2; /* j is the level */
    string str;

    level = j;
    set_pick_up_team(({"mercenary"}));

    set_name("soldier");
    add_name("half-elf");
    set_race_name("half-elf");
    set_adj("half-elf");
    set_short("@@my_adjs@@ soldier");
    add_prop(OBJ_I_COLORABLE, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

#include "level_me.h"

    set_long("This is a regular soldier of the dragonarmy. He is " +
        "clean-shaven and looks more disciplined than his mercenary " +
        "counterpart. @@query_player_al@@ " + str + "\n");

    for(i=0; i<6; i++)
        set_base_stat(i, j * 10 + random(20));
    set_skill(SS_DEFENCE, j * 8 + random(20));
    set_skill(SS_PARRY, j * 8 + random(20));
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

}


string
query_player_al()
{
    if(TP->query_guild_name_occ() == "Solamnian Knights")
        return "The soldier eyes you angrily, seeming on the verge to attack you.";
    if(TP->query_alignment() > 200)
        return "The soldier studies you carefully.";
    return "The soldier glances quickly at you, then ignores you.";
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

/*
 * Function name: help_friend
 * Description:   Help a teammate in trouble by attacking someone
 * Arguments:     ob - the object to attack
 */
public void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        command("grin");
        command("kill " + lower_case(ob->query_real_name()));
    }
}
