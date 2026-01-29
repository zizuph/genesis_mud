// file name:        /d/Avenir/common/village/street/07.c
// creator(s):       Avenir Wizards, 10/98
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/village/street/street_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/bazaar/admin/admin.h"  

/* Now create the room.  */
void
create_street_room()
{
    set_short("southwest of the Tribunal outside Temple Pale");
    set_long("The hedgerows part to reveal a broad cobbled walk "+
        "leading up to an open ornate iron gate in the northeast.  "+
        "On either side of the gate two small towers spiral upward, "+
        "watchposts for the vigilant guards who protect the peace. "+ 
        "Beyond the gate, you can glimpse the red-gold Tribunal "+
        "building.  The worn cobbled walk continues west toward the "+
        "village center and southeast to skirt the Temple Pale.\n");
    
	add_exit(BAZ_ADMIN +"a20", "northeast", 0);
    add_exit("06", "west", 0);
    add_exit("08", "southeast", 1); // not open yet

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

