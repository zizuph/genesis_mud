/*
 *  Company Inn, Stair
 *  Coded by Shinto 031299
 *
 */

#include "/d/Terel/include/Terel.h"

inherit STDROOM;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Stairway in the Withering Willow");
    set_long("You are standing at the top of a stairway on the "+
                   "second floor of the Withering Willow. These "+
                   "rooms are the home to the Company of the Silver "+
                   "Dragon. A window looks out north to the town "+
                   "square of Calathin. To the west is a storage room, "+
                   "east a room with several beds, and a hallway leads "+
                   "south to a board.\n");

    add_item(({"wall","walls"}), "The walls are made of solid oak.\n");
    add_item(({"stair","stairs","stairway"}), "A stone stairway leading "+
             "down to the common room.\n");
    add_item("window","A glass window with a view of the town of "+
                "Calathin.\n");
    INSIDE;
    add_exit(COMPANY +"inn/inn_main", "down",0);
    add_exit(COMPANY +"inn/inn_rack","west",0);
    add_exit(COMPANY +"inn/inn_start","east",0);
    add_exit(COMPANY +"inn/inn_board","south",0);
    reset_room ();

}

