#pragma strict_types
 
#include "/d/Gondor/defs.h"
#include "../mirk_defs.h"
inherit  "/d/Gondor/common/mirkwood/forest/mirkwood";
#include <stdproperties.h>

static string Dirs_edge;
static string Dirs_forest;

public void
create_map_room()
{
    add_std_exits();

    Dirs_edge = desc_map_dirs(get_map_dirs("E"));
    Dirs_forest = desc_map_dirs(get_map_dirs("x"));

    set_short("Edge of the Mirkwood forest");
    set_long("@@my_long@@");

    add_prop(ROOM_I_LIGHT, 1);
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

    text = "You have reached the edge of the Mirkwood forest.";
    if(Dirs_forest != "")
        text += " The forest itself spreads further " + Dirs_forest +
                " from here.";
    if(Dirs_edge != "")
        text += " The edge of the forest continues " + Dirs_edge + ".";
    return text+"\n";
}

