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
    set_place(INTERSECT);
    set_long_desc("To your south you can see the center of the village, " +
		  "which seems to be some kind of large open area. Northwest " +
		  "and northeast of you are stone buildings, west and east " +
		  "you can see several tents, homes of the common people " +
		  "in Que Shu. To your north the path continues through the " +
		  "village leading to an opening in the wall further north, " +
		  "where the path leads outside the village onto the Plains of " +
		  "Abanasinia.");
    add_exit(ROOM + "vill3","east");
    add_exit(ROOM + "intersect3","southwest");
    add_exit(ROOM + "intersect1","northwest");
    set_auto_reset(SHUTABLE,random(3),random(3));
}









