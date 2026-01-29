inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"


//   Prototypes
void tree1(object player);
void tree2(object player);
create_room()
{
    set_short("a garden");
    set_long(
	  "This is the southwest corner of Tom's garden. "
	+ "A huge oak tree spreads its branches towards the sky. "
	+ "To the north is the entrance, "
	+ "and to the east is an open spot in the garden.\n");

    add_item(({"oak","tree", "oak tree", "huge oak tree"}), 
    "The huge oak tree spreads its branches over a big part of the "
	+ "garden. This tree is Tom Bombadil's pride and joy. "
	+ "It looks even older than he himself. You might be able to "
	+ "reach the its lowest branches.\n",);

    add_exit(DOWNS_DIR + "tomg1", "north");
    add_exit(DOWNS_DIR + "tomg", "east");
}

init()
{
    ::init();
    add_action( "do_climb", "climb");
    add_action( "do_reach", "reach");
}

do_climb(str)
{
    if (str == "tree" || str == "oak" || str == "oak tree")
    {
	write("You jump, and barely manage to grab a hold of the treetrunk.\n");
        set_alarm(3.0,0.0,&tree1(this_player()));
	return 1;
    }
}

do_reach(str)
{
    string tmp;

    if (!str) return 0;
    if (sscanf(str,"for %s", tmp)) str = tmp;

    if (str == "branches" || str == "tree" || str == "branch")
    {
	write("You cannot reach the branches from the ground, try something else.\n");
	return 1;
    }
}

void
tree1(object player)
{
    player->catch_msg("You lose your grip on the treetrunk, and fall...\n");
    set_alarm(6.0,0.0,&tree2(player));
}

void
tree2(object player)
{
    player->catch_msg("Luckily you manage to cling to the lowest branch, and climb up...\n");
    player->move_living("up into the old oak", DOWNS_DIR + "oak1");
}
