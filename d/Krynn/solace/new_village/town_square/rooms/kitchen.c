/*
*  The Kitchen of the Inn of the Last Home
*  Created By Leia
*  June 05, 2005
*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solace/new_village/town_square/local.h"
#include <macros.h>
#include <ss_types.h>

inherit R_FILE
object human;

void
make_otik()
{
    if(!human)
    human = clone_object(OTIK);
    human->move(TO);
    human->arm_me();
}

void
reset_krynn_room()
{
    make_otik();
}

string
climb_hole()
{


    if(this_player()->query_skill(SS_CLIMB) < HARD_TO_CLIMB)
    {
        write("You dont think you are skilled enough to try and climb down to the street below.\n");
        say(QCTNAME(this_player()) + " looks a bit too scared to use the back exit.\n");
        return "";
    }
    write("You skillfully make your way through the hole and down the tree onto the street below.\n");
    TP->move_living("down the hole in the floor, climbing down to the street below.", "/d/Krynn/solace/new_village/main_road3.c",1,0);

    return "";
}

create_krynn_room()
{
    set_short("A Well-Kept Kitchen");
    set_long("You have entered the kitchen of the Inn of the Last Home. This kitchen is extremely clean and well-kept, however, it is also very hot. There are pots and pans, a stove, and to no surprise, a kitchen sink. The chef works busily, trying to avoid you as he moves about the kitchen preparing food. There is a hole in the floor that the rubbish is sent through. \n");
    add_item("hole", "There is a hole here which rubbish is pushed through. This hole is also commonly used by those wishing to escape being seen by someone entering the inn.\n");
    add_item("food", "There are lots of potatoes around here. They seem to be the specialty of the house, as everything on the stove contains this not-so-secret ingredient.\n");
    add_item(({"pot", "pan", "pots", "pans", "pots and pans"}), "There are many pots and pans all about the kitchen. They vary in size and cleanliness, as it appears the dishes have not been done.\n");
    add_item(({"sink", "kitchen sink"}), "This is just a standard kitchen sink. There are some dishes in it, just waiting to be washed.\n");
    add_item("dishes", "The dishes are dirty and caked with potatoes in various forms.\n");
    add_item("stove", "The stove is lit and emits a lot of heat. There are three large pots on top of it cooking, undoubtedly, some potato concotion.\n");
    
    add_exit("/d/Krynn/solace/new_village/inn.c", "north", 0);
    add_cmd_item(({"down hole","down rubbish hole","down","hole", }),"climb", "@@climb_hole");
 
    
    reset_krynn_room();    
}