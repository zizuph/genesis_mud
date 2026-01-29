/* Base file for docks in Sanctuary
* Modified from Finwe's Example
*by Tijgen 01jun01
*/


 
#include "/d/Shire/cypress/sys/defs.h"
#include "local.h"
inherit AREA_ROOM;
inherit "/d/Shire/cypress/std/room/room_tell";
inherit "/cmd/std/command_driver";

 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_dock_room() {}
 

string area = "southern"; //the part of town we're in


public void
create_area_room()
{

//    what_time = "It is @@day_desc@@ in @TOWN_NAME@. ";
    set_area("on");
    set_areaname(TOWN_NAME);
    set_land("Cypress");
    set_areatype(0);
    set_areadesc("dock");

    add_item("planks",
        "Worn by years of harsh weather and careless feet, these"+
        " planks of wood have seen better days. The light lacquer "+
        "of earlier more prosperous years has become faded and "+
        "chipped.  More planks then not have been warped by the"+
        " harsh conditions.\n");
        
    add_item(({"buildings", "building"}),
       "The buildings around the town have been crafted from adobe."+
        " They range in heights from a single story to the sprawling"+
        " castle. Each building is in its own state of repair or "+
        "disrepair. The squalor of city life is plainly evident "+
        "from everything your eyes have taken in.\n");
    
    add_item(({"roofs", "roof"}),
        "Flat roofs of various sizes blanket the city. Each"+
        " one has a myriad of different activities played out"+
        " on them.\n");
           
    add_item(({"chimney", "chimneys"}),
        "Protruding from the roof-tops, and extending higher "+
        "then the diverse activities which are being played out"+
        " upon them, are a multitude of pipe like "+
        " apparatuses through which smoke flows freely into the"+
        "sky.\n");

    add_item("sky",
        "The hazy sky is filled with smoke from the populace's"+
        "fireplaces. Strange stenches waft to your nose on the "+
        "winds.\n");
    add_item(({"water", "ocean"}),
        "The ruddy brown water of the harbor, has a small"+
        " amount of fishing vessels scattered through out it."+
        " Floating on the surface of the water are various "+
        " items of flotsam and jetsam that happen to have "+
        "been deposited by activities of the night before.\n");
        
    add_item(({"cleats", "cleat"}),
        "It is a rectangular horizontal bar about an arm's " +
        "length. Both ends are rounded and secured to the pier " +
        "by two vertical bars.  The cleats allow boats to be " +
        "moored to the pier. The cleats are spaced out at " +
        "regular intervals on either side of the pier. The "+
        "paint has been chipped off, and each cleat is rusting"+
        "slowly with every assault of the weather.\n");
    add_item(({"boats"}),
        "There are various boats tied to the piers and out on " +
        "the lake. They bob on the lake. Some are fishing boats, " +
        "sailboats, rowboats, and on the boats.\n");
    add_item(({"fishing boats", "fishing boat"}),
        "The fishing boats are of various sizes. Some are flipped"+
        "upside down on the shore far to your west. While the rest"+
        " are either moored to the piers or out in the harbor or "+
        "ocean.\n");
    add_item(({"merchant boat"}),
        "Sailing slowly into port is a single merchant ship."+
        " From the vastness of the dock area, you can see that"+
        "the port has hardly been very busy in the recent past.\n");
    


//    set_add_all_rooms();
    set_room_tell_time(ROOM_TELL_TIME);

    add_room_tell("The dock rocks back and forth.");
    add_room_tell("A few birds fly overhead.");
    add_room_tell("A cool salty breeze blows from off the harbor.");
    add_room_tell("Waves splash against the dock.");
    add_room_tell("A fish jumps in the harbor");
    add_room_tell("Some clouds pass overhead.");
    add_room_tell("A flock of seagulls squawk overhead.");
    add_room_tell("A fishing boat sails in and docks at the pier.");
    add_room_tell("Some fishing boats sail out onto the harbor"+
        "heading for the ocean.");
    add_room_tell("A large merchant vessel slowly berths at one of the docks.");
    
    create_dock_room();
 
    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
 
}

 
void
init()
{   
    ::init();
//    add_action("drink_it",      "drink");
}

string dock_desc1()
{
    return "These docks have seen better days. Everywhere you"+
        " look the signs of weathering and age are apparent. "+
        "There are few merchant ships here, and many small "+
        "fishing vessels.";
}
string dock_desc2()
{
    return "This mostly abandoned section of pier has several"+
        " broken planks, and most of remaining planks have "+
        "become warped through natures abuse.";
}




