/* 
   Removed the up exit to the big tree, and also removed the ability
   to search it. It used to be part of an ill-documented and illogical 
   quest from the barbarian chieftain in Que Shu, that has now been
   changed. The paper the chieftain wants is now located on the Aurak
   leader in the Dragonarmy camp, which makes a lot more sense
       
   Cherek, January 2016                              
*/

#include "local.h"
inherit TDIR+"plain_base";

#include <macros.h>

void
create_plains_room()
{
    set_short("In a clearing");
    set_long("You are standing in the middle of a small clearing. " +
	     "The remains of an old campfire are here and a few " +
	     "wooden logs are lying about. There is also a small water " +
	     "hole under a fair sized oak tree on the edge of the clearing.\n");

    add_item("clearing","The clearing is circular, and about twenty feet " +
	     "in diameter.\n");
    add_item(({"remains","old campfire","campfire","fire"}),
	     "There are a few black pieces of charcoal left, and some " +
	     "black soot.\n");
    add_search(({"remains","old campfire","campfire","fire"}),4,
	       "The fire is a few weeks old, at least.\n");
    add_item(({"soot","charcoal"}),"You cannot see anything special.\n");
    add_item(({"wooden logs","logs"}),"It looks like they could be used " +
	     "for a fire.\n");
    add_item(({"water","water hole","hole"}),"The water looks dark and brackish " +
	     "and smells foul.\n");
    add_search(({"water","water hole","hole"}),6,
	       "/std/coins",-20);
    add_item(({"tree","oak","oak tree"}),"This is the biggest tree in the " +
	     "vicinity. Other than that, you cannot see anything special about " +
	     "it.\n");
    /*
	add_search(({"tree","oak","oak tree"}),7,
	       "The tree is easy to climb. High up in the branches, you notice a " +
	       "large nest.\n");
    add_cmd_item(({"tree","oak","oak tree","up"}),({"climb"}),"@@climb_up@@");
	
    add_exit("up_tree","up",0,4,1);
    */
	
	add_std_exits();
    
    herbs = HERB_MASTER->query_herbs( ({ "meadow", }) );

    reset();
}

/*
string
climb_up()
{
    this_player()->command("up");
    return "";
}
*/

void
reset_plains_room()
{
}

/* Function name: do_not_remove
 * Description:	  Decide if file with this room should be kept
 *		  (for security it is sometime usefull to keep the file)
 *		  Redefine it in ROOM base file or in room file.
 * Returns:	  0 - file can be removed, 1 - keep the file
 */
public int
do_not_remove()
{
    return 1;
}

