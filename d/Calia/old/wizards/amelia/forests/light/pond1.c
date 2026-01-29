/*
*  by Amelia, for use in Light Forest
*/
inherit "/std/room";
inherit "/d/Calia/mountain/special/room_tell";
#include "/sys/stdproperties.h"
#include <ss_types.h>
#include "/sys/macros.h"
#include "defs.h"


private int toggle;

void
	
reset_room()
	{
		toggle = 1;
	}
create_room() {

	set_short("A large shallow pond");
	set_long("You find yourself by the edge of a large, "+
		"shallow pond.  There is a cushion of moss under your "+
		"feet, and the pond appears quite huge in front of "+
		"you, extending to a woods of willow trees on the other "+
		"side.  Bushes block the path to your right and left.  "+
		"The surface of the pond seems nearly filled with "+
		"water lilies and lily pads.  Some distance away you can "+
		"see a partially submerged rock, which is covered in pond "+
		"slime.  You hear the sound of lots of frogs, big frogs, "+
		"little frogs, all kinds of frogs, but they seem "+
		"to be well camouflaged.\n");
		

	add_item((({"pond", "large shallow pond", "shallow pond","water"})),
		("As you look at the pond, you can sense it "+
		"is filled with life.  It is a large shallow pond, "+
		"and extends some distance to the other side.\n"));
	add_item((({"moss"})),
		("The moss is very thick and green here, like a carpet.\n"));
	add_item((({"willow", "willows", "willow trees", "trees", "tree"})),
		("Willow trees surround the rim of the pond on the further "+
		"side and gracefully drape their limbs over it.\n"));
	add_item((({"surface"})),
		("By the edge, you look under the surface and "+
		"can see pollywogs and small minnows swimming "+
		"around in a lively fashion.  As you look a little "+
		"further away, you see a large slippery rock "+
		"sticking up through the surface of the pond.\n"));
	add_item((({"heron", "bird"})),
		("This is a large water bird that lives near the pond.  "+
		"His main diet is frogs and pollywogs.\n"));
	add_item((({"water lilies", "water lily", "lily", "lilies",
		"flowers"})),
		("The water lilies are large pink and white blossoms that "+
		"grow on the surface of the pond.  Their leaves are "+
		"large green pads.\n"));
	add_item((({"pad", "pads", "lily pad", "lily pads", "leaves"})),
		("The pads are leaves of the water lilies, and nearly "+
		"cover the pond... As you examine them, you see that "+
		"there are some clear spots, including an area that "+
		"looks like it might be a large rock, not too far away.\n"));
	add_item((({"bush", "bushes"})),
		("These bushes look like they might be cranberry "+
		"bushes, but it's not cranberry season now.\n"));
	add_item((({"area", "clear spots","spot","clear spot"})),
		("In a clear area of the pond some distance "+
		"away, you see a big, slippery rock.  Perhaps "+
		"you should examine it closer.\n"));
	add_item((({"rock","rocks", "large rock"})),
		("This looks like a large rock covered with pond slime.  "+
		"If you are careful, you might be able to jump to it.\n"));
	add_item((({"frog", "frogs"})),
		("You can't see them, because they are hidden.\n"));

	set_tell_time(100);
	add_tell("Ribbit!  Ribbit! \n");
	add_tell("Chug-a-rumph, chug-a-rumph, chug-a-rumph!\n");
	add_tell("Neek-neek-neek!\n");
	add_tell("A dragonfly hovers over a water lily.\n");
	add_tell("The heron searches for frogs among the lily pads "+
		"with his long beak.\n");
	add_tell("Croak! Croak! Croak!\n");
	add_tell("Bre-ke-ke-ke, koax! koax!\n");
	add_tell("Splash!\n");
	reset_room();
	add_exit((FPATH+"nearp"), "southwest", 0, 0);
}

/*
 * Function name:
 * Description  :
 */

void
init()
{

	int id;
	::init();
	add_action("find_exit", "jump");
	add_action("find_exit", "leap");
	add_action("find_exit", "hop");
	id = set_alarm(5.0,0.0, "heron_in", TP);


}
void
enter_inv(object obj, object from)
	{
	::enter_inv(obj, from);
	if (interactive(obj))
		start_room_tells();
	}

int
find_exit(string str)
	{
	if((str=="rock")||(str=="to rock")||(str=="on rock"))
	{
	write("You make like a frog and jump!\n");
	say(QCTNAME(TP)+" seems to think "+TP->query_pronoun()+
		" is a frog! "+QCTNAME(TP)+ " leaps out into the pond "+
		"and lands on a rock.\n");
	TP->move_living("M", FPATH+"pond2", 0,0);
	write("You land on the slippery rock, just managing "+
		"to keep your balance.\n");
	say(QCTNAME(TP)+ " jumps onto the rock.\n");
	return 1;
	}
	notify_fail("Jump where?\n");
	return 0;
}

void
heron_in(object ob)
	
{
	ob->catch_msg("A great blue heron glides gracefully "+
		"in and lands at the edge of the pond, not far away.\n", ob);
}
