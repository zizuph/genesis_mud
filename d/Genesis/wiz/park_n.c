#pragma save_binary

#include <std.h>
#include <stdproperties.h>
#include "default.h"

create_room() 
{
	set_short("The island park");
	set_long(
		"You stand in the beautiful park.\n" +
		"The grass under your feet is soft and comfortable.\n" +
		"To the south you can see midpoint of the island.\n" +
		"Further to the south you can see the wizards club house.\n" +
		"To the north you can see a tremendous tower rising towards the sky!\n" +
		"There is a sign on the tower that says: 'Tower of Domains'.\n" +
           "To the west, you can enter an ancient, important looking building.\n" +
           "Over the entrance the words 'House of Lords' have been carved into the stone.\n" + 
           "The park continues to the east.\n"
	);
	add_exit(THIS_DIR + "green", "south");
	add_exit(THIS_DIR + "domain", "north");
	add_exit(THIS_DIR + "park_en", "east", "@@construction");
   add_exit("/d/Debug/debuglord/lordroom", "west", "@@check_wizlevel@@");
	change_prop(ROOM_I_LIGHT, 10);
}

int check_wizlevel()
{
    if (SECURITY->query_wiz_rank(this_player()->query_real_name()) >= 7)
        return 0;

    write("Only Lords and Ladies are allowed to enter here.\n");
    return 1;
}
