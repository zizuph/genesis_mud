/*
 * The delivery Office of thornlin
 * Finwe, November 2005
 */

#pragma save_binary

#include "/d/Gondor/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include "locals.h"
#include "/d/Genesis/delivery/delivery.h"


inherit DELIVERY_OFFICE;
//inherit "/std/room";
inherit (COMMON_DIR + "room");


/* Function name: reset_room
 * Description:   this should call reset_office to reset the office regularly.
 */
void
reset_room()
{
    ::reset_room();
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
    set_long("This is the Thornlin Delivery Office. A large desk, covered " +
        "with papers, sits in the center of the room. Some chairs are " +
        "lined against a wall. One one wall hangs a sign.\n");

    INSIDE;  /* This room is a inside room */

    add_item("desk", 
        "It is a wooden desk covered with papers. A feather and a pot of " +
        "ink sit on the desk.\n");
    add_item("chair",
        "It is high-backed and looks well used. It sits behind the desk.\n");
    add_item("chairs",
        "They are high-backed and line a wall..\n");
    add_item("feather",
        "It's a large goose feather. The end is black from being used " +
        "to write with.\n");
    add_item(({"pot", "ink", "pot of ink", "ink-pot", "ink pot"}), 
        "It is a small ink-pot containing some ink.\n");
    add_item(({"ink"}),
        "It is black and sits in the ink pot.\n");
    add_item(({"paper", "papers", }), 
        "The papers are scattered across the desk in an disorderly manner. " +
        "They appear to be orders for stuff to be delivered. You quickly " +
        "glance at them and discover they are written in a language you're " +
        "not familiar with.\n");

    add_cmd_item("sign","read","The sign reads:\nHere you may:\n"+
      "<ask for a delivery tour> To get a delivery task.\n"+
      "<deliver>  To deliver an assigned task.\n"+
      "<return>  To return a failed delivery.\n");
    /* use the default poster description */
    add_item("poster","@@delivery_poster@@");

    /* set the name and the number of packets */
//    set_office("the Shop in Solace",5);
    set_office("Delivery Office of Thornlin", 5);


    add_content(THORN_DIR + "obj/paper");}

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