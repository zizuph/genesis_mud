/*
 * Sample room, based on Esgaroth road room
 * Finwe, March 2001
 */

 /* domain define file. Always include */
#include "/d/Shire/sys/defs.h"
/* optional define file for area. */
#include "local.h"

/* sets up outdoor rooms with standard defines, like time */
inherit AREA_ROOM;
/* sets up the random room messages */
inherit "/d/Shire/std/room/room_tell";
/* additional standard inherit */
inherit "/cmd/std/command_driver";
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

public void 
/* replaces standard 'create_room()' */
create_area_room()
{
/* See /d/Shire/lib/area_room.c for more detailed information 
 * about the following items:
 */
    set_area("near");
    set_areaname("the Misty Mountains"); // town/area name
    set_land("Wilderland");   // continent/country name
    set_areatype(3);          // type of area, road, grass, bushes, etc
    set_areadesc("road");     // description of room

/* Special notes: set_short and set_long are not used. They are 
 * created from the items above.
 * Use 'add_my_desc("description")' to add room descriptions to 
 * the generated room description. Notice there is no '\n'.
 */

    set_extraline("This is a sample shire room. In this long description, " +
        "describe the room.");

    add_item(({"ground"}),
        "The ground is hard packed dirt.\n");
    add_item("planks",
        "The planks are thick and made of smooth oak. They " +
        "fit neatly into place with very small cracks.\n");
    add_item(({"buildings", "building"}),
        "They line the streets and are made from " +
        "a combination of wood planks and stone and seem very " +
        "sturdy and well crafted. Most of the buildings have " +
        "peaked roofs and vary in height from one to two " +
        "stories.\n");

/* add_items are used to describe what players will examine. 
 * Be sure to describe all nouns you mention, so be careful what 
 * nouns you mention. ;)
 * Also, describe obvous things even if they aren't mentioned, 
 * like walls, ceilings, floors, etc.
 * Below is a sample from the roads in Esgaroth.
 */
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
        "The shingles cover the roof in an overlapping pattern. " +
        "Some roofs are covered with wood shingles while other " +
        "roofs are covered with stone shingles.\n"); 

/* Sets how often random room messages are displayed.
 * Time is measured in real time seconds.
 */
    set_room_tell_time(45);
/* Actual messages. The room will randomly choose from the 
 * defined ones below. Notice there is no \n at the end of them
 */
    add_room_tell("A few birds fly overhead.");
    add_room_tell("A cool breeze blows from off the lake.");
    add_room_tell("Some clouds pass overhead.");
    add_room_tell("High above you, a deep rumble starts as if " +
        "the sky was tearing itself apart. It stops as suddenly " +
        "as it began.");

/* domain reset room function */
    reset_shire_room();

/* exit code. 
   'PATH_DIR' is defined shortcut defined in a header file. It is 
        usually '/d/Shire/areaname/'
   'filename' is name of room player exits to
   'out' is direction player goes
 */
    add_exit(PATH_DIR + "filename", "out");

}

void
reset_shire_room()
{
/* Insert code that needs to be reloaded when room resets 
 * such as npcs
 */
}
