/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave07.c
 *
 * A cave room that is home to two orc guards.
 */

#include "/d/Terel/include/Terel.h"
inherit ORC_CAVE_DIR + "cave_room";

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    int i;
    int nrocks;
    string *list = ({ORC_CAVE_DIR + "monster/orcguard"});

    if (random(10) > 4) {
	nrocks = random(3) + 2;
	for (i = 0; i < nrocks; i++)
	    list += ({"/d/Shire/common/obj/random_rock"});
    }
    return list;
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() + "This room is a little bigger than the others.  " +
	     "@@longdesc");

    DARK;
    
    add_exit(ORC_CAVE_DIR + "cave06", "west");
    add_exit(ORC_CAVE_DIR + "cave08", "northeast");
    add_exit(ORC_CAVE_DIR + "cave12", "east");
    reset_room();
}

/*
 * Function name: longdesc
 * Description:   Change the long desc of the room to reflect the presence
 *                or absence of the orcguard.
 * Returns:       The string with the description.
 */
public string
longdesc()
{
    if (present("orcguard"))
	return "The heavily equipped guard is doing some shadow-fencing.\n";

    return "It looks like there has been a lot of fighting here lately.\n";
}

/*
 * Function name: smell_desc
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */ 
public string
smell_desc()
{
    return "There is a smell of foul creatures in the air.\n";
}
