/* Khahan's Yurt
 * Chaos, 5 April 1995
 */

inherit "/std/room";

#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/katakoro/teamerh.h"

    void
    reset_room()
    {
   bring_room_team(KAT_DIR+"NPC/khahan.c",1,5,KAT_DIR+"NPC/elite.c",1);
    }

void
create_room()
{

    set_short("The Khahan's yurt");
    set_long("This yurt is the home of the Great Khahan of Katakoro.  " +
	"The decore is quite spartan considering the vast power that "+
	"this man wields.  Hanging from the posts over which the felt "+
	"walls are streched are lamps with provide a small amout of "+
	"which seems to add more to the gloom than detract from it.  "+
	"Also scattered about are cushions, presumably there to sit "+
	"on, but one would only do that with the Khahan's permission.  "+
	"Dark shadows, possibly caused by the poor lighting, seem to "+
	"dance about the room, there's no telling what could be "+
	"hiding amongst them.\n");

    add_exit(KAT_DIR+"encampment/camp10","out");
   reset_room();
}

