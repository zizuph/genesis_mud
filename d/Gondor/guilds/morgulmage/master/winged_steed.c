/*
 *  /d/Gondor/guilds/morgulmage/master/options.c
 *
 *  This file is part of the Morgul Mage master object. It should
 *  not be loaded or called directly.
 *
 *  Created by Eowul, November 11th, 2012
 */

#include "/d/Avenir/include/steed.h"

mixed query_winged_steed_fixed_destinations() {
    return ([
        "minas morgul": ([ 
            "path" : (MORGUL_DIR + "city/square"),
            "site" : "The dread tower shoots rapidly high to the sky and "
                     + "you find yourself in the Angmar Square in Minas "
                     + "Morgul.\n"
        ]),

        "black tower" : ([ 
            "path" : "/d/Gondor/guilds/morgulmage/rooms/tower_7c",
            "site" : "The dread tower shoots rapidly high to the sky and "
                     + "you find yourself at the bestiary atop the Black "
                     + "Tower of Minas Morgul.\n"
        ]),

        "morannon" : ([ 
            "path" : (ITH_DIR + "road/nr12") ,
            "site" : "You have landed by a cobbled road somewhere in "
                     + "Ithilien in Gondor.\n"
        ]),

        "lebennin" : ([ 
            "path" : "/d/Gondor/lebennin/road/fieldr7",
            "site" : "The flat plain of grass quickly approaches as you "
                     + "land in the middle of a green field.\n"
        ]),

        "isengard" : ([ 
            "path" : "/d/Gondor/dunland/ford/eyot",
            "site" : "You have landed on the rocky slope of a small "
                     + "island.\n"
        ]),
    
        "evendim" : ([ 
            "path" : "/d/Shire/evendim/ev3",
            "site" : "A grassy rolling hills suddenly grow up from an "
                     + "apparenlty flat surface as your perspective changes "
                     + "during the landing. You have landed on a track on "
                     + "top of a rolling hill in the Shire.\n"
        ]),

        "trollshaws" : ([ 
            "path" : "/d/Shire/common/trollsh/riv6no",
            "site" : "You have landed in the middle of a grove of trees, "
                     + "near some huge rocks.\n"
        ]),

        "vingaard mountains" : ([ 
            "path" : "/d/Krynn/solamn/vin_mount/room/road12",
            "site" : "The wyrm rapidly loses the speed and lands on the "
                     + "top of a mount in the Vingaard Mountains.\n"
        ]),

        "icewall"  : ([ 
            "path" : "/d/Krynn/icewall/forest/forest_11",
            "site" : "You can see nothing but swirling patches of snow as "
                     + "you decend upon the drift and land below it.\n"
        ]),

        "pax tharkas" : ([ 
            "path" : "/d/Krynn/pax/valley/forest6",
            "site" : "Branches crack scraching the tide of your steed "
                     + "as you break through the canopy of trees crowns. You "
                     + "have landed in a light forest near the fortress of "
                     + "Pax Tharkas.\n"
        ]),

        "flotsam" : ([ 
            "path" : "/d/Ansalon/balifor/flotsam_forest/coastline/road9",
            "site" : "You have landed by the end of some eroding road in "
                     + "an evergreen forrest.\n"
        ]),

        "neraka"  : ([ 
            "path" : "/d/Ansalon/taman_busuk/neraka/outer/main/r6",
            "site" : "You have landed in the White Dragonarmy camp within "
                     + "Neraka.\n"
        ]),

        "sanction" : ([ 
            "path" : "/d/Ansalon/taman_busuk/sanction/room/city/slum5",
        ]),

        "estwilde" : ([ 
            "path" : "/d/Ansalon/estwilde/plains/3a" 
        ]),

        "sparkle" : ([ 
            "path" : "/d/Genesis/start/human/wild2/peninsula",
            "site" : "A fresh, see breeze blows at your face as you land "
                     + "on a peninsula.\n"
        ]),

        "hespyre mountains" : ([ 
            "path" : "/d/Kalad/common/wild/pass/w21",
            "site" : "You have landed in a barren valley surrounded by "
                     + "the mighty Hespyre mountains.\n"
        ]),

        "raumdor" : ([ 
            "path" : "/d/Raumdor/common/forest/wforest17",
            "site" : "You have landed in the middle of the grim Forest of "
                     + "Shadows.\n"
        ]),

        "underdark" : ([ 
            "path" : "/d/Terel/mountains/ridge",
            "site" : "You have landed on an icy ridge.\n"
        ]),

        "graveyard" : ([ 
            "path" : "/d/Terel/common/town/mansion/graveyard/grv3",
            "site" : "Tombstones rise around you as you land in a "
                     + "graveyard near a dark mansion.\n"
        ]),

        AVENIR_PORT_NAME : ([ 
            "path" : AVENIR_PORT_PATH,
            "site" : "The ilumination changes rapidly as you reach the "
                     + "very caverns of Avenir. Seconds later you land "
                     + "on a ledge of a cliff along the cavern's wall.\n" 
        ]),

        "argos" : ([ 
            "path" : "/d/Calia/argos/swterr/rooms/for10",
            "site" : "You have landed on a small clearing surrounded by "
                     + "tall, dark pines.\n" 
        ]),

        "blackwall mountains" : ([ 
            "path" : "/d/Emerald/common/guild/aod/rooms/chaos_area", 
            "site" : "Below, a gigantic orange structure looms into view."
                     + " You instantly sense the presence of a powerful and "
                     + "malevolent spirit similar, yet different to your "
                     + "Lord and Master's. Feeling this is an appropriate "
                     + "place for your business, you direct your steed "
                     + "downward where you land beside the immense"
                     + " glowing orifice.\n"
        ]),
    
        "desert" : ([ 
            "path" : "/d/Cirath/ridge/desert/d24",
            "site" : "As your steed slows and the mounds of sand quickly "
                     + "approach, you feel the searing Athasian heat growing "
                     + "more intense.  You land your steed atop the largest "
                     + "dune.\n"
        ]),

        "gont" : ([ 
            "path" : "/d/Earthsea/gont/tenalders/high_fall/ne6" 
        ]),

        "mithas" : ([ 
            "path" : "/d/Ansalon/goodlund/nethosak/forest/room/forest23" 
        ]),

        "palanthas" : ([ 
            "path" : "/d/Krynn/solamn/moor/room/moor3" 
        ]),

        "cadu" : ([ 
            "path" : "/d/Khalakhor/inisi/roke/wild/q5" 
        ]),
    ]);
}

mixed query_winged_steed_destinations(mixed mage) {
    string magename = get_mage_real_name(mage);
    initialize_member(magename);

    if(member_array("winged_steed_destinations", m_indices(member_information[magename])) == -1)
        return ([ ]);

    return member_information[magename]["winged_steed_destinations"];
}

int query_max_number_of_winged_steed_destinations(mixed mage) {
    return 20;
}

void add_winged_steed_destination(mixed mage, string key, string destination) {
    string magename = get_mage_real_name(mage);
    initialize_member(magename);

    // We don't work on non mages
    if(!IS_MEMBER(mage)) return 0;

    // Make sure we always have an array of 
    if(member_array("winged_steed_destinations", m_indices(member_information[magename])) == -1)
        member_information[magename]["winged_steed_destinations"] = ([ ]);

    member_information[magename]["winged_steed_destinations"][lower_case(key)] = ([
            "path" : destination
        ]);
    save_data();
}

void remove_winged_steed_destination(mixed mage, string key) {
    string magename = get_mage_real_name(mage);
    initialize_member(magename);

    // We don't work on non mages
    if(!IS_MEMBER(mage)) return 0;

    if(member_array("winged_steed_destinations", m_indices(member_information[magename])) == -1)
        return;

    m_delkey(member_information[magename]["winged_steed_destinations"], 
        lower_case(key));
    save_data();
}

mixed query_winged_steed_circle_locations() {
    return ([
        "southern ithilien" : ([ 
            "paths" : ({ 
                "/d/Gondor/ithilien/sforest",
                "/d/Gondor/ithilien/emyn-arnen",
                "/d/Gondor/ithilien/forest",
                "/d/Gondor/ithilien/poros"
            })
        ]),

        "northern ithilien" : ([
            "paths" : ({ 
                "/d/Gondor/ithilien/dagorlad",
                "/d/Gondor/ithilien/nforest",
                "/d/Gondor/ithilien/camp"
            }),
        ]),

        "hardondor" : ([
            "paths" : ({ 
                "/d/Gondor/harondor/room/bridge01",
                "/d/Gondor/harondor/room/camp/room/trail07",
                "/d/Gondor/harondor/room/camp/room/campchief",
                "/d/Gondor/harondor/room/camp/room/s05",
                "/d/Gondor/harondor/room/road11s"
            }),
        ]),

        "pelargir" : ([
            "paths" : ({ 
                "/d/Gondor/pelargir/"
            })
        ]),

        "lebennin" : ([
            "paths" : ({
                "/d/Gondor/lebennin/"
            })
        ]),

        "minas tirith" : ([
            "paths" : ({
                "/d/Gondor/minas"  
            })
        ]),

        "anorien" : ([
            "paths" : ({
                "/d/Gondor/anorien"
            })
        ]),

        "edoras" : ([
            "paths" : ({ 
                "/d/Gondor/rohan/edoras/"
            })
        ]),

        "misty mountains" : ([
            "paths" : ({
                "/d/Shire/misty/"
            })
        ]),

        "bree" : ([
            "paths" : ({
                "/d/Shire/bree/rooms/",
                "/d/Shire/bree_camp/"
            })
        ])
    ]);
}

/*
 *  AoB Notes - This function was added to clear the destination lists
 *  of all mages following a wellknown exploit with Halloween costumes
 *  and tents that allowed players with such teleport spells access to
 *  areas like Minas Tirith, Rivendell, and guildhalls. 
 *
 *  It is a blunt function that hopefully shouldn't need to be used 
 *  again, so is commented out.
 *  Arman Kharas - 20Jan2019
 */

/*
void 
clear_all_steed_destinations() 
{
    string * magelist = query_mages();

    foreach(string magename: magelist)
    {
        if(member_array("winged_steed_destinations", 
            m_indices(member_information[magename])) > -1)
        {
            member_information[magename]["winged_steed_destinations"] = ([ ]);
            save_data();
        }
    }
}
*/