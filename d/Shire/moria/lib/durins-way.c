/*
 * Object inherited by all objects on the long Durin's Way.
 */

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "defs.h"

inherit ROGON_ROOM;

int road_distance;

create_rogon_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    
    TO->create_durins_way();
    
    add_item(({ "avenue", "road", "durin's road", "corridor" }),
	     "You are walking in the splendeous Durin's Road, a momenteous " +
	     "historic show of the former greatness of the people of Khazad-dum. " +
	     "The road is quite wide, in fact, a better name for the road is avenue, " +
	     "since it is about 8 yards (7 meters) wide, arched and constructed with " +
	     "a 'Band-pattern' in the grey granite and strokes of red marble. " +
	     "The craft is beautiful, yet remains practical. For the purpose of " +
	     "the stranger, along its Road is marked distances both from the " +
	     "Western Gate and the Eastern Gate by the Dimrill Valley. These " +
	     "marker stones are standing all along Durin's Road.\n");
    add_item(({ "walls", "wall" }),
	     "The 'Band-pattern' in grey granite and strokes of red marble is " +
	     "simply beautiful to the eye. Still being unnursed after the fall " +
	     "of Durin's Line - and the mockery of the Orcs - you clearly " +
	     "see the greatness of the Khazad.\n");
    add_item(({ "marker", "marker stone" }),
	     "You look at the marker, which is written in Sindarin and in Westron,\n" +
	     "you can see that you are @@desc_distance_west@@ from the Western Gate, while " +
	     "@@desc_distance_east@@ from the Eastern Gate by the Dimrill Valley.\n");
    add_item(({"floor", "dust"}),
	     "The floor is rather dusty, but of crotches and grooves you can not see.\n");
    add_item(({"roof", "ceiling"}),
	     "The ceiling is approximately 10 meters above you, and indeed small " +
	     "you feel within these sizes. A main Avenue Durin's Road must have " +
	     "been!\n");
}

string
desc_distance_west()
{
    return LANG_WNUM(road_distance/1000) + " km (" +
	LANG_WNUM(road_distance*10/9) + " yards)" ;
}

string
desc_distance_east()
{
    int dist = 24 * 3000 - road_distance;
    
    return LANG_WNUM(dist/1000) + " km (" +
	LANG_WNUM(dist * 10/9) + " yards)";
}

