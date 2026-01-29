/* Eil-Galaith Garden room
 * May train herbing skills here
 * npc Mateo will load in here
 * Created by Damaris 08/Y2K
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

    sk_add_train(SS_HERBALISM, "identify herbs", 0, 0, 50);
    sk_add_train(SS_TRACKING, "track", 0, 0, 50);
    sk_add_train(SS_LANGUAGE, "speak and understand languages", 0, 0, 60);

}

object meditate;

void
create_guild_room()
{

    set_short("Eil-Galaith Garden");
    set_long("You are standing in the garden of Eil-Galaith. There "+
      "are many plants and flowers growing here varying in size. "+
      "Vines cascade upwards and form walls with pink and white "+
      "blossoms. An air of mystery and magic permeates this garden. "+
      "You notice a small sign has been posted here.\n");
    add_item(({"garden", "room"}),
      "This garden is peaceful with many plants and flowers. The "+
      "bristle of life growing all around you provides this garden "+
      "with peace and sanctuary.\n");

    add_item(({"plants", "plant", "flower", "flowers"}),
      "There are a multitude of plants and flowers varying in size, "+
      "shape and colour.\n");

    add_item(({"blossom", "blossoms"}),
      "Many beautiful pink and white blossoms are scattered along "+
      "the vines. They are small in size but very fragrant.\n");

    add_item(({"wall", "walls"}),
      "The walls are created by the long vines that are intertwined with "+
      "each other and beautiful blossoms blanket them.\n");

    add_item(({"sign"}),
      "Members may <learn>, <improve> and <meditate> here.\n");
    add_cmd_item("sign","read","Members may <learn>, <improve> and <meditate> here.\n");


    add_exit("start", "south");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);  
    clone_here(NPC + "mateo")->move(this_object());
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
        write("You are not a member of " + GUILD_NAME + "!\n");

        SCROLLING_LOG(INFO_LOG, capitalize(player->query_real_name())+ 
          " attempted to train here. <--");

        return 1;
    }
}


