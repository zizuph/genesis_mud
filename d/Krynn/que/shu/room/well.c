/* Started by Gorret,
 * continued by Erine,
 * finished by Aridor
 * 03/95 
 */

#include "../local.h"
inherit OUTBASE_ROOM;
#include RND_MEET

int corpse = 0;

void
create_que_shu_room()
{
    set_place(WELL);
    set_long_desc("Dominating this place is a large round well, made from " +
		  "bricks and topped with a wooden roof. The well doesn't " +
		  "look too deep, and you can see water at the bottom. To " +
		  "your northeast you see some kind of arena. Around you " +
		  "are a few of the typical tents of the village.\n");

    add_exit(ROOM + "intersect3","northeast");
    add_tent_exit(ROOM + "tent10","west");
    set_auto_reset(SHUTABLE,random(3),random(3));
}

