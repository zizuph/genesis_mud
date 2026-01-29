// file name:   
// creator(s):  Grace, Sept 95
// last update: 18 Sept 1995
// purpose:     Tomb of the Last Hobbit
// note:        see ~Avenir/open/HISTORY for background
// bug(s):
// to-do:       


inherit "/std/room";
#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/outpost.h"

void
create_room()
{
    set_short("A room with a pair of white doors");
    set_long("In this small cavern, torches cast uncertain illumination, "+
       "their flames flickering in the breeze which rustles through "+
       "the tunnels.  A pair of marble doors dominate, their white"+
       "ness a shocking contrast to the dark stone of the surround"+
       "ing walls.  Above the doors, letters have been carved into "+
       "the stone and inset with gemstones that glimmer redly "+
       "in the light.\n");
 
    add_exit(OUTPOST + "cave3", "southeast", 0);   
 
    add_item(({"door", "doors", "tomb", "marble", "marble doors"}),
       "The doors are made of unblemished creamy-white marble. "+
       "Though they appear to be made to open outwards, there "+
       "are no handles on which to pull in order to open them. "+
       "Upon the doors are pictures which seem to depict some "+
       "meaningful historical event.\n");
    add_cmd_item(({"door", "doors", "tomb", "marble doors",
       "marble"}), "open",
       "Try as you might, you just can't seem to find a way to "+
       "open the doors.\n");
    add_cmd_item(({"door", "doors", "tomb", "marble doors",
        "marble", "on marble", "on marble doors", "on tomb", 
        "on doors", "on door"}),
        "knock",
        "You bang your fist hard against the heavy marble doors "+
        "in a vain attempt to attract attention.\n");
     add_item(({"picture", "pictures", "pictures on door",
       "painting", "paintings", "last painting", "illustrations"}),
       "The pictures show masses of people of all races wandering "+
       "in dark tunnels. As time progresses in the paintings, "+
       "the numbers of people appear to grow smaller, with "+
       "hobbits being most noticeably reduced. One of the last "+
       "illustrations depicts dwarves, elves, gnomes, goblins, and "+
       "humans standing around a solitary hobbit lying on a bier.\n");
    add_item(({"letters", "carvings", "carving", "opal", "gems",
       "opals", "inset", "incisions", "words", "ribbon", "gemstones"}),
       "The letters were expertly and reverently carved into the "+
       "rough, dark stone above the marble doors. The incisions "+
       "are filled with multi-faceted fire opal gemstones, forming "+
       "a sparkling, blood-red ribbon of words.\n");
    add_cmd_item(({"letters", "carvings", "carving", "opal", "opals",
       "gemstone", "inset", "incisions", "words", "ribbon", "gems"}),
       "read",
       "In the flickering torchlight, the blood-red opal letters "+
       "catch fire, forming the ominous words:\n\n"+
       "                    THE TOMB OF THE LAST HOBBIT\n\n"+
       "           Here lies Orumel, the last of a once-great race.\n"+
       "May his Spirit find in Death that Peace which had evaded him "+
       "in Life.\n\n");
    add_item(({"torch", "torches", "torchlight", "flames"}),
       "They are excellent torches, burning as they do with almost "+
       "no sooty residue.\n");
    add_item(({"walls", "wall", "tunnel", "tunnels", "cavern", "stone"}),
       "The walls of this cavern are dark and rough, a puzzling "+
       "contrast to the exquisite cut and finish of the marble "+
       "doors.\n");
}

