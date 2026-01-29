/* Patched by Tapakah for quest reset - June 2011 */
// 2011/06/27 Last update
// 2011/07/18 Lavellan - Made it indoors, fixed typos, and removed include
inherit "/d/Shire/room";
//#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"

void add_stuff();

create_room() 
{
    //set_short("The Dondel's Residense");
    set_short("The Dondels' Residence");

    set_long("You are standing inside a small house in Michel Delving. "+
             "It is very quite and peaceful here away from the main road. " +
             "You can go out the door back to the main road.\n");

    add_item(({ "door", "doors" }), "There is nothing unusual about these "
//             + "wodden doors except for their round shape.\n");
             + "wooden doors except for their round shape.\n");

    add_exit("/d/Shire/michel/fairroad3", "out", 0, 1);    
    add_npc("/d/Shire/michel/npc/wife");
    add_prop(ROOM_I_INSIDE, 1);
}
/* unused, switched to add_npc */
void
add_stuff()
{
    object wife;

    if(!objectp(wife))
    {
        wife = clone_object("/d/Shire/michel/npc/wife");
        //wife->move(TO, 1);
        wife->move(this_object(), 1);
    }
}



