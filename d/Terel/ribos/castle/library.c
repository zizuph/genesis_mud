/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * library.c
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
    return ({CASTLE_DIR + "monster/weakguard"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Royal Library");
    set_long("The magnificent library of the Ribos castle used to " +
	     "be the premiere library in the land, but the " +
	     "Avenchir's ammassed a collection that " +
	     "put it to shame.  Many years ago, the king donated " +
	     "all of his books to the Avenchir library, keeping " +
	     "only private books in a private part " +
	     "of this library.\n");
 
    add_item(({"books", "shelves", "library"}),
	     "All of the books are on permanent loan to the " +
	     "Avenchir Library.  Sorry.\n");
 
    INSIDE;
   
    add_exit(CASTLE_DIR + "r_hall2_1", "west", 0);

    reset_room();
}
 
