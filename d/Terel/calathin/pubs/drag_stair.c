/*
 *  Dragon Claw Pub, Stair
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
    set_short("Stairway in the Dragon Claw Pub");
    set_long("You are standing at the top of a stairway leading "+
                   "down into the basement of the Dragon Claw Pub.\n");

    add_item(({"wall","walls"}), "The walls are made of stone "+
             "to keep out the harsh wind and snow.\n");
    add_item(({"stair","stairs","stairway"}), "A stone stairway leading "+
            "down to the basement.\n");
    INSIDE;
    add_exit(CALATHIN_DIR +"pubs/drag_base", "down",0);
    add_exit(CALATHIN_DIR +"pubs/drag_pub","west",0);

    reset_room ();

}
