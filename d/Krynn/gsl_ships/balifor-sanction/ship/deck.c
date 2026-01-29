inherit "/d/Krynn/std/deck";
#include "local.h"
#include <stdproperties.h>

int block()
{
    int i;
    mixed team;
    if (this_player()->query_dragonarmy_occ_member())
	return 0;
    if (this_player()->query_pot_member())
        return 0;
    team = this_player()->query_team_others();
    for (i = 0; i < sizeof(team); i++)
	if (team[i]->query_dragonarmy_occ_member())
	    return 0;
    this_player()->catch_tell("Only dragonarmy soldiers and invited guests "+
				"are allowed to travel on the upper deck.\n");
    return 1;
}

void
create_deck()
{
    set_short("lower deck of a small courier vessel");
    set_long("This is the lower deck of a small courier vessel. It is very " +
        "dirty and smelling and uncomfortable for the travel. "+
        "There is a hatch leading down to a " +
        "cabin and stairs leading up to upper deck.\n");

    add_item(({"ship","vessel"}),
      "You stand on the lower deck of a small courier vessel.\n");
    add_item(({"deck", "lower deck"}),
      "The deck sways beneath your feet.\n");
    add_item(({"cabin","hatch"}),
      "A hatch leads down to a cabin below.\n");
    add_item(({"stairs","upper deck"}),
      "The stairs lead up to the upper deck. You can see from here that "+
      "the upper deck is clean and much more comfortable for the travel "+
      "than this deck.\n");

    add_exit(CABIN,"down",0);
    add_exit(UPPER,"up", block);

    set_deck_sound("@@sounds");
}


sounds()
{
    if (random(2))
	return "The ship sways with the wind.\n";
    return "The ship cuts through the waves.\n";
}

