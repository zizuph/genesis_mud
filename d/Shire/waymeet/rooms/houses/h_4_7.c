/* 
 * A hobbit dwelling in Waymeet
 * This smial is oriented westward.
 * A medium-income hobbit hole
 * --Raymundo, Jan 2020
 */
 
inherit "/d/Shire/std/room";
inherit "/std/act/action.c";

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>
#include "/d/Shire/waymeet/lib/hobbitmaker.h"

inherit WAYM_LIB_DIR + "base_hobbit_hole.c";


void reset_shire_room();
void add_hobbit();
object hobbit;

void
create_hobbit_room()
{
	set_short("The Masters' Bedroom");
	
	set_long("This is the master bedroom. The color purple is a theme "
		+ "here, with even the walls having been painted purple. A large "
		+ "princess bed takes up most of the room, but it still leaves "
		+ "room for a closet. To the north is the hallway and past that "
		+ "the children's room, close enough that one of the parents "
		+ "can check on the kids at any time.\n");
	
	add_bedroom_master("princess", "stone");
	add_walls();
	remove_item("wall");
	add_item( ({"wall", "walls"}), "The walls are still made of wood "
		+ "panelling, but these have been painted a light shade of "
		+ "purple and stenciled with flowers.\n");
	add_item( ({"stencil", "stencils", "flower", "flowers"}), 
		"There are flowers that have been stenciled onto the walls. "
		+ "They are little and delicate, with purple, pink, and red tips.\n");
	add_cmd_item( ({"flower", "flowers", "stencil", "stencils"}), "trace",
		"You trace the flowers with your finger. You feel the wood beneath "
		+ "them, yet notice their delicate beauty.\n");
	add_window("purple");

	add_exit(WAYM_HOUSE_DIR + "h_4_5", "north"); //Hallway
	add_hobbit();

}

void
reset_shire_room()
{
	if(!hobbit)
	{
		add_hobbit();
	}
	
}

void
init()
{
	::init();

}

void
add_hobbit()
{
	object hobbit2;
	
	hobbit = clone_object(HOBBITMAKER);
	hobbit->set_type(CITIZEN);
	hobbit->set_power();
	hobbit->set_gender(1);
	hobbit->set_act_time(5);
    hobbit->add_act("hug " + hobbit2->query_name());
	hobbit->set_chat_time(5);
	hobbit->add_chat("I love my husband.");
	hobbit->add_chat("We adopted a daughter together.");
	hobbit->add_chat("Being parents is so fulfilling to us.");
	hobbit->add_chat("We think our daughter is great!");
	hobbit->move(TO);
	

	hobbit2 = clone_object(HOBBITMAKER);
	hobbit2->set_type(MILITA);
	hobbit2->set_power();
	hobbit2->set_gender(0);
	hobbit2->set_act_time(5);
    hobbit2->add_act("kiss " + hobbit->query_name());
	hobbit2->set_chat_time(5);
	hobbit2->add_chat("I'm so happy to be in love with her.");
	hobbit2->add_chat("Please dont talk to our daughter about orcs. She's very "
		+ "upset still.");
	hobbit2->add_chat("I'm so happy to finally have a child with my wife.");
	hobbit2->add_chat("I'm sorry her parents died, but I'm proud to be one of her "
		+ "parents.");
	hobbit2->move(TO);
	
}