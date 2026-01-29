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
    set_long_desc("To your south you can see the center of the village, " +
		  "which seems to be some kind of large open area. Southeast " +
		  "of you is a stone building, northeast and east you can see " +
		  "several tents, homes of the common people in Que Shu. " +
		  "To your north you can see an opening in the wall, where the " +
		  "path leads outside the village onto the Plains of " +
		  "Abanasinia. West of you is another stone building, " +
		  "apparently the home of an important person.");
    add_exit(ROOM + "intersect1","south");
    add_tent_exit(ROOM + "tent1","northeast");
    add_exit(SOUTH_EXIT,"north");
    add_exit(ROOM + "shaman","east");
    add_exit(ROOM + "chief","west");
    add_exit(ROOM + "temple","southeast");
    set_auto_reset(SHUTABLE,random(3),random(3));
}









