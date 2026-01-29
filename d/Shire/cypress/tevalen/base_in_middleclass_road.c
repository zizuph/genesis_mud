/*
 * Base file for middle-class section road Tevalen
 * Tijgen 08 OCT 2001
 */
 
#include "/d/Shire/sys/defs.h"
#include "local.h"
inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";
inherit "/cmd/std/command_driver";
inherit "/d/Shire/esgaroth/base_common";
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

void create_road_room() {}
 
string what_time;


public void
create_area_room()
{

 string area = "average"; //the part of town we're in

    
    set_area("in");
    set_areaname("Tevalen");
    set_land("Cypress");
    set_areatype(0);
    set_areadesc("road");
    add_item(({"road", "ground"}),
        "The roadway travels through the city and is made"+
		" of hard packed sand and gravel.\n");
    add_item(({"gravel","sand"}),
		"These small rounded pebbles have been worn by the"+
		" passage of time and hard travel. It is quite possible"+
		" that the road used to be entirely made of gravel, but "+
		" the harsh weather has slowly changed the gravel to sand"+
		" and the frequent sand storms have attempted neumerous "+
		"times to obliterate the road with its passing.\n");
	
    set_add_all_rooms();
    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("A moan escapes a slave workers lips.");
    add_room_tell("A hot wind howls across the city.");
    add_room_tell("A small urchin bumps into you."); 
    add_room_tell("A slaver bellows out an order followed by a slave screaming in pain.");
    add_room_tell("A begger looks at you then quickly disappears around a corner.");
    add_room_tell("A shopkeeper yells about his wares.");
    add_room_tell("High above you, a deep rumble starts as if " +
        "the sky was tearing itself apart. It stops as suddenly as it began.");

    
    create_road_room();
 
    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
 
}

 


string road_desc1()
{
    return "The road is wide and goes through the average"+
		" section of town.";

}

string road_desc2()
{
    return "The road leading through this part of the"+
		" town seems to be swept clean of debris and well"+
		" maintained.";
}
string road_desc3()
{
    return "The road here is remarkably clean of sand, and "+
		"a fresh load of gravel has been spread across it.";
} 

string road_desc4()
{
    return "This road here is lined with small shops."+
		" Each of the shop owners is standing outside yelling"+
		" to gather attention towards his or her wares.";
} 
