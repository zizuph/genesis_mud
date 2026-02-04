#pragma strict_types
#pragma save_binary

#include "../include/guild.h"
#include "/d/Terel/include/Terel.h"

inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include <ss_types.h>

inherit STDROOM;
 
public void
set_up_skills()
{
    create_skill_raise();

    sk_add_train(SS_MOUNTED_COMBAT, "fight while on horseback", 0, 0, 50);
    sk_add_train(SS_WEP_SWORD, "fight with a sword", 0, 0, 50);
    sk_add_train(SS_PARRY, "parry attacks", 0, 0, 50);
    sk_add_train(SS_TRACKING, "track", 0, 0, 50);
    sk_add_train(SS_DEFENCE, "defend yourself", 0, 0, 50);
    sk_add_train(SS_ANI_HANDL, "handle animals", 0, 0, 50);
    sk_add_train(SS_LOC_SENSE, "be aware of surroundings", 0, 0, 50);
    sk_add_train(SS_RIDING, "ride a steed", 0, 0, 50);
    sk_add_train(SS_AWARENESS, "be more aware", 0, 0, 50);
//    sk_add_train(SS_SPECIAL, "special attack", 0, 0, 100);
}

object meditate;

public void
create_room()
{
    set_short("Riders Training Area");
    set_long("This is the Riders of Last training area. " +
       "You notice several people engaged in various " +
       "activities. Some are fighting others with sword " +
       "while on horseback, others are studying the ground " +
       "for tracks. You see a small sign nailed " +
       "to the fencepost.\n");

    add_item("sign","The sign is nailed to the fence post. You can read it.\n");
    add_cmd_item("sign","read","Members may learn and meditate here.\n");
 
 
    create_guild_support();
    set_up_skills();
}
 
public void
init()
{
    ::init();
    init_guild_support();
    init_skill_raise();
    add_action("do_improve","improve");
    add_action("do_improve","learn");

}

int
do_improve(string str)
{
    object player = this_player();

    if (!IS_MEMBER(player) && !player->query_wiz_level())
    {
        write("Only Riders of Last are allowed to train here.\n");


        SCROLLING_LOG(RIDER_INFO_LOG, capitalize(player->query_real_name())+ 
          " attempted to train here. <--");

     return 1;
    }
}
