/* 
 * A hobbit dwelling in Waymeet
 *
 * --Raymundo, Jan 2020
 */
 
inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>

inherit WAYM_LIB_DIR + "base_hobbit_hole.c";

void reset_shire_room();

int lights = 0;

void
create_shire_room()
{
	set_short("In the Study");
	
	set_long("You have entered the study. Here the master of the house can "
		+ "work on whatever catches his fancy from behind the big fancy desk "
		+ "in the center of the room. Along the walls are paintings, and even "
		+ "a few busts on pedestals. Even with the rich carpets covering the "
		+ "floor, the room feels cold, and unused, with cobwebs hanging "
		+ "down from the ceiling and a layer of dust covering almost "
		+ "everything.\n");
		
	set_room_tell_time(200);
	
	add_item( ({"wall", "walls"}), "The walls are covered in wood paneling, "
		+ "like the rest of the smial. Unlike the rest of the smial, however, "
		+ "these walls are almost completly covered in dust and cobwebs. You "
		+ "see paintings hung from the walls and busts on pedestals stood "
		+ "up against them.\n");
	add_item( ({"bust", "busts", "paintings", "painting"}), "The busts and "
		+ "paintings all seem to depict the same hobbit woman whose painting "
		+ "hangs in the hallway far to the south. In each piece of art, she "
		+ "looks beautiful and serene.\n");
	add_item( ({"chair", "chair"}), "Looking around the room, you notice "
		+ "the office chair smashed and overturned. It looks like some "
		+ "hobbit became very distraught here.\n");
	add_item( "desk", "A symbol of power, the desk takes up most of the room. "
		+ "It is quite large, for a hobbit desk, and is made of oak. There are "
		+ "even some gold-leaf inlays on it, suggesting no expense was "
		+ "spared.\n");
	add_item( ({"gold leaf", "inlay", "inlays", "gold-leaf inlay", "gold-leaf inlays", "gold-leaf"}),
		"The inlays are shaped like maple leaves, and on each one is a little "
		+ "heart, making you believe this desk was a gift from a lover.\n");
	add_item("expense", "This desk was a huge expense, that's for sure!\n");
	add_item("floor", "The floor is covered in rich carpets.\n");
	add_item( ({"carpet", "carpets"}), "These carpets are thick and rich, "
		+ "unfortunately, they are quite dusty. They really need to be taken "
		+ "outside and beaten!\n");
	add_item( "ceiling", "The ceiling looks like the ceiling in the rest "
		+ "of the smial, but you see cobwebs all over.\n");
	add_item( ({"cobweb", "cob web", "web", "cob web", "cob webs", "webs"}),
		"The cobwebs hang from the ceiling, a sign that no one comes "
		+ "in here anymore.\n");
	add_item("dust", "The dust covers everything in a thin layer.\n");
	add_item( ({"center", "center of the room", "center of room"}),
		"The center of the room is dominated by a huge desk, but you "
		+ "already knew that.\n");
	add_item("everything", "Everything is a lot, but looking around the "
		+ "room, you feel like everything is the desk, the broken chair, "
		+ "the artwork, the lamps, even the carpet. There's a lot that goes "
		+ "into everything!\n");
	add_item(({"light", "lights", "lamp", "lamps", "sconce", "sconces"}),
		"The lamps are attached to sconces on the wall. Thanks to the light "
		+ "coming off of them, you can see. But if you ever get tired of "
		+ "seeing, you could always extinguish them.\n");
		
	add_cmd_item( ({"light", "lights", "lamp", "lamps", "sconce", "sconces"}),
		"light", "@@light_lamp@@");
	add_cmd_item( ({"light", "lights", "lamp", "lamps", "sconce", "sconces"}),
		"extinguish", "@@extinguish_lamp@@");
	add_cmd_item( ({"bust", "busts"}), "grasp", "You grasp one of the busts "
		+ "and pull it toward you, listening for the tell-tale 'click' of a "
		+ "hidden passage opening...\n\nYou hear nothing.\n");
	add_cmd_item( ({"carpet", "carpets", "it"}), "beat", "You beat the carpet "
		+ "as hard as you can, but succeed only in sending plumes of dust "
		+ "into the air. Perhaps next time you'll wait to beat the carpets "
		+ "until you're outside.\n");
	add_prop(ROOM_I_LIGHT, -1);
	add_prop(ROOM_I_INSIDE, 1);
	
	add_exit(WAYM_HOUSE_DIR + "h_1_5", "south");
	
		
}

void
reset_shire_room()
{
	add_prop(ROOM_I_LIGHT, -1);
	lights = 0;
}

void
init()
{
	::init();

}

//makes some light
int
light_lamp()
{
	if(lights == 1)
	{
		write("But the room is already light!\n");
		return 1;
	}
	write("You reach up and light the lamps on the wall. Suddenly you "
		+ "can see!\n");
	add_prop(ROOM_I_LIGHT, 1);
	say(QCTNAME(TP) + " reaches up and lights the lamps on the wall. Suddenly "
		+ "you can see!\n");
	lights = 1;
	return 1;
}

//returns the dark
int
extinguish_lamp()
{
	if(lights == 0)
	{
		write("But the room is already dark!\n");
		return 1;
	}
	write("You reach up and extinguish the lamps on the wall, plunging the "
		+ "room back into darkness.\n");
	say(QCTNAME(TP) + " reaches up and extinguishes the lamps on the wall, "
		+ "plunging the room back into darkness.\n");
	add_prop(ROOM_I_LIGHT, -1);
	lights = 0;
	return 1;
}
	