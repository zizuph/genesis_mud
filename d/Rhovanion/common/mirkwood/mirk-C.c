#include "/d/Rhovanion/defs.h"
inherit MIRK_DIR+"mirkwood";
#include <stdproperties.h>

static object tree;

public void
create_map_room()
{
    set_short("On a clearing in the Mirkwood");
    set_long("@@my_long@@");
    add_std_exits();
    add_prop(ROOM_I_LIGHT, 1);
    if(!tree || !present(tree, TO))
    {
	seteuid(getuid());
	tree = clone_object(OBJ_DIR+"tree");
	tree->set_uptree_file(OBJ_DIR+"mirk_tour_uptree");
	tree->move(TO, 1);
    }
}

public nomask int
do_not_remove()
{
    return 1;  /*** do not remove this file (player may be on tree) ***/
}

public int
block_enter()
{
    if (TP->query_spider()) return 1;  /*** block spiders out of here ***/
    return 0;
}

public int
query_map_fatigue()
{
    return 3;
}

public string
my_long()
{
    string text, time = time_of_day();

    text = "You are on a clearing in the Mirkwood.";
    switch (time)
    {
	case "early morning":
	case "morning":
	    text += " Between the trees you can catch glimpses of the sky. "+
		    "It is "+time+" now. The darkness is still quite deep.";
	    break;
	case "noon":
	case "afternoon":
	    text += " The sun is shining, but the light can hardly "+
		    "penetrate the thick layer of leaves.";
	    break;
	case "evening":
	case "night":
	    text += " It is very dark here. The air has a bit more fresh "+
		    "scent here than in the forest.";
	    break;
    }
    return text+"\n";
}

