/* /d/Genesis/delivery/example_office.c
 * 
 * This is a small example of what an office could look like. 
 *
 * Created by Aridor, 05/95
 * Last modified by Aridor 06/07/95
 *
 * A typical office. Nothing fancy, but it serves the purpose.
 */

#include "/d/Genesis/delivery/delivery.h"

#pragma save_binary

inherit DELIVERY_OFFICE;
inherit "/std/room";

/* Function name: reset_room
 * Description:   this should call reset_office to reset the office regularly.
 */
void
reset_room()
{
    /* reset the office regularly */
    reset_office();
}

/* Function name: create_room
 * Description:   here should the office be assigned with a name. use the
 *                set_office() or set_office_name() function for this. Also,
 *                there is a standard text to display with a call to
 *                delivery_poster.
 */
void
create_room()
{
    set_short("Office example room");
    set_long("You are in the delivery office example room. There is a poster " +
	     "hanging on the wall and there are packets and boxes stacked " +
	     "everywhere.\n");

    /* use the default poster description */
    add_item("poster","@@delivery_poster@@");

    /* set the name and the number of packets */
    set_office("the Shop in Solace",5);
    /* let's pretend we're the shop in solace */

    /* The shop delivers torches to other places in Genesis */
    add_content("/d/Krynn/solace/village/obj/torch");
}

/* Function name: init
 * Description:   this adds the room commands to the player. Here we must call
 *                init_office to give the office specific commands to the
 *                player.
 */
void
init()
{
    /* give the commands for the office */
    init_office();
    ::init();
}