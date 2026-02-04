//-*-C++-*-
// file name:      m5.c
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
    set_short("northeast columbarium");
    set_long("This the northeast section of the ancient granite "+
        "mausoleum. Hand-high letters have "+
        "been engraved into the north wall, while the west wall is "+
        "lined with columbarium niches filled with urns. There is a "+
        "remarkably well-preserved mosaic on the east wall.\n");    

    add_exit("m3", "south");
   
    add_item(({"inscription", "engraving","south wall","letters"}), 
        "Engraved deep into the granite is the following:\n"+
        "    Nullum magnum ingenium sine mixtura dementiae\n");
        /* There is no one great ability without a mixture of madness */
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
    add_item(({"mosaic"}), "This is a well-preserved example of a mosiac, "+
        "a form of art that went out of fashion long ago.  It is "+
        "divided into three sections, each of which depicts the same "+
        "figure fighting different dragons.\n");
    add_item(({"figure", "skirt", "kilt", "shield", "spear"}),
        "A mysterious and featureless figure dressed "+
        "in what appears to be a kilt or skirt and carrying a shield. "+
        "It has a long spear in its free hand.\n");
    add_item(({"first section", "east section", "black dragon", 
        "first dragon"}),
        "This section of the mosaic shows the mysterious figure fight"+
        "ing a black dragon.\n");
    add_item(({"second section", "middle section", "red dragon",
        "second dragon"}),
        "This section of the mosaic shows the mysterious figure fight"+
        "ing a red dragon.\n");
    add_item(({"third section", "west section", "white dragon",
        "third dragon"}),
        "This section of the mosaic shows the mysterious figure fight"+
        "ing a white dragon.\n");        
    add_item(({"dragon", "dragons"}), "Which one? There are three "+
        "to look at.\n");
    add_item(({"west wall", "columbarium"}), 
        "It is lined with niches that are filled with urns.\n");
    add_item(({"niche", "niches"}), 
        "There are nine niches in this part of the columbarium, all of them "+
        "marked with names and filled with urns.\n");

    add_item(({"urn", "urns", "cinerary urns", "marked niches"}), 
        "It looks like there are urns in every niche. You can see "+
         "a pale jade urn, a rusted iron urn, an ornate bronze urn, "+
         "a ram's horn urn, an ancient wooden box, a red clay urn, "+
         "a black onyx urn, a garnet-encrusted gold urn, and a "+
         "milk-white quartz urn on the niches."+
         ".\n");
    add_item(({"markings", "names"}),
        "There are nine names marked on the niches:\n"+
         "Galerian, Laelius, Octavia, Sicinon, Drusus, Tullia, "+
         "Quintus, Triar, Annaea.\n");
    add_cmd_item(({"markings", "names", "niches"}), ({"read"}),
        "There are nine names marked on the niches:\n"+
         "Galerian, Laelius, Octavia, Sicinon, Drusus, Tullia, "+
         "Quintus, Triar, Annaea.\n");

    add_item(({"first urn", "first niche", "Galerian", "galerian", 
        "pale jade urn", "pale urn", "jade urn"}),
        "There is a pale jade urn in the first niche. The name "+
        "Galerian is inscribed on it.\n");
    add_item(({"second urn", "second niche", "laelius", "Laelius",
        "rusted iron urn", "rusted urn", "iron urn"}), 
        "There is an rusted iron urn in the second niche. The name "+
        "Laelius is inscribed on it.\n");
    add_item(({"third urn", "third niche", "Octavia", "octavia",
        "ornate bronze urn", "bronze urn"}), 
        "There is an ornate bronze urn in the third niche. The name "+
        "Octavia is inscribed on it.\n");
    add_item(({"fourth urn", "fourth niche", "Sicinon", "sicinon",
        "ram's horn urn", "horn urn"}), 
        "There is an urn made of ram's horn in the fourth niche. The name "+
        "Sicinon is inscribed on it.\n");
    add_item(({"fifth urn", "fifth niche", "drusus", "Drusus",
        "ancient wooden box", "wooden urn"}),
        "There is an ancient wooden box in the fifth niche. The name "+
        "Drusus is inscribed on it.\n");
    add_item(({"sixth urn", "sixth niche", "tullia", "Tullia", "red urn",
        "red clay urn"}),
        "There red clay urn in the sixth niche. The name "+
        "Tullia is inscribed on it.\n");
    add_item(({"seventh urn", "seventh niche", "Quintus", "quintus",
        "black onyx urn", "black urn", "onyx urn"}),
        "There is black onyx urn in the seventh niche. The name "+
        "Quintus is inscribed on it.\n");
    add_item(({"eighth urn", "eighth niche", "triar", "Triar",
        "garnet-encrusted gold urn", "garnet-encrusted urn", "gold urn"}),
        "There is garnet-encrusted gold urn in the eighth niche. The name "+
        "Triar is inscribed on it.\n");
    add_item(({"ninth urn", "ninth niche", "Baldrhys", "baldrhys",
        "milk-white quartz urn", "milk-white urn", "quartz urn"}),
        "There is milk-white quartz urn in the ninth niche. The name "+
        "Annaea is inscribed on it.\n");

}

