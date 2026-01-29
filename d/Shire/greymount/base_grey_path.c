/*
 * Base file for paths near the Grey Mountains
 * Altrus, September 2005
 */

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/greymount/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";
inherit "/cmd/std/command_driver";
 
void create_path_room() {}

public void create_area_room()
{
	set_areadesc("path");
	set_area("through");
	set_areaname("the foothills");
	set_land("the Grey Mountains");
	set_areatype(0);
	
	add_item(({"path", "ground"}), "Being so near the mountains, the ground here has become much more barren than that of the foothills.\n");
	add_item(({"mountains", "ranges", "mountain ranges"}), "There are two mountain ranges near here, the Misty Mountains and the Grey Mountains. Mount Gundabad can be seen from here as well.\n");
	add_item(({"river","rivers"}), "There are two rivers in the general area. The Langwell, flowing east from the Misty Mountains, and the Greylin, flowing south from the Grey Mountains. Both meet to form the larger river Langflood.\n");
	create_path_room();
	
	add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
}

void
init()
{   
    ::init();
}

string path_desc1()
{
    return "To the west and directly to the north, mountains can be seen. The mountain range visible to north is the Ered Mithrin, or Grey Mountains in the common tongue. The Misty and Grey Mountain ranges culminate at one point northwest of here, forming the forbidding peak of Mount Gundabad, to the west of which lies the infamous Mountains of Angmar. Nearby, the sound of rushing water can be heard, and a small river can be seen flowing by. ";
}

string path_desc2()
{
    return "To the west and directly to the north, mountains can be seen. The mountain range visible to north is the Ered Mithrin, or Grey Mountains in the common tongue. The Misty and Grey Mountain ranges culminate at one point northwest of here, forming the forbidding peak of Mount Gundabad, to the west of which lies the infamous Mountains of Angmar. ";
}

string path_desc3()
{
    return "The towering peak of Mount Gundabad looms overhead. The air seems to be much colder, and frequently a rushing blast of wind comes roaring from the east, pummeling the eastern face of the mountains. From this vantage point one has a good view of the Grey Mountain range, stretching out to the east. ";
}

string path_desc4()
{
    return "This is the base of the Grey Mountains. Though not nearly so tall as the Misty Mountains, it nonetheless looks quite forboding. This is a barren and unwelcome land, cold and lonely. The bleak countenance of Mount Gundabad looms to the west, a stark reminder of the harshness of this land. ";
}
