/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * harem.c
 *
 * Vader
 * Recoded by Sorgum 950712
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDROOM;

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({CASTLE_DIR + "monster/h_girl1",
	     CASTLE_DIR + "monster/h_girl2"});		 
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Royal Harem");
    set_long("This is a very bright, very lovely room.  The smells " +
	     "are exotic, and the sights are stunning.  Exotic " +
	     "plants abound everywhere, and a multitude of the " +
	     "most beautiful women you have ever seen lie " +
	     "around everywhere.  The room is furnished with " +
	     "many couches, all of which are occupied by a lovely " +
	     "woman being cared for by a servant.  " +
	     "You don't think that the King would appreciate " +
	     "unauthorized visitors here, but the ladies don't " +
	     "seem to mind!\n");
 
    add_item(({"couches", "couch"}), "They are very luxurious.\n");
 
    add_item(({"plants", "exotic plants"}),
	     "They come from lands all over the world.\n");
    
    add_item(({"women", "beautiful women"}), 
	     "These are the most beautiful women in all of Genesis.  " +
	     "One of them may some day become the Queen of Ribos.\n");
 
    INSIDE;
 
    add_exit(RIBOS_DIR + "castle/l_hall2_3", "west", 0);
    add_exit(RIBOS_DIR + "castle/r_hall2_2", "east", 0);
    add_exit(RIBOS_DIR + "castle/k_bed",     "down", 0);
    reset_room();
}
 
