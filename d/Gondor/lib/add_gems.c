 /* set_gems(int) 	Choose a number between 0 and 3.
					0 = no gems.
					1 = easy (low value)
					2 = medium (medium value)
					3 = hard (high value)
					
	guard_type(int)	SCOUT
					GUARD
					CAPTAIN

*/

#define GEMS_DIR "/d/Genesis/gems/obj/"
#define GEMS_SET "_i_have_gems_set_manually"

#include "/d/Gondor/defs.h"
int difficulty = (random(4));

string
gems_easy()
{
	string *gemseasy =
		({"agate", "pyrite", "quartz", "amber", "aquamarine", "spinel"});
	return(ONE_OF_LIST(gemseasy));
}

string
gems_medium()
{
	string *gemsmed =
		({"topaz", "carnelian", "garnet", "lapis", "pearl", "jade", "turquoise"});
	return(ONE_OF_LIST(gemsmed));
}

string
gems_hard()
{
	string *gemshard =
		({"diamond", "pearl_black", "alexandrite", "moonstone", "spinel", 
          "amber", "coral", "sapphire"});
	return(ONE_OF_LIST(gemshard));
}

/* 
 * function		set_gems()
 * arguments	dif
 * 0 = no gems, 1 easy gems, 2 med gems, 3 hard gems
 *
 */
int
set_gems(int dif)
{
	difficulty = dif;
	TO->add_prop(GEMS_SET, 1);
}

/*
 * function: 	make_gems
 * description:	used to determine which gems should go in which corpse.
 */ 
string
make_gems()
{
	if(difficulty >= 4)
	{
		difficulty = 1;
	}
	switch(difficulty)
	{
		case 0:  return "";	
		case 1:  return (gems_easy());		
		case 2:  return (gems_medium());		
		case 3:  return (gems_hard());		
		default: return (gems_easy());		
	}
}