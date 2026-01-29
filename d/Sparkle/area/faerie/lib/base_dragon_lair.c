/*
 * Base file for dragon's Lair rooms in Faerie
 * By Nerull, April 2009
 */

#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>



inherit "/std/room";
inherit COMMON_BASE;

#define ALLOW_PASS   "_i_am_allowed_lair"

void create_dragon_cave_room() {}

   
public void
create_room()
{
    set_short("Inside a dark narrow cave");
    
    create_dragon_cave_room();
    reset_room();
 
    add_prop(ROOM_I_INSIDE, 1); // This is an indoor room
    add_prop(ROOM_I_NO_ALLOW_STEED, 1); // sorry, no horses in here.
}

string dragon_lair_desc1(string str)
{
    return short() + ". " +"You are just inside the opening of a small " +
    "crack in the mountain that is hidden by a large boulder from " +
    "outside. This cave appears to have been formed naturally, possibly " +
    "by an earthquake." + str + "\n";
}

string dragon_lair_desc2(string str)
{
    return short() + ". " +"This cave appears to have been formed naturally, possibly " +
    "by an earthquake. Small cobwebs decorate some of the edgy corners this part of the " +
    "cave." + str + "\n";
}

string dragon_lair_desc3(string str)
{
    return short() + ". " +"This cave appears to have been formed naturally, possibly " +
    "by an earthquake. Small cobwebs decorate some of the edgy corners this part of the " +
    "cave. There is a small square socket into the northern cavewall here." + str + "\n";
}

/*
 * Function name : set_cave_room
 * Description   : adds descr of dry cave room
 */
void set_cave_room()
{
    add_item(({"pebbles", "rocks"}),
        "They are small stones that have been dislodged from the walls " +
        "and ceiling. They are smooth and various sizes.\n");
    add_item(({"ceiling"}),
        "It is jagged and irregular shaped. The ceiling is low and " +
        "was carved by the sea many years aqo.\n");
    add_item(({"walls"}),
        "The walls are rough and irregular from having been carved by " +
        "rushing sea waters.\n");
    add_item(({"ground"}),
        "The ground is uneven and dirty, and littered with rocks and " +
        "pebbles.\n");
}

void set_groove()
{
    add_item(({"socket", "groove"}),
             "This is a small square groove into the northern cavewall, about an inch deep.\n");
    
}


