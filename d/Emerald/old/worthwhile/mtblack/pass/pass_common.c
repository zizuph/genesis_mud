/* pass_common.c, the baseroom for the pass over Mt. Black*/
/* Geraden 22 January 1997 */

#include "/d/Emerald/defs.h"

inherit "/std/room";

void create_pass();
void create_room()
{

	set_long("   You are on a rocky trail near the top of Mt. Black. "+
		"Rocks ranging from small pebbles to large boulders "+
		"are strewn across the trail, making passage difficult. "+
		"The path twist and turns its way through the gullies and "+
          "knolls on its way toward the summit. ");

	add_item(({"summit", "Mt. Black", "mountain"}), "The summit of the "+
		"mountain rises to a sharp peak about a league away.\n");
	add_item(({"trail", "path"}), "The trail is narrow and strewn with "+
		"rocks and other obsticles making the way dangerous to walk.\n");
	add_item(({"rocks", "pebbles", "boulders", "debris"}), "The rocks "+
		"and debris cover the trial making passage difficult and "+
		"dangerous.\n");
	add_item(({"gullies"}), "Most of the gullies are nothing more than "+
		"small washouts from the heavy rains, but there are a few "+
		"that boarder on ravines, so deep and dark are they.\n");
	add_item(({"knolls"}), "There is nothing special about the knolls.\n");
	add_item(({"ravines"}), "The ravines are dark and overgrown with "+
		"vegitation.  You can't be sure, but you think you see "+
		"large moving around down there.\n");
	
	create_pass();
}

create_pass()
{
}
