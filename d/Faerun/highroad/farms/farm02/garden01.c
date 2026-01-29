/*
 * Farm flower garden
 * By Finwe, October 2006
 */
 
#pragma strict_types
 
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit BASE_GARDEN;
inherit BASE_COMMON;
/*
#define WALL_IDENT   9358106724 
#define WALL_RANGE   5          
*/

#define MIN_TRACKING    30 
#define MIN_AWARENESS   30

#define WALL_ACTION     ({ "climb", "kick", "smash", "push", "bash", "hit", "shove" })
#define WALL_SEARCHED   "_wall_searched"
#define WALL_CRACKS     "_wall_found_cracks"
#define MAX_PATHS       8

// how to get past wall
string wall_howto = ONE_OF_LIST(WALL_ACTION), path_file;
int num_of_paths;
int query_num_of_paths();

int reset_paths();

void
create_garden_room()
{
    set_short("A large flower garden");
    add_prop(ROOM_S_MAP_FILE, "farm_w_map.txt");

    set_extraline("A gravel path passes by large flower beds. Bees dart " +
        "from the lush flowers. The stone wall that surrounds the garden " +
        "is partially hidden by flowers growing over it. The large " +
        "farmhouse dominates the southern side of the garden.\n");

    remove_item("wall");
    add_item(({"wall", "stone wall"}),
        "@@wall_desc");
    add_item("cracks",
        "The cracks run throughout the wall. They have weakened " +
        "the wall, making it unstable.\n");
    add_item(({"farmhouse", "house"}),
        "The farmhouse is large and surrounded flowerbeds. It is whitewashed " +
        "and sits at the southern edge of the garden.\n");

    reset_room();

    add_exit(FARM2_DIR + "garden02", "east");
    add_exit(FARM2_DIR + "kitchen", "south");
    
    add_prop(OBJ_S_SEARCH_FUN, "do_search");


}


void reset_room()
{
    ::reset_room();
    reset_paths();
}

int reset_paths()
{
    num_of_paths = random(MAX_PATHS);

    while(num_of_paths == 0)
    {
        num_of_paths = random(MAX_PATHS);
    }

// sets paths file
    switch(num_of_paths)
    {
        case 1:
        {
            path_file = "pt01_01"; 
            break;
        }
        case 2:
        {
            path_file = "pt02_01"; 
            break;
        }
        case 3:
        {
            path_file = "pt03_01"; 
            break;
        }
        case 4:
        {
            path_file = "pt04_01"; 
            break;
        }
        case 5:
        {
            path_file = "pt05_01"; 
            break;
        }
        case 6:
        {
            path_file = "pt06_01"; 
            break;
        }
        case 7:
        {
            path_file = "pt07_01"; 
            break;
        }
        case 8:
        {
            path_file = "pt08_01"; 
            break;
        }
    }
    

}

/*
 * search routine to find entrance in bushes
 */
mixed do_search(object searcher, string str)
{
    int awareness, tracking;

    awareness = searcher->query_skill(SS_AWARENESS);
    tracking  = searcher->query_skill(SS_TRACKING);
    if (awareness >= MIN_AWARENESS && tracking >= MIN_TRACKING)
    {
// have they searched the wall?
        if(str=="wall" || str =="stone wall")
        {
            TP->add_prop(WALL_SEARCHED,1);
            return "You find some cracks in the wall.\n";
        }
        if(str=="cracks" || str == "horizontal cracks");
        {
            remove_item("wall");
            remove_item("cracks");
            add_item(({"wall", "stone wall"}),
                "@@wall_desc");
            add_item(({"cracks"}),
                "They run everywhere through the wall. There are gaps between the cracks. It looks like you can probably " + wall_howto + " the wall.\n");

            TP->add_prop(WALL_CRACKS,1);
            return "They run everywhere through the wall. There are gaps between the cracks. It looks like you can probably " + wall_howto + " the wall.\n";
        }

    }
    return 0;
}

string wall_desc()
{
    string str;

    str = "It is about waist high and made of flat stones piled on top " +
        "of each other.";

    
    if(TP->query_prop(WALL_SEARCHED))
    {
        str +=  " There are visible cracks through the wall, which make it " +
            "weak and unstable. ";
    }
    
    if(TP->query_prop(WALL_CRACKS))
    {
        str += "The cracks run everywhere through the wall with gaps " +
            "between them. It looks like you can probably " + 
            wall_howto + " the wall.";
    }
    return str + "\n";
}

void
init()
{
    ::init();

    add_action("move_wall", wall_howto );
}

int move_wall(string str)
{
    if(str == "wall" || str == "stone wall")
    {
        write("You " + wall_howto + " the wall.\n");
        write("The wall collapses before you, opening up to the north.\n");
        write("You climb over the rubble and head to the north.\n");
        say(QCTNAME(TP)+" climbs over the wall.\n");
        tell_room(FARM2_DIR + "path01",QCTNAME(TP) + " arrives.\n");
	    TP->move_living("M", PATHS_DIR + path_file,1);

        return 1;
    }
    write(CAP(wall_howto) + " what, the wall?\n");
    return 1;
}

int query_num_of_paths()
{
    return num_of_paths;
}