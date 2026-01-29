#include "/d/Shire/old_forest/defs.h"
inherit OLD_FOR_DIR+"old_forest";
#include <stdproperties.h>

static string Dirs_edge;
static string Dirs_hedge;
static string Dirs_forest;
static string Dirs_river;

public void
create_map_room()
{
    add_std_exits();

    Dirs_edge = desc_map_dirs(get_map_dirs("E"));
    Dirs_hedge = desc_map_dirs(get_map_dirs("H"));
    Dirs_forest = desc_map_dirs(get_map_dirs("x"));
    Dirs_river = desc_map_dirs(get_map_dirs("R"));

    set_short("Edge of the "+FOREST_NAME+"");
    set_long("@@my_long@@");

    add_prop(ROOM_I_LIGHT, 1);
}

public int
block_enter()
{
    if (this_player()->query_spider()) return 1;  /*** block spiders out of here ***/
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

    text = "You have reached the edge of the "+FOREST_NAME+".";
    if(Dirs_forest != "")
        text += " The forest itself spreads further " + Dirs_forest +
                " from here.";
    if(Dirs_edge != "")
        text += " The edge of the forest continues " + Dirs_edge + ".";
    if(Dirs_river != "")
        text += " The Brandywine runs " + Dirs_river + " from " +
            "here.";
    return text+"\n";
}

