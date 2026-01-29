// file name:        /d/Avenir/common/village/street/00.c
// creator(s):       Avenir Wizards, 10/98
// revisions:
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
    set_short("northwest of the merchantile pale");
    set_long("This is a cobbled walk bordered on both sides by "+
        "tall hedges. The air is laden with moisture that "+
        "glistens upon every surface, from the smallest of "+
        "leaves to the moss which thrives in the seams "+
        "between the cobbles. Through the easterly hedges the "+
        "scent of food from the merchantile pale drifts. "+
        "There is a large intersection southwest.\n");

    add_exit("01", "northeast", 0);
    add_exit("35", "southwest", 1); // blocked for now.

    /* Air, cobbles, source, and hedges added from the base room, 
     * put additional add_items below. 
     */

    reset_domain_room();
}

