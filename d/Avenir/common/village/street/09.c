// file name:        /d/Avenir/common/village/street/09.c
// creator(s):       Avenir Wizards, 10/98
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/village/street_base.c";


/* Now create the room.  */
void
create_street_room()
{
    set_short("directly west of the temple pale");
    set_long("You stand at the eastern-most point in the village, "+
        "where the hedges have been groomed to slant sharply away "+
        "to the northwest and southwest.  A gentle breeze carries "+
        "the scent of incense and the muffled sound of voices raised "+
        "in litany from the Temple Pale in the west.  Here and "+
        "there new stones glow palely amongst the worn cobbles.\n");

    add_exit("08", "northwest", 0);
    add_exit("10", "southwest", 0);

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

