// file name:        /d/Avenir/common/village/street/04.c
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
    set_short("street northeast of merchantile pale");
    set_long("A broad cobbled walk, bordered on each side by majestic, "+
            "impeccably groomed hedgerows. There is a small swirl of "+
            "activity, where the occasional priest seems to be caught in "+
            "the tide of people ebbing and flowing from the east in the "+
            "intersection southeast of you. The granite cobbles beneath "+
            "your feet provide secure footing despite the light sheen "+
            "of moisture covering them. A warm breeze causes the leaves "+
            "of the hedge to tremble slightly.\n");

    add_exit("03", "northwest", 0);
    add_exit("05", "southeast", 0);

    /* Air, cobbles, source, and hedges added from the base room, 
     * put additional add_items below. 
     */

    reset_domain_room();
}

