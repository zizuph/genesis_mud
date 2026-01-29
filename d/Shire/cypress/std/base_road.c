/*
 * Base file for road in Esgaroth
 * Finwe, March 2001
 */
 
#include "/d/Shire/cypress/sys/defs.h"
#include "local.h"
inherit AREA_ROOM;
inherit "/d/Shire/cypress/std/room/room_tell";
inherit "/cmd/std/command_driver";
//inherit "/d/Shire/esgaroth/base_common";
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_road_room() {}
 
public void
create_area_room()
{

 string area = "northern"; //the part of town we're in

    what_time = "It is @@day_desc@@ in Esgaroth. ";
    set_area("in ");
    set_areaname("Esgaroth");
    set_land("Wilderland");
    set_areatype(0);
    set_areadesc("road");
    add_item(({"road", "ground"}),
        "The road is made of thick planks of oak and arranged " +
        "in a diagonal pattern. The road is wide, lined with " +
        "buildings, and very clean.\n");
    add_item("planks",
        "The planks are thick and made of smooth oak. They " +
        "fit neatly into place with very small cracks.\n");
    add_item(({"buildings", "building"}),
        "New buildings line the streets. They are made from " +
        "a combination of wood planks and stone and seem very " +
        "sturdy and well crafted. Most of the buildings have " +
        "peaked roofs and vary in height from one to two " +
        "stories and are well crafted, appearing very sturdy.\n");

    add_item(({"house", "houses"}),
        "All the houses are wooden and of fair size. They are " +
        "sturdy and made of smooth planks of wood. Some of the " +
        "houses appear to belong to well-to-do people.\n");
    add_item(({"roofs", "roof"}),
        "The roofs of the buildings are mostly peaked and made " +
        "of wood or stone shingles.\n");
    add_item("eaves",
        "The eaves extend from the roof by about an arm's length, " +
        "providing protection to anyone standing beneath them.\n");
    add_item(({"shingles"}),
        "The shingles cover the roof in an overlapping pattern, " +
        "Some roofs are covered with wood shingles while other " +
        "roofs are covered with stone shingles\n"); 
    add_item(({"wood shingles", "wood shingle"}),
        "The shingles are made from rough cut lumber and are " +
        "attached to the roofs.\n");
    add_item(({"stone shingles", "stone shingle", 
            "slate shingles", "slate shingle"}),
        "The shingles are made of slate and black. They are " +
        "smooth and well worn from the elements.\n");
    add_item("slate",
        "It is a thin, black stone used as shingles on many " +
        "roofs in the town.\n");
    add_item(({"chimney", "chimnies"}),
        "The chimnies are made from stone and concrete. They " +
        "run up the side of some buildings. They are very wide " +
        "at the base and then become narrow about two thirds of " +
        "the way up the buildings.\n");
    add_item("sky",
        "It is @@day_desc@@ in Esgaroth. @@daylight_desc@@ fills " +
        "the sky.\n");

    set_add_all_rooms();
    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("A few birds fly overhead.");
    add_room_tell("A cool breeze blows from off the lake.");
    add_room_tell("The town shudders as waves crash against it."); 
    add_room_tell("The town pitches gently in a wake.");
    add_room_tell("Dark clouds roll overhead, blocking the @@light_type@@.");
    add_room_tell("Some clouds pass overhead.");
    add_room_tell("High above you, a deep rumble starts as if " +
        "the sky was tearing itself apart. It stops as suddenly as it began.");

    
    create_road_room();
 
    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
 
}

 
void
init()
{   
    ::init();
//    add_action("drink_it",      "drink");
}

string road_desc1()
{
    return "The road is wide and wanders through the town. " +
        "The view is blocked by the many two storied " +
        "buildings that crowd the road. ";
}

string road_desc2()
{
    return "Buildings crowd the road here, blocking " +
        "your view of the town. Most of the buildings " +
        "are two-story structures made of wood amd stone. ";
} 

string road_desc3()
{
    return "Wooden buildings crowd the road. They are about " +
        "two stories " +
        "tall and block most of your view of the town. The road " +
        "winds it way through the town. ";
} 

string road_desc4()
{
    return "All around are many tall buildings with the " +
        "road winding its way through the town. ";
} 

string bridge_default()
{
    return "The large bridge spans Long " +
        "Lake which connects different parts of Esgaroth and " +
        "unifies the town. The bridge is wide, allowing many " +
        "inhabitants and carts to cross it at the same time. ";
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
