// tree_s03b.c
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

#define  DOWN   CALATHIN_DIR + "trees/tree_s03"
#define  SPATH  ({ CALATHIN_DIR + "paths/path_s03" })
#define  BELOW  ({ DOWN })

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
    object *live = get_view(SPATH);

    if (!sizeof(live))
	return "you can see that the path below is empty.";

    return "you can see "+ COMPOSITE_LIVE(live) +" standing on "+
    "the path beneath your tree. ";
}


public string 
see_tree(void)
{
    object *live = get_view(BELOW);

    if (!sizeof(live))
	return "";

    return "Directly below, you can see "+ COMPOSITE_LIVE(live) +
    " on a lower branch. ";
}


public void
create_terel_room()
{
    set_short("high up in a tree");
    set_long("You are high up in a pine tree above a path "+
      "along the forest edge. "+ 
      "It is cold here, but sheltered from the wind. "+
      "The air smells strongly of woodsmoke and pine. "+
      "The snow-covered tree branches obscure much of the "+
      "view, but @@see_down@@@@see_tree@@\n");

    add_exit(DOWN, "down");

    /* inherited from path_s00 */
    add_intree();
    add_here();
    add_town();
    add_buildings();
}

int
climb_act(string str)
{
    write("You can't find a way to climb any higher.\n");
    return 1;
}

public void
init()
{
    ::init();

    add_action(climb_act, "climb");
}
