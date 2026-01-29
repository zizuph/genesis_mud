/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * intsec4.c
 *
 * An intersection in Ribos
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("An intersection");
    set_long("You now stand at an intersection in front " +
	     "of the Castle of Ribos.  A paved road leads north to it.  " +
	     "To your south, stands the church.  It, however, is closed " +
	     "for remodeling.  You note that the castle looks splendid, " +
	     "despite the condition of the rest of the town.\n");

    add_item(({"castle"}), "It is splendid looking.  Truly a castle " +
             "fit for a king.\n");

    add_item(({"church"}), "It is closed for now, but you can tell " +
             "that the King supports it.\nThere are massive spires, tall " +
             "stain windows, and the\nentire building is made from marble.\n");

    add_exit(RIBOS_DIR + "castle/cas_ent", "north", 0);
    add_exit(RIBOS_DIR + "road7",   "west",  0);
    add_exit(RIBOS_DIR + "road8",   "east",  0);
    add_exit(RIBOS_DIR + "church1", "south", "@@closed");
}

/*
 * Function name: closed
 * Description:   VBFC to handle closed exit
 * Returns: 1
 */
public int
closed()
{
   write("The church is still under construction.  Sorry.\n");
   return 1;
}
