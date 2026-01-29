/* File         : /d/Khalakhor/guilds/racial/clans/room/train.c
 * Creator      : Tomas@Genesis
 * Copyright:   : Bryan D.
 * Date         : March, 13 2001         
 * Purpose      : training facility to the default Clans of Khalakhor Guildhome
 * Related Files: /
 * Comments     : This is the training facility to the default Clansmen guildhome.
 * Modifications: 
 */
#pragma strict_types

#include "../guild.h"
#include <ss_types.h>
#include <stdproperties.h>
inherit GUILD_ROOM;
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

public void
set_up_skills()
{
    create_skill_raise();

    sk_add_train(SS_APPR_OBJ, "appraise objects", 0, 0, 50);
    sk_add_train(SS_APPR_VAL, "appraise valueable items", 0, 0, 50);
    sk_add_train(SS_TRADING, "trading", 0, 0, 50);
    sk_add_train(SS_AWARENESS, "be more aware", 0, 0, 50);
    sk_add_train(SS_SWIM, "swimming", 0, 0, 50);
    sk_add_train(SS_CLIMB, "climbing", 0, 0, 50);
    sk_add_train(SS_LOC_SENSE, "maintain your bearings", 0, 0, 50);

}

object meditate;

public void
create_guild_room()
{
    set_short("Clans of Khalakhor Training Room");
    set_long("This is the Clans of Khalakhor Training " +
       "room. You notice a sign nailed to the wall before you.\n");

    add_item(({"training hall", "hall", "room"}),
      "This is the Eil-Galaith Training hall. There "+
      "are a few tapestries along the walls. In here you may "+
      "increase your knowledge of a few skills.\n");
    add_item(({"sign"}),
      "Members may <learn>, <improve> and <meditate> here.\n");
    add_cmd_item("sign","read","Members may <learn>, <improve> and <meditate> here.\n");

    add_exit("start", "south");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);  
 //   clone_here(NPC + "dromadus")->move(this_object());
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


    if (!this_player()->query_guild_member(GUILD_NAME) &&
      !this_player()->query_wiz_level())
    {
        write("You are not a member of this guild!\n");

        SCROLLING_LOG(INFO_LOG, capitalize(player->query_real_name())+ 
          " attempted to train here. <--");

        return 1;
    }
}
