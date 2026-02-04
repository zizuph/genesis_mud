/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * r_hall2_2.c
 *
 * Vader
 * Recoded by Sorgum 950712
 *
 *  Modified: 16 June 2003, by Bleys
 *      - Expanded guarded() significantly. Previously it just
 *          checked for the presence of a guard when deciding
 *          if the mortal could pass by, and it gave an odd
 *          message when the exit was blocked. It now checks
 *          if any of the guards in the room can see, and
 *          provides an appropriate message if so. This means
 *          that mortals can now sneak past the guards.
 *
 */

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/ribos/castle/local.h"
#include <macros.h>

inherit CASTLE_DIR + "hall_room";

string guard = CASTLE_DIR + "monster/trsguard";

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({guard,
             guard,
             guard
             });
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() + 
	     "It continues south.  Pleasant smells come from the " +
	     "west.  There is an important looking room to the north.\n");
    
    add_exit(CASTLE_DIR + "r_hall2_1", "south",     0);
    add_exit(CASTLE_DIR + "harem",     "west",      0);
    add_exit(CASTLE_DIR + "treas_ent", "north",     "@@guarded");

    reset_room();
}

/*
 * Function name: guarded
 * Description:   Don't let player pass if guards are present
 *                  and can see the mortal.
 * Returns:       1 if any of the guards can see the mortal, 0 if not.
 */
public int
guarded()
{

    object *contents = all_inventory();
    object item;

    int guard_len = strlen(guard);
    int i;


    // If you just check for the presence of one of the guards,
    //  then test if that guard can see, players can get past
    //  easily by blinding the first guard and then walking past.
    //  But what if the other guards can still see? They won't
    //  let him just walk on by.
    for ( i = 0 ; i < sizeof(contents) ; i++ )
    {
        item = contents[i];

        if ( wildmatch(guard + "*", file_name(contents[i])) )
        {
            if ( CAN_SEE(contents[i], TP) )
            {
                write(item->query_The_name(TP) + " stops you.\n");
                return 1;
            }

        }

    }

    return 0;

}
