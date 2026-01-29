/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * p_office.c
 *
 * The Ribos Post office
 *
 * Vader
 * Recoded by Sorgum 950602
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
    return ({RIBOS_DIR + "obj/letter"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Ribos Post Office");
    set_long("This was the Post Office of Ribos.  It used to be " +
	     "where the residents sent mail to their loved ones.  " +
	     "Now, it lies deserted along with the rest of the town.  " +
	     "On the northeast wall, you can see a massive claw mark, " +
	     "and there is blood on the north wall.\n");

    add_item(({"claw mark", "claw marks"}), "It was an incredible creature " +
             "that did this!\n");

    add_item(({"blood"}), "It looks several days old.  It's a brownish " +
             "color now.\n");

    INSIDE;

    add_exit(RIBOS_DIR + "road12", "southwest", 0);
    reset_room();
}
