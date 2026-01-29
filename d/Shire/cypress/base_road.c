/*
 * Base file for road in Esgaroth
 * Finwe, March 2001
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/cypress/sys/defs.h"
inherit "/d/Shire/cypress/std/room/room_tell";
inherit "/cmd/std/command_driver";
inherit AREA_ROOM;
                                  
void create_road_room() {}
 
public void
create_area_room()
{

    set_area("in");
    set_areaname("Esgaroth");
    set_land("Wilderland");
    set_areatype(0);
    set_areadesc("road");
    
    set_vbfc_extra("Across the road is a large house that towers over all. ");
    add_my_desc("this is a test of the base file room.\n");
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

//    set_add_all_rooms();
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
}

public string
long_desc()
{
    string desc;
    
    desc = CAP(query_short()) + ". ";
    if (strlen(extraline))
	desc += (" " + extraline);
    if (functionp(vbfc_extra))
	desc += " " + vbfc_extra();
    return (desc);
}
