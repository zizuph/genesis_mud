/*
 * /w/petros/sparkle/library/room/domains.c
 *
 * East wing of the Genesis Library with resources about
 * all of the domains in Genesis.
 *
 * Created by Petros, March 2008
 * Updated by Gronkas, August 2, 2016 - fixed a typo
 */

#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

// Defines

// Inheritance
inherit (LIBRARY_ROOM_DIR + "library_base");

// Global Variables

// Prototypes
public void             init();
public void             create_library_stack();

/* 
 * Function name:       init
 * Description  :       Standard init function to add actions
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void 
init() 
{
    ::init();  
} // init

/* 
 * Function name:       create_library_stack
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_library_stack()
{
    // Library Initialization Section
    create_genesis_library( ({ "domains" }), 
                            "" );

    // Descriptions Section
    set_short("Stacks - domains of Genesis");
    set_long("A gigantic map takes up most of the wall space in this area "
           + "of the library stacks. You note that the map is an atlas of "
           + "sorts of the entire donut. Many of the books on the shelf "
           + "are labeled with the names of the various domains of "
           + "Genesis. You gather that this room in the east wing would "
           + "be where you would learn about all the wonderful lands one "
           + "could travel to. The stacks continue to the north and to "
           + "the south."
           + "\n\n");
 
    // Room Item Section                              
    add_item( ({ "map", "gigantic map", "donut", "entire donut",
                 "atlas", "detailed atlas", "extremely detailed atlas" }),
                  "An extremely detailed atlas allows you to see the "
                + "entire donut laid out in all its glory. Each domain "
                + "can be examined separately and you get a good "
                + "sense of where everything is by studying this atlas.\n");

    add_item( ({ "wall space", "space" }),
                  "Most of the available wall space contains the "
                + "atlas.\n");

    add_item( ({ "east wing", "wing" }),
                  "The east wing extends to the north and to the south. "
                + "The books in this wing are instructive to the patrons "
                + "regarding the details of the land.\n");

    add_item( ({ "domains" }),
                  "All the domains are labeled in bold lettering on the "
                + "atlas. You can see these domains: Avenir, Calia, "
                + "Earthsea, Emerald, Gondor, Khalakhor, Krynn, "
                + "Raumdor, Shire, Sparkle, and Terel.\n");

    add_item( ({ "domain" }),
                  "Which domain out of the many domains would you like "
                + "to examine more closely?\n");

    add_item( ({ "continent" }),
                  "Which continent would you like "
                + "to examine more closely?\n");

    add_item( ({ "avenir", "avenir domain", "continent of avenir",
                 "avenir continent", "outpost", "sybarus",
                 "isle of the dead", "holm", "utterdark",
                 "shadow union" }),
                  "Towards the southern part of the atlas, you see the "
                + "continent of Avenir. It consists of three land masses. "
                + "You see Sybarus, the Outpost, and the Isle of the "
                + "Dead. Some notable locations on the continent are "
                + "the Holm, Utterdark, and the home of the Shadow "
                + "Union. To the east of Avenir is Krynn, and to the "
                + "northwest is Earthsea.\n");

    add_item( ({ "calia", "calia domain", "continent of calia",
                 "calia continent", "cadets", "cadets of gelan",
                 "calian warriors", "calians", "amazons" }),
                  "The continent of Calia is located on the northeast "
                + "corner of the atlas. From the atlas you can see that "
                + "the continent is home to the world renowned Cadets of "
                + "Gelan, the Calian Warriors, and the Amazons. The "
                + "continent of Middle Earth is to the south, and the "
                + "Emerald domain lies to the west.\n");

    add_item( ({ "earthsea", "earthsea domain", 
                 "continent of earthsea", "earthsea continent",
                 "roke", "travellers", "gardeners of gont", "gardeners",
                 "gont" }),
                  "The Earthsea domain contains one large land mass "
                + "called Gont, and one much smaller one called Roke. "
                + "The famed Travellers as well as the Gardeners of "
                + "Gont find their residences, as you can tell by the "
                + "markings on the atlas. To the north you see the "
                + "Raumdor domain, and to the southeast, you see both "
                + "Avenir and Krynn.\n");

    add_item( ({ "emerald", "emerald domain", "continent of emerald",
                 "emerald continent", "blackwall mountains",
                 "mist isle", "telberin", "city of telberin" }),
                  "The continent of Emerald is situated at the north "
                + "part of the donut on the atlas. Of note on the "
                + "continent is the capital city of Telberin, the "
                + "Blackwall Mountains, and the Mist Isle. Emerald "
                + "is surrounded by Terel to the west, Calia to the "
                + "east, and Middle Earth to the southeast.\n");

    add_item( ({ "gondor", "gondor domain", "edoras", "mordor",
                 "minas tirith" }),
                  "The Gondor domain is a part of the second largest area "
                + "on the donut, Middle Earth. Middle Earth itself takes "
                + "up most of the space along the eastern part of the "
                + "atlas. Gondor is the southern part of Middle Earth. "
                + "You recognize such notable cities as Minas Tirith, "
                + "Edoras, and Mordor. The Shire is to the north, and to "
                + "the west, you see the grand continent of Sparkle.\n");

    add_item( ({ "khalakhor", "khalakhor domain", "continent of khalakhor",
                 "khalakhor continent", "baile ashlagh", "port macdunn",
                 "blademasters" }),
                  "The continent of Khalakhor is located in the northwest "
                + "corner of the atlas. You see one main land mass with "
                + "Port Macdunn, and a smaller island with Baile Ashlagh. "
                + "You see that the Blademasters can be found in "
                + "Khalakhor. To the south is the Raumdor domain, and to "
                + "the east is the continent of Terel.\n");

    add_item( ({ "krynn", "krynn domain", "continent of krynn",
                 "krynn continent", "knights", "knights of solamnia",
                 "palanthas", "neraka", "sanction", "xak tsaroth",
                 "solace", "pax tharkas", "qualinesti", "silvanesti",
                 "mithas", "icewall" }),
                  "Without a doubt, the continent of Krynn is the single "
                + "largest piece of land mass on the entire donut. It "
                + "occupies much of the space on the southern part of "
                + "the atlas. The famed Knights of Solamnia, the grand "
                + "city of Palanthas, Neraka, Sanction, Xak Tsaroth, "
                + "Solace, Pax Tharkas, Qualinesti, Silvanesti, Mithas, "
                + "and Icewall. To the west you see the continent of "
                + "Avenir.\n");

    add_item( ({ "raumdor", "raumdor domain", "continent of kalad-cirath",
                 "land of raumdor", "gladiators", "cirath", "kalad",
                 "drakmere", "forest of shadows", "kabal" }),
                  "The Raumdor domain contains both the actual land "
                + "of Raumdor as well as the continent of Kalad-Cirath. "
                + "The famous Gladiators are located in Cirath in the "
                + "city of Tyr. The large city of Kabal is in the land "
                + "of Kalad. The capital of Raumdor, Drakmere, is next "
                + "to the dreaded Forest of Shadows. The domain is "
                + "found on the western part of the atlas, to the north "
                + "of Earthsea, and to the south of Khalakhor.\n");

    add_item( ({ "shire", "shire domain", "grey havens", "hobbiton",
                 "bree", "herald of the valar", "herald", "rockfriends" }),
                  "The Shire domain takes up the northern part of the "
                + "continent of Middle Earth, a large continent located "
                + "to the east of the atlas. Grey Havens, Hobbiton, and "
                + "Bree are three of the more notable places that you can "
                + "see on the map. You also note that the Herald of the "
                + "Valar can be found here and so are the Rockfriends. To "
                + "the south, you see the Gondor domain.\n");

    add_item( ({ "sparkle", "sparkle domain", "continent of sparkle",
                 "sparkle continent", "shipping lines", "faerie",
                 "dwarfheim", "dragon order" }),
                  "Right in the middle of the atlas, you can see the "
                + "grand domain of Sparkle, where the great city of "
                + "Sparkle resides. It is surrounded on all sides by "
                + "the other domains. You can see from the markings that "
                + "all the shipping lines that go through Sparkle and out "
                + "to all the other domains. Within the domain, you can "
                + "see the land of Faerie, Dwarfheim, and the Dragon "
                + "Order.\n");

    add_item( ({ "terel", "terel domain", "land of terel", 
                 "terel continent", "continent of terel", "ribos", "last",
                 "dabaay", "calathin", "minstrels" }),
                  "The fabled land of Terel is found to the northwest "
                + "portion of the atlas. Among the notable locations "
                + "on the map, you see the capital Calathin, Ribos, "
                + "Last and Dabaay. You can see here that the Minstrels "
                + "can also be found here. To the west is the land of "
                + "Khalakhor, and to the east of it is Emerald.\n");

    // Properties Section
    
    // Exits Section
    add_exit(LIBRARY_ROOM_DIR + "guides_tutorials", "north", 0);
    add_exit(LIBRARY_ROOM_DIR + "map_reference", "south", 0);
} // create_library_stack

/*
 * Function name:        reset_room
 * Description  :        Override the standard reset_room to bring in
 *                       objects that should be here.
 * Arguments    :        none
 * Returns      :        nothing
 */
public void
reset_room()
{
} // reset_room

