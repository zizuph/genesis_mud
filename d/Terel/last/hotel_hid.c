/* -*- C++ -*- */

/*
 * hidden_hid
 *
 * Shinto 6/98
 * Modified 05102002 Goldberry
 *   Relocating Trevin
 * 
 * 12/8/2009 - Fixed typo in object list, Petros
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;


/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({"/d/Terel/last/npc/assassin"});

}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    set_short ("Large room in the White Dragon Inn");
    set_long ("You have entered a hidden room in the back of the " +
					      "White Dragon Inn. A small cot sits in one corner and " +
                "a lamp hangs from the ceiling.\n");
    add_item("cot","The cots looks as if it has been recently slept in.\n");
    add_item("lamp","The lamp provides the only light in this room.\n");

    add_exit(LAST_DIR+"hotel3","south",0);
    add_prop(ROOM_I_INSIDE,1);

    reset_room();
}

