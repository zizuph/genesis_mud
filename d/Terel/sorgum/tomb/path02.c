inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("forest path");
    set_long(
	"The narrow path continues northeast up an incline. " +
	"The air is quite brisk and a chilling wind carries " +
	"a fine icy mist that clings to everything.  There are patches " +
	"of snow here and there under the shade of the evergreens.\n"
    );


    add_item(({"mist", "icy mist"}), 
        "White and feathery it comes from the deep to its brothers " +
	"the clouds.\n"
    );
    
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "path01", "southwest", 0);
    add_exit(TOMBDIR + "path03", "northeast", 0);
    add_exit(TOMBDIR + "meadow01", "south", 0);
    add_exit(TOMBDIR + "forest01", "north", 0);    
}
