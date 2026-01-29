// file name:        /d/Avenir/common/village/pale/temple/
// creator(s):       Avenir Wizards, 03/01
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/village/temple_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/village/village.h"  

/* Now create the room.  */
void
create_temple_room()
{
    set_short("South Gallery");
    set_long("This covered passage is a broad gallery which "+
        "runs north into the vault and ends at a massive "+
        "granite wall to the south.  Three huge arches have "+
        "been carved into the south wall, leading into darkness "+
        "interrupted only by the shadow-play from flickering "+
        "lamps set high above you. A filigree screen runs the "+
        "entire length of the west side, beyond which can be "+
        "seen a gravelled walk. Fragrant scents waft in from "+
        "the east, where there is a meditation garden that is "+ 
        "used as one of the main entrances into the temple.\n");



    add_exit("16", "north", 0);
    add_exit("19", "south", 0);
    add_exit("18", "southeast", 0);
    add_exit("20", "southwest", 0);
    add_exit("89", "east", 0);


     /* Screens, scents, source, floors and walls added from the
      * base room, put additional add_items below. 
      */

    add_gallery();

    add_item(({"garden", "meditation garden"}),
        "From here you can see that the garden is bisected "+
        "by a wide cobbled walk.\n");

    add_item(({ "south wall", "massive wall", "massive granite wall"}),
        "The wall is hewn of a pale white granite, smooth and cool "+
        "to the touch. The lamplight makes the crystals found "+
        "within the granite glow eerily. Within the wall are "+
        "carved three large archways, one leading southwest, the "+
        "center one leading south and the last southeast.\n");

    add_item(({"southwest archway", "southwest", "fifth archway",
        "five", "quill", "quill pen", "spot", "black spot"}),
        "Carved into the granite above the lintel of this "+
        "archway is the number FIVE. A repeating pattern of "+
        "quill pens and black spots made of obsidian, the "+
        "symbols of Nantur and Thagrinus, "+
        "has been embedded in the stone.\n");

    add_item(({"south archway", "sixth archway", "south", "six",
        "cross", "circle", "cross and circle", "coin", 
        "massive coin", "massive gold coin"}),
        "The number SIX is cut deep into the lintel. The "+
        "symbols of Nitikas and Zahun, a massvie gold coin and "+
        "a scarlet cross on a white circle, are depicted in "+
        "bas-relief.\n");
   
    add_item(({"southeast archway", "seventh archway", "southeast",
        "two circles", "two circles half-merged", "knife" }),
        "In addition to the single instance of the word SEVEN, "+
        "two repeating symbols are depicted: the two circles "+
        "half-merged, representing Cahor, and the knife, for "+
        "Tarob, both of whom are Gods of the Seventh Hour.\n");

    reset_domain_room();
}
