inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("toolshed");
    set_long(
	"The toolshed has no windows and is rather dark.  You are able " +
	"to see by the light of day through the door behind you. " +
	"There are shelves with various bottles and tools on them and " +
	"various gardening equipment lying around stacked against the " +
	"walls.  The floor is littered with the remnants of several " +
	"powdered substances.\n"
    );

    add_prop(ROOM_I_INSIDE, 1);

    seteuid(getuid(TO));

    clone_object(JANUSDIR + "garden/scissors")->move(TO);
    clone_object(JANUSDIR + "garden/rake")->move(TO);
    clone_object(JANUSDIR + "garden/hammer")->move(TO);
    clone_object(TOMBDIR + "al_powder")->move(TO);
    clone_object(TOMBDIR + "white_powder")->move(TO);
    clone_object(TOMBDIR + "black_powder")->move(TO);

    add_exit(TOMBDIR + "cottage_garden", "south", 0);    
}


