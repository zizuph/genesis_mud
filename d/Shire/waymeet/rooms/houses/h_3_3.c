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

void add_hobbit();
object hobbit;


void
create_hobbit_room()
{
	set_short("In the Kitchen");
	
	set_long("This is, perhaps, the most important room in any hobbit's "
		+ "home--the kitchen. This is, as they say, where the magic happens. "
		+ "A pot-bellied stove commands most of the attention here, a pot "
		+ "of stew on top of it creating amazing aromas. But this kitchen is "
		+ "more than a stove. You notice nice wooden counter tops, a sink, "
		+ "and even a pantry. A great meal could be cooked here (several "
		+ "times a day).\n");

	add_kitchen("oak");
	add_stove("pot-bellied");
	add_walls();
	
	add_exit(WAYM_HOUSE_DIR + "h_3_2", "north"); 
	
	add_hobbit();
}

void
reset_shire_room()
{
	add_hobbit();
}

void
init()
{
	::init();
	
}

add_hobbit()
{
	   if (!present(hobbit))
	   {
	hobbit = clone_object(HOBBITMAKER);
	hobbit->set_type(CITIZEN);
	hobbit->set_gender(1);
	hobbit->move(TO);
	   }
	   return ;
	
}