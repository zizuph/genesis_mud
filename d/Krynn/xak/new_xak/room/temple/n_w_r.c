/* 
 * Xak Tsaroth - Temple of Mishakal
 * Originaly coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"

inherit INROOM;
inherit CHAPEL;

public void
create_xak_room()
{    
    set_short("In the North Worship Room");
    set_long("This is the north worship room. It was here that people " +
	     "would come to worship Mishakal. This is a rectangular room " +
	     "in sharp contrast to the circular chamber outside. Light " +
	     "streams in from windows high up on the far wall. The room " +
	     "contains several marble benches and the west wall contains " +
	     "a raised dais. The room is however quite empty.\n");

    LIGHT;

    add_item(({"bench", "benches", "marble bench", "marble benches"}), 
	     "The benches are made of good quality marble. You think that " +
	     "they were probably covered with felt but that has long " +
	     "since worn away.\n");
    add_item(({"dais", "raised dais"}), "A simple dais raised up on stone.\n");

    add_exit(TEMPLE + "chamber1", "east");
}

public void
init()
{
    init_chapel();
    ::init();
}




