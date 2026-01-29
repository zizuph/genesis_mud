/*
 * Base file for road outside Tevalen
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

 string area = "northern"; //the part of town we're in

    
    set_area("in");
    set_areaname("the wasteland");
    set_land("Cypress");
    set_areatype(0);
    set_areadesc("road");
    add_item(({"road", "ground"}),
        "The roadway extends towards the city and is made"+
		" of hard packed sand and gravel.\n");
    add_item(({"gravel","sand"}),
		"These small rounded pebbles have been worn by the"+
		" passage of time and hard travel. It is quite possible"+
		" that the road used to be entirely made of gravel, but "+
		" the harsh weather has slowly changed the gravel to sand"+
		" and the frequent sand storms have attempted neumerous "+
		"times to obliterate the road with its passing.\n");
	add_item(({"plants","plant","cactus"}),
		"These large spiny plants stretch up from the wasteland"+
		" floor. They are covered in many sharp spines as if "+
		" trying to protect themselves from something.\n");
    
    set_add_all_rooms();
    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("A few buzzards circle overhead.");
    add_room_tell("A hot wind howls across the wasteland.");
    add_room_tell("A sharp Yip! sounds from somewhere close."); 
    add_room_tell("A small dust devil spins off to the left.");
    add_room_tell("Lightning crashes in the distance.");
    add_room_tell("A high wind picks up sending sand to move around you.");
    add_room_tell("High above you, a deep rumble starts as if " +
        "the sky was tearing itself apart. It stops as suddenly as it began.");

    
    create_road_room();
 
    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
 
}

 


string road_desc1()
{
    return "The road is wide and wanders through the wasteland"+
		" meandering towards a town.";

}

string road_desc2()
{
    return "This partially obscured track leading through the"+
		" wasteland seems to wander aimlessly through the"+
		" desert.\n";
}
string road_desc3()
{
    return "Wooden buildings crowd the road. They are one story"+
		"shanties unfit for most human habitation." +
        "They block most of your view of the town. The road " +
        "winds its way towards the town. ";
} 

string road_desc4()
{
    return "All around are many desert plants slowly pulling"+
		" substance from the arid wastes.\n";
} 
