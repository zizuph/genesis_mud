/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * g_quart_room.c
 *
 * Ribos Castle guard quarters
 *
 * Vader
 * Recoded by Sorgum 950602
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
    return ({CASTLE_DIR + "monster/c_guard"});
	   
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Guards quarters");
    set_long("These quarters are provided for the honour guards " +
	     "so that they may be close to their duty positions at " +
	     "all times.  There are several beds lining one wall.  " +
	     "Light comes in through a a window in the north wall.\n");

    INSIDE;

    add_item(({"bed", "beds"}), "They are all neatly made.\n");

    add_item(({"window"}), "Outside, you see several honor guards " +
              "training.\n");
}
