inherit "/std/room";
 
#include "default.h"
#include <macros.h>

int enter_mirror(string str);

void
create_room()
{
    set_short("In tower");
    set_long( "You are standing in a stairway. On the wall there "+
	     "is a mirror, while the stairs continue up and down.\n" );
 
    add_item("mirror",
	      "It is a full-length mirror, and you can see a figure " +
             "resembling yourself peering back at you when you look at " +
             "it.\n");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TCASTLE_DIR + "tower_top", "up");
    add_exit(TCASTLE_DIR + "tower_bottom", "down");
}
 
void
init()
{
    ::init();
    add_action(enter_mirror, "enter");
}
 
int
enter_mirror(string arg)
{
    if (arg!="mirror") {
	notify_fail("Enter what?\n");
	return 0;
    }
    set_dircmd(arg);
    say(QCTNAME(this_player()) + " steps closer to the mirror and promptly "+
	"disappear!\n");
    this_player()->move_living("M", TCASTLE_DIR + "behind_mirror");
    tell_room(TCASTLE_DIR + "behind_mirror", QCTNAME(this_player()) + " " + this_player()->query_m_in() + "\n", this_player());
    return 1;
}
