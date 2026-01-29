/*
 * Orchard in Farm01
 * By Finwe, October 2006
 */
 
#pragma strict_types
 
#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_ORCHARD;

#define QUEST_NAME_PROP "_fruit_quest"
#define PICKED_FRUIT    "_i_picked_fruit"

string path_file;
int path_num;

void
create_orchard_room()
{
    add_prop(ROOM_S_MAP_FILE, "farm_e_map.txt");

    set_short("An old orchard");
    set_extraline("The orchard is small and wild. The trees are old and " +
        "grow in twisted shapes. They grow in rows, as if planted here " +
        "on purpose. Tall grasses grow beneath the trees and a few " +
        "bumblebees dart around the orchard. An old gate leads out of " +
        "the orchard.");

    remove_item("grass");
    remove_item("orchard");
    remove_item("orchard");
    remove_item("path");

    add_item(({"grass"}),
        "The grass is tall and comes up to your knees. It is gray colored and waves in the breeze. It covers the ground beneath the trees.\n");
    add_item(({"orchard"}),
        "The orchard is old and full of gnarled fruit trees. They have not been cared for in years, and look overgrown. Tall grass grows everywhere, hiding the ground and making the orchard look unkempt.\n");
    add_item(({"gate"}),
        "The gate hangs on one hinge and looks rusty. It has a rounded top with the middle full of stylized curls. It looks like you may enter it to leave the orchard.\n");
    add_item(({"trees"}),
        "The trees are old and gnarled. They look overgrown and haven't been cared for in years. Still, they look vigorous and have fruit hanging from them.\n");
    
    add_room_tell("The gate swings in the breeze.");
  
    reset_room();

}

void reset_room()
{
    ::reset_room();
}

public void
init()
{
    ::init();
    add_action("enter_gate", "enter");
    add_action("enter_gate", "out");
}

string set_path_file()
{
// sets paths file
    switch(path_num)
    {
        case 1:
        {
            path_file = "pt01_09"; 
            break;
        }
        case 2:
        {
            path_file = "pt02_09"; 
            break;
        }
        case 3:
        {
            path_file = "pt03_09"; 
            break;
        }
        case 4:
        {
            path_file = "pt04_09"; 
            break;
        }
        case 5:
        {
            path_file = "pt05_09"; 
            break;
        }
        case 6:
        {
            path_file = "pt06_09"; 
            break;
        }
        case 7:
        {
            path_file = "pt07_09"; 
            break;
        }
        case 8:
        {
            path_file = "pt08_09"; 
            break;
        }
    }
//    return path_file;
}


int
enter_gate(string str)
{
    string vb;

    vb = query_verb();
    path_num = find_object(FARM2_DIR + "garden01")->query_num_of_paths();

    if (!str)
    {
        write("Enter what, the gate?\n");
        return 1;
    }

    if( str=="gate" || str=="rusty gate" || vb=="out" )
    {
        set_path_file();
        write("You pass through the rusty gate.\n");
        say(QCTNAME(TP)+" passes through the rusty gate.\n");
        tell_room(HR_DIR + "btr01",QCTNAME(TP) + " arrives.\n");
	    TP->move_living("M", PATHS_DIR + path_file,1);
        return 1;
    }
    write("You do not see any "+str+" to enter through.\n");
    return 1;
}
