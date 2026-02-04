/*
 *  Company Hideout, Waterfall
 *  Coded by Shinto 120798
 *
 */

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/company/guild.h"

inherit STDROOM;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Behind a waterfall");
    set_long("Nice description of the room.\n");

    add_item(({"wall","walls"}), "The walls are made of solid rock.\n");

    INSIDE;
    add_exit(COMPANY +"hidden/tunnel1", "south",0);

    reset_room ();

}
