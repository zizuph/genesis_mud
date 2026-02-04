//-*-C++-*-
// file name:      m3.c
// creator(s):     Lilith June 2008
// last update:    
// note: 
// bug(s):
// to-do:
#include "../guild.h";

inherit ROOM_DIR+"vamp_room";

#include <ss_types.h>


public void create_vamp_room()
{

    set_short("east columbarium of mausoleum");
    set_long("This is a granite mausoleum raised to honour the dead "+
        "of a family whose line was long ago extinguished. The south "+
        "wall bears a deep inscription, while the west wall is lined "+
        "with shallow niches holding cinerary urns. A series of "+
        "frescoes band the the upper portion of the walls.\n");
    

    add_exit("m5", "north");
    add_exit("mausoleum", "west");    

    add_item(({"inscription", "engraving","south wall"}), 
        "Engraved deep into the granite is the following:\n"+
        "    Mors Cum Terrore Novo Venit\n");
        /* Death has come with a new terror */
    add_item(({"granite", "quartz", "black stone"}), 
        "The granite is dark grey in colour "+
        "and speckled with black stone and bits of quartz.\n");
    add_item(({"walls", "band"}), 
        "A band of the granite walls have been plastered-over, extending "+
        "from the ceiling down about four feet. Frescoes have been painted "+
        "there.\n");
    add_item(({"ceiling", "ceilings", "ground", "floor"}), 
        "They are made of the same granite as the rest of the structure.\n");
    add_item(({"frescoes", "fresco", "painting", "paintings"}), 
        "The frescoes are so faded that most of the detail is gone, "+
        "however, it seems that they depict scenes of feasting and "+
        "celebration of the afterlife.\n");
    add_item(({"east wall", "columbarium"}), 
        "The columbarium begins on the west wall and continues north. "+
        "It is lined with niches, some empty, some filled with urns.\n");
    add_item(({"niche", "niches"}), 
        "There are nine niches in this part of the columbarium, four of them "+
        "marked with names and filled with urns.\n");
    add_item(({"urn", "urns", "cinerary urns", "marked niches"}), 
        "There are four urns resting in their niches. You can see "+
        "a pink marble urn, an ancient wooden urn, a blue-green "+
        "copper urn, and a red-lacquered urn.\n");
    add_item(({"markings", "names"}),
        "There are four names marked on the niches:\n"+
        "Aulus, Spurius, Gnaea, and Caelian.\n");
    add_cmd_item(({"markings", "names", "niches"}), ({"read"}),
        "There are four names marked on the niches:\n"+
         "Aulus, Spurius, Gnaea, and Caelian.\n");
    add_item(({"first urn", "first niche", "aulus", "Aulus", 
        "pink marble urn", "marble urn", "pink urn"}),
        "There is a pink marble urn in the first niche. The name "+
        "Aulus is inscribed on it.\n");
    add_item(({"second urn", "second niche", "spurius", "Spurius",
        "ancient wooden urn", "wood urn", "wooden urn"}), 
        "There is an ancient wooden urn in the second niche. The name "+
        "Spurius is inscribed on it.\n");
    add_item(({"third urn", "third niche", "gnaea", "Gnaea",
        "blue-green copper urn", "coppper urn"}), 
        "There is a blue-green copper urn in the third niche. The name "+
        "Gnaea is inscribed on it.\n");
    add_item(({"fourth urn", "fourth niche", "Caelian", "caelian",
        "red-lacquered urn", "red urn", "lacquered"}), 
        "There is a red-lacquered urn in the fourth niche. The name "+
        "Caelian is inscribed on it.\n");
    add_item(({"fifth urn", "fifth niche"}),
        "This is a columbarium niche. There is no name inscribed on it.\n");
    add_item(({"sixth urn", "sixth niche"}),
        "This is a columbarium niche. There is no name inscribed on it.\n");
    add_item(({"first empty niche", "seventh niche", "eighth niche", 
        "second empty niche", "ninth niche", "third empty niche",
        "first unmarked niche", "second unmarked niche", 
        "third unmarked niche"}),
        "This is a columbarium niche. There is no name inscribed on it.\n");
}

    
