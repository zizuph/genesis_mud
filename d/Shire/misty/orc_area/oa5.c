/* highpass */

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>

inherit SHIRE_ROOM;

void make_npcs();

static object *orcs = allocate(6);

void
create_shire_room()
{
	set_short("In a glade at the foot of the mountains");
	set_long("You are at the foot of the Misty Mountains. To the west you can see only huge peaks. You are off the path, among some tall pine trees.\n");
	
	add_item("peak", "The peaks are high and dark.\n");
	add_item("peaks", "The peaks are high and dark.\n");
	add_item("saddle", "It is a natural saddle between two high peaks.\n");
	add_item("glade", "There are mostly pine trees here at the foot of the mountains.\n");
	add_item(({"trees", "pine trees", "tall trees", "tall pine trees"}), "They are quite tall indeed, although somewhat bare looking, as if they are not healthy.\n");
	
	add_exit("/d/Shire/misty/orc_area/oa8", "north", 0, 5);
	add_exit("/d/Shire/misty/orc_area/oa2", "south", 0, 5);
	add_exit("/d/Shire/misty/orc_area/oa4", "west", 0, 5);

	reset_shire_room();
}

void reset_shire_room()
{
	make_npcs();
}

void make_npcs()
{
    /* Do this first, since we may need to clone. */
    setuid();
    seteuid(getuid());
 
    /* Loop over all elements in the array. */
    for(int index = 0; index < 6; index++)
    {
        if (!objectp(orcs[index]))
        {
		orcs[index] = clone_object("/d/Shire/guild/orc_guild/orc_guard");
		orcs[index]->move(TO);
		tell_room(TO, capitalize(LANG_ADDART(orcs[index]->query_nonmet_name()))+ " stalks into the general area.\n");
		orcs[index]->set_restrain_path("/d/Shire/misty/orc_area");
		orcs[index]->set_random_move(4);
        }
    }

}
