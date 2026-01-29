inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void
create_room()
{
    set_short("Corridor");
    set_long( "The corridor leads to the east and west from here. "+
	     "The floor is worn down like there has been quite a lot of "+
	     "traffic here in previous years. However it is mostly silent "+
	     "here now. On the south door, someone has hung a sign and on "+
	     "the north wall there is an empty door frame.\n" );
 
    add_item("sign", "There is writing on it.\n");
    add_item( ({ "opening", "frame" }),
	      "It looks like it used to hold a door.\n");
 
    add_cmd_item("sign", "read", "It reads 'Hatchery'.\n");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    clone_object(TCASTLE_DIR + "doors/hdoor_b")->move(this_object());
 
    add_exit(TCASTLE_DIR + "under_tower", "north", 0);
    add_exit(TCASTLE_DIR + "corridor_w", "west", 0);
    add_exit(TCASTLE_DIR + "corridor_e", "east", "@@block");
}
 
int
block()
{
    write("You sense that that part have not been finished yet, and stay "+
	  "where you are.\n");
    if (this_player()->query_wiz_level()) {
	write("Being a wizard, you are persistant and tries anyways.\n");
	return 0;
    }
    return 1;
}
