/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * vader_ent.c
 *
 * Vader
 * Recoded by Sorgum 950712
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDROOM;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Entrance chamber");
    set_long("You have entered what appears to be an entrance " +
	     "chamber.  A large, magical looking orb lights this " +
	     "room.  Along the walls are various curios and " +
	     "artifacts, probably collected by someone long " +
	     "ago.  To your north, you see an archway, leading " +
	     "into some kind of workroom.  There is a blue " +
	     "glow surrounding this archway.  To your east and " +
	     "west are other archways, these without the " +
	     "blue glow.  The hallway is back to your south.\n");

    add_item(({"curios", "artifacts"}), 
	     "Little trinkets and artifacts from all over Genesis.  " +
	     "You see a few things that you recognize, such " +
	     "as a Calian Medallion, a Holy Cross of the Bath, " +
	     "and a painting of some great magician, which you think " +
	     "might be Lars.\n");

    add_item(({"orb"}), 
	     "This fragile looking orb floats in the air, high above " +
	     "your head.  It emanated a powerful light, but it does " +
	     "not hurt to look directly at it.\n");

    add_item(({"archway"}),
	     "These are ornate archways, decorating the paths " +
	     "to the north, west, and east.  The one to the north " +
	     "looks protected.\n");

    INSIDE;

   add_exit(CASTLE_DIR + "vader_hall",  "south", 0);
   add_exit(VADER_DIR + "workroom",     "north", "@@wizcheck");
   add_exit(CASTLE_DIR + "vader_den",   "west", 0);
   add_exit(CASTLE_DIR + "vader_study", "east", 0);
}

/*
 * Function name: wizcheck
 * Description:   Don't let player pass
 * Returns:       1
 */
public int
wizcheck()
{
    write("You do not feel ready to enter this doorway.\n");
    return 1;
}

