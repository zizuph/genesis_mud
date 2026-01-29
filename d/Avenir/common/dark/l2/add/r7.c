// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/r7.c
// creator(s):      
// revisions:        Casca, 11/13/99
// purpose:         no purpose right now.
// note:             
// bug(s):           
// to-do:          not ready to open yet.  

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/dark/darkl2_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/dark/dark.h"  

/* Now create the room.  */
void
create_tunnel_room()
{
    set_short("Dusty cavern");
    set_long("A small natural cavern. The floor and the ceiling "+
        "both resemble huge bowls that have been placed rim to rim. "+
        "An opening leads out to the northeast. The floor is virtually "+
        "flooded with dust, and towards the center of the room it nearly "+
        "reaches your knees. At the center of the room is a crudely "+
        "carved pillar about three feet high with a small depression "+
        "in the top.\n");

    add_exit("","southwest", "@@test_exit");

    /*
     * Put additional add_items below. 
     */



    reset_tunnel_room();
}

 
int
test_exit()
{
    object ob;
    if (ob = present("desired_item_unique_name", this_player()))
    {
//        do_mean_thing(this_player());
        return 1;
    }
    else
        return 0;
}
