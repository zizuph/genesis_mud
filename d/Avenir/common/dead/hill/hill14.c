// file name: hill14
// creator(s): Ilyian (28 August, 1995)
// last update:
// purpose:
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/dead";
#include "../dead.h"

public void
create_room()
{
    hill_long("The hill rises steeply to the west. To the "
      +"north and east, a sheer cliff drops straight "
      +"down.");

    AI(({"cliff","dropoff"}),"The hill ends abruptly to the "
      +"north, dropping straight down to the swampy "
      +"ground below. To the east, the cliff falls "
      +"down to the murky sea below. There is a tiny hole "
      +"just over the edge of the east cliff.\n");
    AI("hole","It is a tiny hole, blacker than night.\n");

    AI(({"sea","ocean","water"}),"The great dark sea spreads out "
      +"to the east as far as you can see. Its gentle waves lap "
      +"softly against the side of the cliff.\n");

    add_prop(OBJ_S_SEARCH_FUN, "search_me");

    ahup(HILL+"hill9","west");
    AE(HILL+"hill15","south",0,3);

    reset_room();
}

public void
reset_room()
{
    hill_reset();
}

#include "/d/Avenir/union/lib/bits.h"
#define LIST ("/d/Avenir/union/list")

string search_me(object player, string str)
{
    if (player->query_prop("found_it_yet") ||
	player->test_bit("Avenir", GUILD_GROUP, QUEST_BIT) ||
	!LIST->query_accepted(player->query_real_name()))
    {
	return "";
    }

    if (!parse_command(str, ({ }),
	    "[the] 'cliff' / 'rock' / 'hole' / 'ledge'"))
    {
	return "";
    }

    player->add_prop("found_it_yet", 1);
    object ob = clone_object(UNION+"obj/quest/sliver");
    ob->move(player, 1);

    return "You find "+LANG_ASHORT(ob)+" wedged into the tiny hole.\n";
}
