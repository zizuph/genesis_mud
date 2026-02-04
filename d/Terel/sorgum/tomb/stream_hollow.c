/*
    Modified: 3 May 2003, by Bleys
        - fixed a typo
*/

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

reset_room()
{
   object squirrel;
   if(present("squirrel"))return;
   squirrel=clone_object("/d/Terel/silver/monster/squirrel");
   squirrel->move(this_object());
}


create_room()
{
    set_short("stream hollow");
    set_long(
	"The sparkling stream flows through this sheltered hollow " +
	"composed of intermixed birch and cedar trees.  The white trunks " +
	"of the birch trees stand out in contrast to the darker cedars.\n"
    );

    add_item(({"cedars", "birches", "tree", "trees", "birch tree",
	       "cedar tree", "birch trees", "cedar trees"}), 
	     "The trees are exceptionally tall and healthy.\n");

    add_item("hollow", 
        "The sheltered hollow is so peaceful it has an almost hypnotic " +
	"effect on you.\n"
    );

    add_item("stream", 
        "The stream is very clear and cold.  The babbling of the stream " +
        "sounds almost like whispered speech.\n"
    );
    
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "stream_falls", "east", 0);
    reset_room();
}


