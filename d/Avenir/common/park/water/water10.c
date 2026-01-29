// Underwater room beneath the fountain
// under the park
//  -Cirion, Jan 1996

inherit "/d/Avenir/inherit/water";
#include "/d/Avenir/common/common.h"

public void
create_room()
{
    underwater_room();

    set_short("dead end");
    set_long("The rocky tunnel around you is dark and "
      +"shadowy in the gloom, and the water "
      +"weighs down on you like a menacing hand. You have "
      +"reached a dead end at a solid wall of rock. The "
      +"only way back is to the southwest.\n");

    add_item(({"wall", "walls", "rock"}),"The rocky walls "
      +"around you are rough and unhewn, implying "
      +"that this passage is naturally formed. A small crevice "
      +"runs along the rock face.\n");    
    add_item(({"crevice", "crack"}),"It is a dark crevice, leading into "
      +"blackness and gloom.\n");

    add_prop(OBJ_S_SEARCH_FUN, "search_me");

    add_prop(ROOM_I_LIGHT, -4);
    IN_IN;

    add_exit(PK + "water/water9", "southwest");
}

#include "/d/Avenir/union/lib/bits.h"
#define LIST ("/d/Avenir/union/list")

public string
search_me(object player, string str)
{
    if (player->query_prop("found_it_yet") ||
	player->test_bit("Avenir", GUILD_GROUP, QUEST_BIT) ||
	!LIST->query_accepted(player->query_real_name()))
    {
	return "";
    }

    if (!parse_command(str, ({ }),
	"[the] 'cliff' / 'rock' / 'crack' / 'crevice'"))
    {
	return "";
    }

    player->add_prop("found_it_yet", 1);
    object ob = clone_object(UNION+"obj/quest/ring");
    ob->move(player, 1);

    return "You find "+LANG_ASHORT(ob)+" wedged into the crevice.\n";
}
