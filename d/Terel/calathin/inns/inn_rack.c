/*
 *  Company Inn, Rack
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
    set_short("Rack room");
    set_long("Rack room description\n");

    add_item(({"wall","walls"}), "The walls are made of solid oak.\n");

    INSIDE;
    add_exit(COMPANY +"inn/inn_stair", "east",0);

    reset_room ();

}
