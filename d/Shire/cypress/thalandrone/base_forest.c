/*
 * Base file for road in elven city Thalandrone
 * Finwe, july 2001
 */
 
#include "/d/Shire/cypress/sys/defs.h"
#include "local.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;
inherit "/d/Shire/cypress/std/room/room_tell";
inherit "/cmd/std/command_driver";
inherit "/d/Shire/cypress/thalandrone/base_common";
 
//define ROOM_TELL_TIME  random(180)+30
void create_forest_room() {}

string road_type = "path";
 
public void
create_area_room()
{


    set_area("in an");
    set_areaname("ancient forest");
    set_land("Cypress");
    set_areatype(0);
    set_areadesc(road_type);
    add_item(({road_type}),
        "The "+road_type+" is well worn and winds through the " +
        "ancient trees of the forest. It is hard, packed dirt " +
        "that is free from roots, rocks, or anything else that " +
        "would hamper travel. Light and shadows dance across the "+ 
        road_type+"\n");
    add_item("sky",
        "The sky is alive with sunlight.\n");

    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("A few birds fly overhead.");
    add_room_tell("Some leaves fall gently to the ground.");
    add_room_tell("Sunlight dances across the "+road_type+".");
    add_room_tell("Something rustles in the bushes.");
    add_room_tell("Branches move slowly back and forth above you.");
    add_room_tell("A gentle breeze blows past you.");
    add_room_tell("Something watches you, hidden by the forest.");

    add_item(({"plants", "woodland plants"}),
        "Besides trees, a diverse number of plants grow in the " +
        "forest. Flowers and bushes grow everywhere, somewhat " +
        "hampering your travel and blocking your view.\n");
    add_item(({"bushes", "shrubs"}),
        "Bushes of different color and sizes grow everywhere. " +
        "Most of them are thick and healthy looking, and odd " +
        "thing in a large forest.\n");
    add_item(({"moss", "mosses"}),
        "Mosses grow on logs, rocks, hang from trees, and " +
        "under the trees in patches. It is healthy and a deep " +
        "green. Some patches of moss are so large that bumps " +
        "can be seen under them.\n");
    add_item(({"lichen", "lichens"}),
        "Lichen grow on rocks and trees, a sign that the forest " +
        "is ancient. It is grey or white colored and simple or " +
        "fan shaped.\n");
    add_item(({"flowers", "wild flowers"}),
        "Various wild flowers grow throughout the forest. They " +
        "are pink, white, blue, yellow, and other bright colors. " +
        "The flowers are varied, add color to the forest, and " +
        "sway in the breeze.\n");
    reset_cypress_room();
    
    create_forest_room();
    set_add_forest_debris();
    set_add_trees();

    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room

}

 
void
init()
{   
    ::init();
    reset_cypress_room();
}

string road_desc1()
{
    return "The "+road_type+" is well worn and winds through the " +
    "ancient trees of the forest. The trees grow over the "+
    road_type+", creating a canopy of shade. Light filters " +
    "through the leaves, creating pools of light on the "+
    road_type+" and the forest. ";
}

string road_desc2()
{
    return "The wide forest "+road_type+" winds past many " +
    "ancient trees. The forest is ancient and seems healthy " +
    "despite its age. A canopy of leaves shade the "+road_type+
    ", and block some light. Bushes and flowers grow along the "+
    road_type+", preventing travellers from leaving the "+
    road_type+". ";
} 

string road_desc3()
{
    return "Bushes and flowers line the wide forest "+road_type+
    ". It winds past ancient trees that stand like giant " +
    "pillars. Their tops are hidden high above you. Long mosses " +
    "grow from many branches, like old beards. Beneath the trees " +
    "are various fallen branches and logs. ";
} 

string road_desc4()
{
    return "Ancient trees grow over this part of the "+road_type+
    ". They stand like silent guards protecting everything beneath " +
    "them. The "+road_type+" winds under them. Light and shadows " +
    "dance beneath the trees and across the "+road_type+". ";
} 



public string
long_desc()
{
//    string time;
    string desc;
    
//    time  = CLOCK->query_time_of_day(),
    desc = CAP(query_short()) + ". ";
/*
    if (!(CLOCK->query_war()))
    {
	desc += describe_time(time);
    }
    else 
    {
	desc += describe_war(time);
    }
*/
    if (strlen(extraline))
	desc += (" " + extraline);
    if (functionp(vbfc_extra))
	desc += " " + vbfc_extra();
    return (desc);
}
