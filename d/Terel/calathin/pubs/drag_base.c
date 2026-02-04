/*
 *  Dragon Claw Pub, Basement
 *  Coded by Shinto 120798
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
    set_short("Basement of the Dragon Claw Pub");
    set_long("You are in the basement of the pub now. A stairway "+
                   "leads back up. Six barrels are stacked against the left "+
                   "wall in the shape of a pyramid. A wooden bench lines the "+
                   "right wall.\n");

    add_item(({"wall","walls"}), "The walls are made of stone "+
             "to keep out the harsh wind and snow.\n");
    add_item(({"stair","stairs","stairway"}), "A stone stairway leading "+
             "back upstairs.\n");
    add_item(({"barrel","barrels"}), "The barrels are filled with different "+
             "drinks that are served in the pub. Large wooden barrels that hold "+
             "quite a bit of liquid.\n");
    add_item("bench","The bench serves a number of purposes, something "+
             "to hold the barrels on while tapping, or just workers sitting "+
             "down taking a break.\n");
    INSIDE;
    add_exit(CALATHIN_DIR +"pubs/drag_stair", "up",0);

    reset_room ();

}
