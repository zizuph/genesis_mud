inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

create_room()
{
    set_short("forest path");
    set_long(
	"The narrow path winds along below the cover of tall evergreens.  " +
	"A beautifully brilliant sheen of ice that reflects the " +
	"sunlight coats the evergreens and icicles hang from many of the " +
	"branches.   The air is quite brisk and a chilling wind carries " +
	"a fine icy mist that clings to everything.  There are patches " +
	"of snow here and there under the shade of the evergreens.\n"
    );

    add_item(({"ice", "sheen"}), 
        "You can't look at the brilliant sheen too closely because it " +
        "starts to hurt your eyes.\n"
    );

    add_item(({"mist", "fine mist", "icy mist"}), 
	"The mist is so fine that it is barely visible.\n"
    );
    
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "stream_falls", "southwest", 0);
    add_exit(TOMBDIR + "path02", "northeast", 0);    
}


