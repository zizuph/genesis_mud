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
    set_short("East Gallery");
    set_long("This covered passage is a broad gallery which "+
        "runs west into the vault and ends at a massive granite "+
        "wall to the east.  Three huge arches have been carved "+
        "into the east wall, leading into darkness interrupted "+
        "only by the shadow-play from flickering lamps set high "+
        "above you. A filigree screen runs the entire length of "+
        "the south side, beyond which can be seen a gravelled "+
        "walk. Fragrant scents waft in from the north, where "+
        "there is a meditation garden that is used as one of "+
        "the main entrances into the temple.\n");


    add_exit("14", "east", 0);
    add_exit("12", "west", 0);
    add_exit("87", "northeast", 0);
    add_exit("15", "southeast", 0);
    add_exit("90", "north", 0);


   /* Screens, scents, source, floors and walls added from the
    * base room, put additional add_items below. 
    */

    add_gallery();

    add_item(({"garden", "meditation garden"}),
        "From here you can see that the garden is bisected "+
        "by a wide cobbled walk.\n");

    add_item(({ "east wall", "massive wall", "massive granite wall"}),
        "The wall is hewn of a pale white granite, smooth and cool "+
        "to the touch. The lamplight makes the crystals found "+
        "within the granite glow eerily. Within the wall are "+
        "carved three large archways, one leading southeast, the "+
        "center one leading east and the last northeast.\n");

    add_item(({"northeast archway", "second archway", "northeast",
        "circles", "lightning", "two" }),
        "A circle, half green and half blue, divided by a white "+
        "lightning bolt, rests on the keystone of the archway, "+
        "just below the word TWO. The divided circle is the "+
        "symbol of Tabris-Zeffar, Lords of the Second Hour.\n");

    add_item(({"east archway", "third archway", "east", "three",
        "flame", "crescent"}),
        "The number THREE is cut deep into the lintel. "+
        "An alternating pattern of red flames and golden "+
        "crescents mark the archway as the portal through "+
        "which Hahabi and Misrun, Gods of the Third Hour, "+
        "may be sought.\n");

    add_item(({"southeast archway", "southeast", "fourth archway",
        "four", "orbs", "tear-drop", "tear-drops", "lapis-lazuli"}),
        "Carved into the granite above the lintel of this "+
        "archway is the number FOUR.  The white, all-seeing eye "+
        "and the blue hammer of Plalgus have been carefully "+
        "rendered on the smooth granite.\n");

    reset_domain_room();
}
