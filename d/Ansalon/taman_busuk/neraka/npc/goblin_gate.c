/* created by Aridor 06/19/93 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/sys/money.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
inherit AUTO_TEAM

string color = "green";

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

    set_pick_up_team(({"goblin"}));
    
    set_name("gob");
    set_race_name("goblin");
    add_prop(OBJ_I_COLORABLE, 1);
    add_prop(LIVE_I_NEVERKNOWN,1);

#include "level_me.h"

    set_adj("burly");

    set_long("This short and ugly creature is a goblin. Its mottled "+
    "puke-green skin contrasts its dull yellow eyes. Wiry black hair "+
    "sprouds from its head, while dirty, black fangs poke out from "+
    "its rubery lips. A foul stink seems to surround it. "+str+"\n");


    for(i=0; i<6; i++)
        set_base_stat(i, j * 5 + random(30));      /*5-29*/
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
    trig_new("%w %w 'Open.\n'","react_open");
    trig_new("%w %w 'Open\n'","react_open");
    trig_new("%w %w 'open.\n'","react_open");
    trig_new("%w %w 'open\n'","react_open");

    if (IS_CLONE)
        set_alarm(1.0,0.0,"arm_me", j);

}

void
react_open(string str1, string str2)
{
    object who;
    who = present(lower_case(str1),E(TO));
    set_alarm(2.0,0.0,"door_open",who);
}

void
door_open(object who)
{
    if(who->query_guild_name_occ() == "P of Takhisis")
    {
        command("say Yes, your Holiness!");
        command("grovel "+lower_case(who->query_name()));
        command("open gate");
        set_alarm(6.0,0.0,"close_gate");
    }
    else
    {
        command("say Get out of here, fool!");
    }
}

void
close_gate()
{
    command("close gate");
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
