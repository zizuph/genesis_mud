// file name:        /d/Avenir/common/village/street/03.c
// creator(s):       Avenir Wizards, 10/98
// revisions:        Lilith, Oct 2021/
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/village/street/street_base.c";

/* Now create the room.  */
void
create_street_room()
{
    set_short("Street northeast of the merchantile district");
    set_long("The cobbled walkway bends here, angling "+
        "southeast in one direction, and west in the other. On "+
        "either side, tall hedges grow, so impeccably trimmed "+
        "that they resemble textured green walls. From the "+
        "southwest, in the merchantile pale, the sounds of "+
        "commerce ebb and flow.\n");

    add_exit("02", "west", 0);
    add_exit("04", "southeast", 0);

    /* Air, cobbles, source, and hedges added from the base room, 
     * put additional add_items below. 
     */
    
    reset_domain_room();
}



