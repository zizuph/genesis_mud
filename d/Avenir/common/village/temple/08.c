// file name:        /d/Avenir/common/village/pale/temple/08.c
// creator(s):       Avenir Wizards, 03/01,04/02
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
    set_short("North Gallery");
    set_long("This covered passage is a broad gallery which "+
        "runs south into the vault and ends at a massive "+
        "granite wall to the north. Three huge arches have "+
        "been carved into the north wall, leading into darkness "+
        "interrupted only by the shadow-play from flickering "+
        "lamps set high above you. A filigree screen runs the "+
        "entire length of the east side, beyond which can be "+
        "seen a gravelled walk. Fragrant scents waft in from "+
        "the west, where there is a meditation garden that is "+ 
        "used as one of the main entrances into the temple.\n");

    add_exit("10", "north", 0);
    add_exit("07", "south", 0);
    add_exit("11", "northeast", 0);
    add_exit("09", "northwest", 0);
    add_exit("91", "west", 0);


     /* Screens, scents, source, floors and walls added from the
      * base room, put additional add_items below. 
      */

    add_gallery();

    add_item(({"garden", "meditation garden"}),
        "From here you can see that the garden is bisected "+
        "by a wide cobbled walk.\n");

    add_item(({ "north wall", "massive wall", "massive granite wall"}),
        "The wall is hewn of a pale white granite, smooth and cool "+
        "to the touch. The lamplight makes the crystals found "+
        "within the granite glow eerily. Within the wall are "+
        "carved three large archways, one leading northwest, the "+
        "center one leading north and the last northeast.\n");

    add_item(({"northwest archway", "northwest", "eleventh archway",
        "eleven", "wavy lines", "willow wands", "wands",         "serpents"}),
        "Carved into the granite above the lintel of this "+
        "archway is the number ELEVEN. A repeating pattern of "+
        "three wavy lines and willow wands wound with serpents, "+
        "the symbols of Hizarbin and Sachluph, has been meticu"+
        "lously rendered on the face of the stone.\n");

    add_item(({"north archway", "twelfth archway", "north", 
        "twelve", "red triangles", "black triangles",         "triangles"}),
        "The number TWELVE is cut deep into the lintel. "+
        "Red triangles, symbol of Sisera, and black triangles, "+
        "symbolizing Jazur, are arranged in diamond-shaped "+
        "patterns along the stone face of this archway.\n");

    add_item(({"northeast archway", "first archway", "northeast",
        "last archway", "first", "one", "octagons", "locks",
        "keys", "lock-and-key"}),
        "In addition to the single instance of the word ONE, "+
        "the right-hand side of the archway is lined with "+
        "octagons, and the left-hand side with lock-and-key "+
        "glyphs.  These are symbols of Sair and Salilus, the "+
        "Gods of the First Hour.\n");

    reset_domain_room();
}
