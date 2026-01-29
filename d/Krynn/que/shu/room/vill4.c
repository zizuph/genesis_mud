/* Started by Gorret,
 * continued by Erine,
 * finished by Aridor
 * 07/95 
 */

#include "../local.h"
inherit OUTBASE_ROOM;
#include RND_MEET

void
create_que_shu_room()
{
    set_place(MAINPATH);
    set_long_desc("You are standing on a path in the village of Que Shu. " +
		  "To your north you can see the center of the village, which " +
		  "seems to be some kind of large open area. West and east you " +
		  "can see several tents, homes of the common people in Que " +
		  "Shu. To your south you can see an opening in the wall, " +
		  "where the path leads outside the village onto the Plains " +
		  "of Abanasinia.");

    add_exit(ROOM + "intersect3","north");
    add_tent_exit(ROOM + "tent5","east");
    add_exit(NORTH_EXIT,"south");
    add_tent_exit(ROOM + "tent6","southwest");
}
