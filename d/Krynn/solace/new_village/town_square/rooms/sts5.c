/*
* STS Room 5
* Created by Leia
* May 30, 2005
*/

/*
** Last Updated By:
** Leia
** July 1, 2005
*/

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit SQUARE_BASE;

void
reset_solace_room()
{
}

void
create_solace_room()
{
    set_add_buildings();
    add_item(({"trees", "tree"}), "There are a few vallenwood trees in this area. As you gaze about, you notice one especially beautiful one to your north. Suddenly something darting in the branches overhead catches your eye.\n");
    add_item(({"branch", "branches"}), "As you gaze towards the branches you notice the dark shape is still darting about above you.\n");
    add_item(({"shape", "dark shape"}), "Peering intently at the dark shape, you finally discern that it is just a mere squirrel. Smiling at your concern over something so small, you notice a vallenwood leaf falling towards you.\n");
    add_item(({"vallenwood leaf", "leaf"}), "@@examine_leaf@@");
    add_exit(ROOM3, "north");
    add_exit(SOUTHSTS5, "south");
    add_exit(ROOM6, "east");
    add_exit(ROOM4, "west");
    add_exit(SESTS5, "southeast");
    add_exit(SWSTS5, "southwest");
    reset_solace_room();
}

string examine_leaf(string str)
{

    if(!present("_leaf_for_cleansing", TO) & !present("_leaf_for_cleansing", TP))
    {
        clone_object(VALLENWOOD_LEAF)->move(TP, 1);
        return "The squirrel seems to have caused a leaf to fall from the trees above you. You follow its trail as it falls through the air and, reaching out, you catch it in the palm of your hand.\n";
    }
    
    else
        return "";
}
