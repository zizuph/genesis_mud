/* File: /d/Shire/common/eastroad/eroad.26.c */

#define ROOM_NUMBER 26
#define TEMP_DIR "/d/Shire/common/eastroad/"

#include "defs.h"

object orc;

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	 "You are now standing on the Last bridge, east of the Trollshaws.\n"+
	 "Stories have been told about the Trollshaws, and it used to be a\n"+
	 "dangerous area for adventurers in earlier years. You feel a little\n"+
	 "unsafe as you come closer to the it, since you dont know what's  \n"+
	 "hiding there. The road continues southest into the forrest and \n"+
	 "northwest towards Bree.\n"
	 );

    add_item(({"bridge"}),
	"The bridge is made of stone. Its very  old, but still strong\n"+
	"after so many years. It is a magnificent piece of work.\n"
    );
    add_exit(TEMP_DIR + "eroad.27", "southeast", 0);
    add_exit(TEMP_DIR + "eroad.25", "northwest", 0);
    orc = clone_object("/d/Shire/common/monster/invading_orc");
    orc->move(this_object());
}


reset_room()
{
  ::reset_room();
  if (!orc) { orc = clone_object("/d/Shire/common/monster/invading_orc");
    orc->move(this_object());
    }
}

