/*
 * Inside tent in the Toron minotaur village.
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
    set_location("TENT");
    set_short("Inside a rather large tent");
    set_start_desc("You stand inside a rather large tent made from " +
                   "animal hides. ");
    set_long_desc("You can leave the tent and return to the camp " +
                  "by the opening in the northeast wall. ");

    add_cmd_item("fire","extinguish","You kick some dirt into the " +
                 "fire but all good it does is add to the smoke in the " +
                 "tent. \n");
                 
    add_item("northeast wall",
             "There is an opening in the wall leading outside. \n"); 

    add_furs();
    add_smoke();
    add_walls();
    add_fire();
    add_ground();
    add_logs();
    add_opening();
    add_twigs_straw();
    add_hut_flames();
    add_hut_shadows();
    add_tent_light();   

     
    add_exit(ROOM + "village_b","out",0,3);

    reset_room();
}
