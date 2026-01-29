/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * legion_room.c
 *
 * A generic room in the legion of darkness.
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#define MONSTER_DIR LOD_DIR + "monster/"

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
/*    add_action("do_smell",  "smell",  0);*/
}

/*
 * Function name: query_monster_list
 * Description:   return list of monsters to clone at each reset.
 */
/*public string*
query_monster_list()
{
    return ({ });
}*/

/*
 * Function name: reset_room
 * Description:   clone monsters at each reset.
 */
/*public void
reset_room()
{
    int i;
    object monster;
    string *monster_list;

    monster_list = query_monster_list();
    for (i = 0; i < sizeof(monster_list); i++) {
	
	if ((i == 0) && present(monster_list[0]))
	    return;
	
	monster = clone_object(MONSTER_DIR + monster_list[i]);
	monster->move_living("arrives", TO);
    }
}
*/

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    INSIDE;
}
    
