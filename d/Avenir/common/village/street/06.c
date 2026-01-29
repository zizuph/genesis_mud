// file name:        /d/Avenir/common/village/street/06.c
// creator(s):       Avenir Wizards, 10/98
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/village/street/street_base.c";

/* Now create the room. */
void
create_street_room()
{
    set_short("in the street between the path to tribunal and "+
        "the village");
    set_long("This is a cobbled walk bordered on both sides by "+
        "tall hedges.  The air is laden with moisture that glistens "+
        "upon every surface, from the smallest of leaves to the "+
        "moss which thrives in the seams between the cobbles.  "+
        "From the north, the scent of incense is carried upon a "+
        "breeze that ruffles the miniature leaves upon the high "+
        "hedges.\n");

    add_exit("05", "west", 0);
    add_exit("07", "east", 0);

    add_tell("Sounds filter through the hedge, sounds of "+
        "love and pleasure admixed with low murmuring voices.\n");
    add_tell("The chime of bells and the thrum of tympani can "+
        "be heard in the direction of the temple pale.\n");   
    add_tell("The faint undertone of reverent voices percolates "+
        "through the hedge.\n");
    add_tell("Eerie chanting rises and falls rythmically.\n");
    add_tell("Citrus and sandlewood scents swirl by.\n");
    add_tell("The coppery scent of fresh blood wafts in from "+
        "the temple pale.\n");
    add_tell("A puff of wind carries the scent of pungent "+
        "incense to your nose.\n");

    /* Air, cobbles, source, and hedges added from the base room, 
     * put additional add_items below. 
     */

    reset_domain_room();
}

