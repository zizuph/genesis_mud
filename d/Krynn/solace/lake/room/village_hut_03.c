/*
 * Inside hut in the Toron minotaur village.
 * Made to inherit minotaur_base_in.
 * Made by Cherek, Jan 2007
 */
 
#include "../local.h"

inherit VILLAGE_BASE_IN;

object mino1, mino2, mino3;

void
reset_toron_room()
{
    if (!objectp(mino1))
    {
        mino1 = clone_object(NPC + "minotaur_standard.c");
        
        mino1->move(TO, 1);
        
        tell_room(TO, "A minotaur arrives.\n", mino1); 
    }
    
    if (!objectp(mino2))
    {
        mino2 = clone_object(NPC + "minotaur_standard.c");
        
        mino2->move(TO, 1);
        
        tell_room(TO, "A minotaur arrives.\n", mino2); 
    }
    
    if (!objectp(mino3))
    {
        mino3 = clone_object(NPC + "minotaur_standard.c");
        
        mino3->move(TO, 1);
        
        tell_room(TO, "A minotaur arrives.\n", mino3); 
    }
}

void
create_toron_room() 
{
    set_location("HUT");
    set_short("Inside a wooden hut");
    set_start_desc("You stand inside a rather poorly constructed " +
                   "wooden hut. ");
    set_long_desc("You can leave the hut and return to the camp " +
                  "by the opening in the west wall. ");     

    add_cmd_item("pole","climb","You try to climb the pole " +
                 "but realize it is simply too sleek.\n");
                 
    add_cmd_item("fire","extinguish","You kick some dirt into the " +
                 "fire but all good it does is add to the smoke in the " +
                 "room. \n");
                 
    add_item("west wall",
             "There is an opening in the wall leading outside. \n");

    add_pole();
    add_furs();
    add_smoke();
    add_hut_roof();
    add_hut_walls();
    add_hut_fire();
    add_hut_ground();
    add_furniture();
    add_opening();
    add_hut_flames();
    add_hut_shadows();
    add_twigs_straw();
 
    add_exit(ROOM + "village_i","out",0,3);  

    reset_room();
}


