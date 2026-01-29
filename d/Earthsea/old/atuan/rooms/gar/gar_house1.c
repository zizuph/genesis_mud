inherit "/d/Earthsea/std/room";

#include <ss_types.h>
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Earthsea/atuan/defs.h"

int chest_moved,able_to_move,able_to_see;       /* (1) = chest moved (0) = chest unmoved */
string LONG;

void
create_earthsea_room()
{
	set_short("Inside a small wooden house.");
	set_long("@@long_desc");
		 	
	INSIDE;
	
	add_item(({"view","unbelievable view","window"}),"@@breath_away");
	add_item(({"table","small table"}),"It is a small table constructed from driftwood.");
	add_item(({"chair","simple chair"}),"It is a simple chair constructed from driftwood");
	add_item(({"chest","plain chest"}),"@@check_chest");
	add_item(({"bed","unmade bed"}),"The covers have just been thrown down on the bed.");
	add_item(({"covers","blankets","blanket"}),"They consist of a couple of old tattered blankets.");

add_exit(GAR + "gar_road2","south",0);

reset_room();

}

reset_room()
{
	if (chest_moved = 1){
		remove_exit ("down");
	chest_moved = 0;
	}
}

init()
{
   ::init();
   add_action("move_chest","move");
   add_action("move_chest","push");
   add_action("move_chest","lift");
   add_action("open_chest","open");
   add_action("open_chest","unlock");
}


long_desc()
{
LONG = (BS("You are inside the small house. Despite being made from what looks"+
		" like driftwood, it seems to be very well insulated from the fierce weather"+
		" that undoubtedly lashes the high cliffs.  A small table sits in one corner"+
		" with two simple chairs on either side.  An unmade bed rests in the opposite"+
		" corner with a plain chest at one end. Set into the far wall is a large window"+
		" with an unbelievable view over the ocean and the island of Karego-At.",70));
	if (chest_moved == 1){
		LONG = LONG + (BS("The chest has been moved slightly and you can see a dark"+
			" opening in the floor leading down.",70));
		
	}
	return LONG;
}	

open_chest(str)
{
	if (str != "chest"){
		notify_fail("Open what?\n");
		return 0;
	}

	write ("You dont have the key to open the lock.\n");
	return 1;
}

move_chest(str)
{
	if (str != "chest"){
		notify_fail("Move what?\n");
		return 0;
	}

	able_to_move = (TP->query_stat(0));
		if (able_to_move < 60){
			notify_fail("You lack the strength to move the chest.\n");
			return 0;
		}
		else 
		{
			chest_moved = 1;
			write("You move the chest to one side revealing a trapdoor!\n");
			add_exit(GAR + "stair1","down",0);
		}
	return "";
}
		

check_chest()
{
	write("The chest is quite large and made of heavy oak, with sturdy metal bands"+
		" to strengthen it. A large lock securely fastens it.\n");
	able_to_see = (TP->query_skill(SS_AWARENESS));
         if (able_to_see >= 15){
            write("You can see faint scrape marks, like someone has"+
				" dragged this chest across the floor.\n");
            say(QCTNAME(this_player()) + " examines the chest.\n");
            return "";
		 }
			else{
			 return "";
		 }
		 
	
}


breath_away()
{
	TP->catch_msg("The view is magnificent, and it takes your breath away.\n");
	tell_room(ENV(TP), QCTNAME(TP) + " has his breath taken away by the view.\n",
	  ({TP}));

	return "";
}