/* The rubble contains the pieces to the entrance quest of the Gnomes
 * guild 
 * Created by Dajala
 */

inherit "/std/object";

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "../local.h"

int search = 3;  /* flag -> empty */

create_object()
{
	set_short("heap of rubble");
	set_long(BS("A huge heap of rubble. It is a collection of some "
		+ "weird devices or, better, the sad remains of these.", 70));
	add_prop(OBJ_I_WEIGHT, 1000000);
	add_prop(OBJ_I_VOLUME, 20000);
	add_prop(OBJ_I_VALUE, 1);

	set_name("rubble");
	add_name("heap");
	add_name("heap of rubble");

	add_prop(OBJ_S_SEARCH_FUN, "search_rubble");
	add_prop(OBJ_I_SEARCH_TIME, 5);
}

string
search_rubble(object player, string str)
{
	if (search == 0)
	{
		clone_object(OBJ + "nail.c")->move(E(TO));
		search = 1;
		return "You search through the rubble and find a rusty "
			+ "nail.\nAs it looks useless you drop it again.\n";
	}
	if (search == 1)
	{
		clone_object(OBJ + "board.c")->move(E(TO));
		search = 2;
		return "As you search the rubble you come up with an old "
			+ "wooden board. Useless as it seems, you drop "
			+ "it.\n";
	}
	if (search == 2)
	{
		clone_object(OBJ + "stick.c")->move(E(TO));		
		search = 3;
		return "After a while you come up with a round wooden "
			+ "stick. Worthless as it is you drop it.\n";
	}
	return BS("You finish searching the rubble and are quite confident "
		+ "that there is no money to find in there.", 70);
}


/* called when the mining wagon empties in the binroom */

new_rubble()
{
	search = 0;  /* Now the items for the sign-quest are in here */
}
