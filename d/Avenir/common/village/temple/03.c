
// file name:        /d/Avenir/common/village/pale/temple/03.c
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
    set_short("West Gallery");
    set_long("This covered passage is a broad gallery which "+
        "runs east into the vault and ends at a massive granite "+
        "wall to the west.  Three huge archways have been carved "+
        "into the west wall, leading into darkness interrupted "+
        "only by the shadow-play from a flickering lamp set high "+
        "above you. A filigree screen runs the entire length of "+
        "the north side, beyond which can be seen a gravelled "+
        "walk. Fragrant scents waft in from the south, where "+
        "there is a meditation garden that is used as one of "+
        "the main entrances into the temple.\n");

    add_exit("05", "west", 0);
    add_exit("02", "east", 0);
    add_exit("06", "northwest", 0);
    add_exit("04", "southwest", 0);
    add_exit("88", "south", 0);

     /* Screens, scents, source, floors and walls added from the
      * base room, put additional add_items below. 
      */

    add_gallery();

    add_item(({"garden", "meditation garden"}),
        "From here you can see that the garden is bisected "+
        "by a wide cobbled walk.\n");

    add_item(({ "west wall", "massive wall", "massive granite wall"}),
        "The wall is hewn of a pale white granite, smooth and cool "+
        "to the touch. The lamplight makes the crystals found "+
        "within the granite glow eerily. Within the wall are "+
        "carved three large archways, one leading southwest, the "+
        "center one leading west and the last northwest.\n");

    add_item(({"southwest archway", "southwest", "eighth archway",
        "eight", "orbs", "tear-drop", "tear-drops", "lapis-lazuli"}),
        "Carved into the granite above the lintel of this "+
        "archway is the number EIGHT. A repeating pattern of "+
        "translucent crystal orbs and tear-drop shaped pieces "+
        "of lapis-lazuli, symbols of Tacritan and Zizuph, "+
        "has been embedded in the stone.\n");

    add_item(({"west archway", "ninth archway", "west", "fist",
        "sculpture", "nine", "red carnelian", "carnelian"}),
        "The number NINE is cut deep into the lintel.  The "+
        "sculpture of a giant fist carved from red carnelian "+
        "juts out of the stone beneath it, a reminder to "+
        "everyone who passes through the archway that Zaren "+
        "can be sought within.\n");

    add_item(({"northwest archway", "tenth archway", "northwest",
        "rectangles", "rectangular carvings" }),
        "In addition to the single instance of the word TEN, "+
        "small rectangular carvings cover the stone face of "+
        "this archway, symbols of Sabrus, Goddess of the Tenth "+
        "Hour.\n");

    reset_domain_room();

}
