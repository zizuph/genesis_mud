/* Training room of Eil-Galaith
 * npc Dromadus will load in here
 * Created by Damaris 09/Y2K
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

    sk_add_train(SS_ANI_HANDL, "handle animals", 0, 0, 50);
    sk_add_train(SS_LOC_SENSE, "be aware of surroundings", 0, 0, 50);
    sk_add_train(SS_AWARENESS, "be more aware", 0, 0, 50);
    sk_add_train(SS_SWIM, "swimming", 0, 0, 50);
    sk_add_train(SS_CLIMB, "climbing", 0, 0, 50);

}

object meditate;

public void
create_guild_room()
{
    set_short("Eil-Galaith Training Hall");
    set_long("This is the Eil-Galaith Training hall. There "+
      "are a few tapestries along the walls. In here you may "+
      "increase your knowledge of a few skills. Dromadus is "+
      "eager to assist young and old alike in the ways of elven. "+
      "There is a small sign posted here as well.\n");
    add_item(({"tapestry", "tapestries"}),
      "The tapestries are made with vibrant silken threads. "+
      "Finely crafted with elven hands depicting elves in "+
      "battle scenes.\n");
    add_item(({"thread", "threads"}),
      "The silken threads which make of the tapestries are "+
      "vibrant and give depth to each tapestry.\n");
    add_item(({"training hall", "hall", "room"}),
      "This is the Eil-Galaith Training hall. There "+
      "are a few tapestries along the walls. In here you may "+
      "increase your knowledge of a few skills.\n");
    add_item(({"sign"}),
      "Members may <learn>, <improve> and <meditate> here.\n");
    add_cmd_item("sign","read","Members may <learn>, <improve> and <meditate> here.\n");

    add_exit("start", "east");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);  
    clone_here(NPC + "dromadus")->move(this_object());
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
