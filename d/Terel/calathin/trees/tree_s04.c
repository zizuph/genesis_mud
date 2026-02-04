// tree_s04.c
// This is a tree on the path that runs behind the 
// townhouses toward the West Gate. Using the same
// base room (path_s00) since this is bascially a 
// room above that path. 
// Lilith Mar 2022

#include "/d/Terel/include/Terel.h"
inherit CALATHIN_DIR + "paths/path_s00";

#include <tasks.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>

#define  UP   CALATHIN_DIR + "trees/tree_s04b"
#define  DOWN CALATHIN_DIR + "paths/path_s04"
#define  BELOW ({ DOWN })
#define  DIFFICULTY  (TASK_ROUTINE + 200)  /* 27 avg gives 50% success */
#define  DAMAGE      25              

public object *
get_view(string *arr)
{
    object *inv = ({});

    foreach(string path: arr)
    {
	object room = find_object(path);
	if (objectp(room))
	    inv += all_inventory(room);
    }

    if (sizeof(inv))
	inv = FILTER_CAN_SEE(FILTER_LIVE(inv), this_player());

    return inv;
}

public string 
see_down(void)
{
    object *live = get_view(BELOW);

    if (!sizeof(live))
	return "you can see that the path below is empty.";

    return "you can see "+ COMPOSITE_LIVE(live) +" standing on "+
    "the path beneath your tree. ";
}

public void
create_terel_room()
{
    set_short("up in a tree");
    set_long("You are in a pine tree above the path that follows "+
      "along the forest edge. "+
      "Silvery-green branches surround you, blocking much of "+
      "the wind. "+
      "The tree branches obscure most of the view, but "+
      "@@see_down@@"+
      "This seems as good a place as any to rest for a while.\n");

    add_exit(DOWN, "down");

    add_item(({"tree", "branch", "trunk" }), "It is a pretty silver pine tree.\n");

    add_cmd_item(
      ({"tree", "up tree", "branch", "to branch", "up to branch", 
	"up to next branch", "to next branch", "up tree trunk", 
	"trunk", "tree trunk", "up trunk" }),
      ({"climb", "jump", "leap", "parkour"}),
      "@@climb_tree");

    /* inherited from path_s00 */
    add_here();
    add_intree();
    add_town();
    add_buildings();

}


/* Borrowed from the routine in the big silver pine for consistency */
int
climb_tree()
{

    int success;

    success = TP->resolve_task(DIFFICULTY,
      ({ SKILL_WEIGHT, 600, SS_CLIMB,
	SKILL_WEIGHT, 150, SS_DEX }) );

    if (success < 0)
    {
	write("You try to climb up the tree but you can't seem " +
	  "to get a good grip. Your feet slip on the icy branch you "+
	  "are balancing on and down you go!\n");
	say(QCTNAME(TP) + " tries to climb up the tree, but falls.\n");
	TP->reduce_hit_point(DAMAGE);
	TP->move_living("falling, screaming, downwards", DOWN);
	return 1;
    }

    write("You grab onto a branch above and heave yourself up.\n");
    TP->move_living("climbing upwards", UP);
    return 1;

}