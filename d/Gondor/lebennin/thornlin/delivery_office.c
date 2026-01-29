/*
 * The delivery Office of thornlin
 * Finwe, November 2005
 */
#include "/d/Gondor/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include "locals.h"
#include "/d/Genesis/delivery/delivery.h"

inherit (COMMON_DIR + "room");
inherit "/d/Genesis/delivery/office";

object *officer = allocate(1);

int
add_stuff()
{
    int io = sizeof(officer), 
        statnr;

    while (io--)
    {
	    if (!objectp(officer[io]))
	    {
	        officer[io]->set_name("officer");
    	    officer[io] = clone_object(THORN_DIR + "npc/militia");
	        for(statnr=0; statnr < 6; statnr ++)  
		    officer[io]->set_stat_extra(statnr, 40);
    	    officer[io]->set_long("He seems to be a retired officer of " +
                "the Thornlin Military. He still well versed in battles " +
                "and appears strong. The retired officer is responsible " +
                "for deliveries sent and received in the area.\n");
    	    officer[io]->set_officer();
	        officer[io]->arm_me();
	        officer[io]->move_living("from the void", TO);
    	    officer[io]->refresh_living();
	    }
    }
}

void
create_room()
{
    set_short("The Thornlin Delivery Office");
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

    set_office("Delivery Office of Thornlin", 3);

    add_content(THORN_DIR + "obj/paper");

    add_exit(THORN_DIR + "r2c","east");

    add_stuff();
}


void
init()
{
    init_office();
    ::init();
}

void
reset_room()
{
    reset_office();
    add_stuff();
    ::reset_room();
}
