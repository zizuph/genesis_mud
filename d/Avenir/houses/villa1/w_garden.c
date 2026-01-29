/*
 * villa1/w_garden.c
 *
 * Lilith, Nov 2021
 *
 */

#pragma strict_types

#include "villa1.h"
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

inherit V1 +"housebase";


/*
 * Function name:        create_house_room()
 * Description  :        Creates a house room from from the base file
 *                       "housebase.c"
 */

void 
create_house_room()
{
    //	object door;

    set_short("water garden");
    set_long("An open-air water-garden unfolds before you. "+
      "A slab of banded white onyx forms a bridge in the center "+
      "of a pond where fish flit between flowering lotuses. "+
      "Water runs down the face of the cliffwall to the south "+
      "and then spills into a bed of black pebbles. Stepping "+
      "stones lead the way into the villa, whilst the bridge "+
      "leads south, toward the front door and "+ 
      "and the fortress guarding the Sybarus sea "+
      "that lies beyond it. There is a discreet "+
      "sign posted near the stone doorway, and a window in "+
      "the door itself.\n");

    add_cmd_item("sign", "read", "@@sign_desc@@");
    add_item("sign", "@@sign_desc@@");
    add_item( ({ "window", "window in door", "doorwindow"}), 
      "@@exa_window|You look through the window.\n|" + V1 +"entry@@");
    add_item( ({"villa", "house", "facade", "north wall"}),
      "The facade of the house is made of white onyx.\n");
    add_item( ({"onyx", "white onyx", "bands", "stripes"}),
      "The onyx here is milky white, banded with stripes both "+
      "translucent and opaque.\n");	
    add_item( ({"bridge", "onyx bridge", "floor", "ground"}),
      "The bridge is made of a slab of white onyx. It spans the "+
      "pond from the entryway to the front hall of the house.\n");
    add_item( ({"front hall", "house", "villa" }),
      "You need to get closer for a better view.\n");
    add_item( ({"ceiling", "sky", "Source"}), 
      "There is open air above. You can see the Source glowing "+
      "and the ceiling of the great cavern far overhead.\n");		
    add_item( ({"south wall", "southern wall", "curtain of water",
	"cliffwall", "cliff wall", "waterfall"}),
      "The southern wall of the water garden is rough, natural " +
      "stone. A curtain of water seeps from it into the pond.\n");
    add_item( ({"doorway", "stone doorway", "door frame", 
	"entryway"}), "It is a deep doorway made of stone.\n");
    add_item( ({"east wall", "eastern wall", "east"}),
      "The eastern wall of the garden is rough, natural stone.\n");
    add_item( ({"west wall", "western wall", "west"}),
      "The western wall of the garden is rough, natural stone.\n");	
    add_item( ({"wall", "walls"}), "The walls of this space are mostly "+
      "natural stone, except the north wall, which is polished onyx.\n");
    add_item(({"north"}), "The front hall of the villa is north.\n");
    add_item(({"south"}), "A heavy door.\n");
    add_item( ({"stone", "natural stone"}),
      "The rough stone of the walls is a natural contrast "+
      "to the highly polished onyx bridge.\n");
    add_item( ({"stones", "stepping stones"}),
      "Textured white onyx stepping stones provide secure "+
      "footing across the bed of black pebbles.\n");
    add_item( ({"bed", "pebbles", "bed of pebbles", "black pebbles" }),
      "Black pebbles polished smooth by water mark the end of the "+
      "pond.\n");
    add_item( ({"pond", "water garden", "east pond", "west pond"}),
      "The pond makes a serene water garden in which fish and "+
      "lotuses float.\n");
    add_cmd_item(({"pond"}), "enter", "Which way, east or west?\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    add_prop("_live_i_can_fish", ({"freshwater"}));

    add_help_topic("here",  "/d/Avenir/houses/help/general");
    add_help_topic("room",  "/d/Avenir/houses/help/general");

    add_exit("front_hall", "north");
    add_exit("pond_e", "east", 0, 0, 1);
    add_exit("pond_w", "west", 0, 0, 1);
}

string
sign_desc()
{
    return
    "     Welcome! Please try <help house>.\n"+
    "                      -The Management.\n";
}

/*
 * Function name: exa_window
 * Description  : This lets people see the adjacent outside room.
 */

public string
exa_window(string desc, string room_file)
{
    object room = find_object(room_file),
    *in_room_p, *in_room_o;

    in_room_p = FILTER_CAN_SEE(
      FILTER_SHOWN_COMPOSITE(FILTER_LIVE(all_inventory(room))),
      this_player());
    in_room_o = FILTER_CAN_SEE(
      FILTER_SHOWN_COMPOSITE(FILTER_DEAD(all_inventory(room))),
      this_player());

    write((room_file)->long());

    if (sizeof(in_room_p))
	this_player()->catch_msg(capitalize(COMPOSITE_LIVE(in_room_p)) + 
	  ".\n");

    if (sizeof(in_room_o))   
	this_player()->catch_msg(capitalize(COMPOSITE_DEAD(in_room_o))+ 
	  ".\n");

    tell_room(ENV(TP), QCTNAME(TP) + " gazes through the window.\n", TP);

    return "";
} 
