/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road_room.c
 *
 * A generic road room in Ribos
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

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
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    
    add_item(({"house", "houses", "homes"}), "These homes were once " +
    "beautifull, with well kept shrubs and colorfull rooftops.\n");

}
    
