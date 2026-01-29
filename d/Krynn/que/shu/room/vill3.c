/* Started by Gorret,
 * continued by Erine,
 * finished by Aridor
 * 07/95 
 */

#include "../local.h"
inherit OUTBASE_ROOM;
#include RND_MEET

object monster;

void
create_que_shu_room()
{
    set_place(EASTPATH);
    set_long_desc("You are standing on a path in the village of Que Shu. " +
		  "To your west you can see the center of the village, which " +
		  "seems to be some kind of large open area. Northwest of " +
		  "you is a stone building, north and southeast you can see " +
		  "several tents, homes of the common people in Que Shu. " +
		  "To your east you can see an opening in the wall, where the " +
		  "path leads outside the village onto the Plains of " +
		  "Abanasinia.\n");

    add_exit(ROOM + "intersect4","west");
    add_tent_exit(ROOM + "tent3","north");
    add_exit(WEST_EXIT,"east");
    add_exit(ROOM + "tent7","southeast");
    set_auto_reset(SHUTABLE,random(3),random(3));
}
