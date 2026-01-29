/* 
 * A hobbit dwelling in Waymeet
 * This smial is oriented westward.
 * A medium-income hobbit hole
 * --Raymundo, Jan 2020
 */
 
inherit "/d/Shire/std/room";

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
	set_short("The Children's Bedroom");
	
	set_long("Judging by the pink curtains on the windows, this bedroom "
		+ "belongs to a girl. Looking at the bunk bed along the wall, "
		+ "you quickly realize it belongs to two girls. There are toys "
		+ "about, and a cute chest of drawers that's large enough to hold "
		+ "clothes for two kids. There is a window on the north wall, and "
		+ "it lets in a bit of light.\n");
	
	add_bedroom_child("bunk bed");
	add_walls();
	add_window("pink");

	add_exit(WAYM_HOUSE_DIR + "h_4_5", "south"); //Hallway
	
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
	hobbit = clone_object(HOBBITMAKER);
	hobbit->set_type(CHILD);
	hobbit->set_gender(1);
	hobbit->move(TO);
	hobbit->set_chat_time(5);
	hobbit->add_chat("I'm happy my parents adopted me.");
	hobbit->add_chat("I miss my real parents, but I love my new mom and dad.");
	hobbit->add_chat("I have new parents now!");
	hobbit->add_chat("I hate orcs. They killed my parents.");
	hobbit->add_chat("Will you kill the orcs for me? My dad says I'm too little.");
	hobbit->set_default_answer("The hobbit looks angry about orcs.\n");

}