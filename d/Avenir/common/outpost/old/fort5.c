// file name:   /d/Avenir/common/outpost/fort5.c
// creator(s):  Kazz    Feb '95
// last update: Denis, Jul'96: Made the room to inherit /d/Avenir/inherit/room
// purpose:     middle of the fort
// note:	
// bug(s):
// to-do:       

# pragma strict_types
# include "/d/Avenir/common/common.h"
inherit "/d/Avenir/inherit/room";

void create_domain_room()
{
    set_short("Center of fort");
    set_long("This is the center of the fort. The gate stands west, the "+
	     "black tower stretches up from the southwest and a door leads "+
	     "south. To the northeast you can see an exit from the fort, "+
	     "passing through a large natural archway in the cavern wall. "+
	     "A building is being constructed to the east.\n" );

    add_exit("fort4", "north");
    add_exit("fort7", "northeast");
    add_exit("fort2", "west");
    add_exit("fort6", "south");
// what to put in fort 8?
//      add_exit(OUTPOST + "fort8","east",0);

    add_item(({ "gate"}),
             "The black stone gate controls fort access.\n" );
    add_item(({ "tower", "black tower" }),
             "The black tower rises high above you. Near the top, "+
	     "where the cavern ceiling meets the tower, a window stares "+
	     "blankly out over the fort. You can see a door on the "+
	     "north side of the tower.\n");
    add_item(({ "window", "tower window" }),
             "The tower window is too high for you to look inside.\n");
    add_item(({ "northeast", "exit", "archway", "natural archway" }),
             "From here, it just looks like a way out of the fort.\n");
    add_item(({ "cavern", "ceiling" }),
             "The cavern walls bend up to form the ceiling. The "+
	     "ceiling bends down to the north and south.\n");
    add_item(({ "building", "east" }),
             "The building, really just walls, is just being started. "+
	     "You can't determine what it will be.\n");

    LIGHT
    IN
}
