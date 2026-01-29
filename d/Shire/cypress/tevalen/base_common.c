/* Base common file in Tevalen
* Modified from Finwe's Example
*by Tijgen 01jun01
*/

/*
 * This file file contains all the common items that players 
 * can examine in Esgaroth such as houses, arches, bridges, etc.. 
 * This way these routines aren't  spread over several files 
 * and makes maintaining these routines much easier.
 *
 * To use any of these routines, this file must be inherited 
 * by the base file, then simply call the routine(s) within 
 * the room definition.
 */
 
#include "/d/Shire/cypress/sys/defs.h"
#include "local.h"
inherit AREA_ROOM;
inherit "/d/Shire/cypress/std/room/room_tell";
inherit "/cmd/std/command_driver";

 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

static string	add_all_rooms		="",
				add_citywall_near   ="",
				add_citywall_far	="",
				add_poorhouses		="",
				add_tower_near		="",
				add_tower_far		="",
				add_shops			="";

void set_add_all_rooms()
{
	add_item(({"dust","wind"}),
		"The wind blows through the dry landscape causing a fine"+
		" gritty dust to stir up from the dried out ground. In its"+
		" wild windblown flight, it looks for ever available crack"+
		" to lodge itself in./n");
	add_item(({"sun","glowing disc"}),
		"The hazy disc floating in the heavens is blinding to"+
		" eye, so you avert your gaze quickly, but not before "+
		"an after image of a demon trying to burn the moisture"+
		" from everything around is planted firmly on your eyes./n");
	add_item(({"haze","wavy image","wavy images","water"}),
		"Wavy bands of heat haze reflect off of the ground creating"+
		" an image of water rising from the parched landscape.\n");
	add_item(({"wasteland","shattered land","desert"}),
		"The large expanse of wasteland stretches out in all"+
		" directions heat wavers from the ground in large "+
		"patches obscuring your vision.\n");
}
void set_add_citywall_near(string str)
{
	add_item(({"wall","city wall","walls","city walls"}),
		"These large walls made of dark grey granite "+
		"were brought here by slave labor. They stand"+
		" roughly four times the height of an average "+
		"human and appear to be at least as thick. The"+
		" constant heating by the sun and cooling by "+
		"night have caused the wall to crack in some"+
		" places.\n");
	add_item(({"crack","cracks"}),
		"The cracks in the wall have been painstakingly "+
		" filled with a mud and straw combination to keep"+
		" the wall from cracking more and the sand from "+
		"taking hold and eroding the wall.\n");
	add_item(({"stone","stones","granite"}),
		"The stones that create these walls is uniformly"+
		" grey and appears to be carved from the surrounding"+
		" mountains.\n");
}
void set_add_city_wall_far(string str)
{
	add_item(({"wall","walls","city wall","city walls"}),
		"Even from the distance the massive walls of the city"+
		" loom into your vision. They travel almost straight "+
		" and level into the distance.\n");
}
void set_add_poorhouses(string str)
{
	add_item(({"house","houses","poor house","poor houses"}),
		"These houses seem to be in a state of total disrepair,"+
		" most of the houses have small piles of sand built up"+
		" against their walls, and mounds of sand piled high "+
		"upon their flat roofs.\n");
	add_item(({"sand","piles","mounds","mound"}),
		"Tiny granules of sand have built up on any place"+
		" where there is a crack or crevasse for it to accumulate"+
		" after the wind has blown it up off the ground.\n");
}
void set_add_middlehouses(string str)
{
	add_item(({"house","houses","middle class house"}),
		"The houses around this area have been freshly swept"+
		" clean from the last sand storm. There are signs of"+
		" freshly patched cracks on various homes.\n");
	add_item(({"crack","cracks","patch","patches"}),
		"A mixture of mud and straw has been applied to"+
		" the most recent cracks in the walls around this"+
		" part of town.\n");
}
void set_add_tower_near(string str)
{
	add_item(({"tower","towers","guard tower","guard towers"}),
		"The towers are heavily fortified and made of of the"+
		" same granite that the walls are made off. Atop them"+
		" you see as many guards facing inwards as outwards.\n");
	add_item(({"guard","guards"}),
		"Atop the tower there are several guards facing both"+
		" inwards and outwards. Each is dressed in a tunic "+
		"and a turban to shield themselves from the sun. "+
		"Occasionally you see a glint of metal as one of "+
		"the guards move about. Strapped to their backs you"+
		" can make out a large bow and a quiver of arrows.\n");
}


void set_add_tower_far(string str)
{
	add_item(({"tower","towers","guard tower","guard towers"}),
		"These large fingers stretch high above the city walls"+
		" and reach towards the heavens. There is some movement"+
		" atop the towers.\n");
}
void set_add_shops(string str)
{
	add_item(({"shop","shops","stores","store"}),
	"They are small and are open-aired. They " +
	"are facing the road and loaded with many things for " +
	"sale. Shopkeepers and their assistants yell for the " +
	"attention of everyone passing by, hoping to sell their " +
	"wares.\n");
	add_item(({"shopkeepers", "shopkeeper"}),
		"The shopkeepers are both men and women. They are " +
		"yelling, trying to get anyone's attention to buy their " +
		"wares. Some are thin and plump while others are tall " +
		"and short. Their ages range from young to middle-aged " +
		"to older people.\n");
	add_item(({"wares"}),
		"They are all the things that are available for sale.\n");
}
