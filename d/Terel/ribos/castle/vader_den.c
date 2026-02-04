/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * vader_hall.c
 *
 * Vader
 * Recoded by Sorgum 950712
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDROOM;

public int do_sit(string str);

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();

    set_short("A small den");
    set_long("This small circular chamber is quite quaint.  " +
	     "In the middle is a large comfortable looking chair " +
	     "that you can sit in.  In front of that is a small " +
	     "foot rest.  At its side is a small table, atop " +
	     "which stands a wine goblet.  Light seems to fill " +
	     "the room, but you cannot see the source.  Many " +
	     "furs and pelts from animals give the room a homely " +
	     "feeling, as well as a leatherlike fragrance.  An " +
	     "exit is to the east, and there is a large, dark " +
	     "hole in the ceiling.\n");

    add_item(({"chair", "large chair", "comfortable chair"}),
	     "This chair is upholstered in leather, and has " +
	     "a high back.  It looks very comfortable, and inviting.\n");

    add_item(({"foot rest"}), 
	     "A small footrest, with a soft white fur that feels " +
	     "great against the bare foot.\n");

    add_item(({"table", "small table"}),
	     "This table sits beside the chair, and is a convenient " +
	     "place to put a book, or glass of wine on while sitting " +
	     "at the chair.\n");

    add_item(({"hole", "dark hole", "large dark hole"}), 
	     "It is dark and forboding.  It goes up so high " +
	     "that you cannot see the top.  No light comes from " +
	     "it either.\n");

    add_item(({"furs", "pelts"}),
	     "They come from various animals around the area.  " +
	     "They give the room a lived in feeling.\n");

    add_item(({"goblet", "wine goblet"}), 
	     "A fine wine goblet, made from silver, sits here " +
	     "clean, ready to be filled with wine.\n");

    INSIDE;
    add_prop(OBJ_S_WIZINFO, 
	     "If you sit in the chair, you will be returned to " +
	     "the ground level of the castle.  It is the only " +
	     "exit from this area.\n");

    add_exit(CASTLE_DIR + "vader_ent", "east", 0);
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
   ::init();
   add_action(do_sit,  "sit");
}

/*
 * Function name: do_sit
 * Description:   Handle the sit action
 * Returns:       1/0
 */
public int
do_sit(string str)
{
    if (!strlen(str) || ((str != "on chair") && (str != "in chair"))) {
	NF("Sit where?\n");
	return 0;
    }
	
    write ("As you settle into the chair, its ejection system notices that " +
	   "you are not the owner.\n");
        
    say(QCTNAME(TP) + " sits in the chair, and the chair rumbles.\n");
    say(QCTNAME(TP)+" is sent flying through a hole in the ceiling by the " +
	"chair's ejector system.\n");

    write ("The chair sends you flying through the hole in the ceiling.\n");
    write ("You fly higher and higher.  You ears start to pop!\n");
    write ("You arrive in a hallway.\n");

    TP->move_living("M", CASTLE_DIR + "m_hall1_2");
    tell_room(CASTLE_DIR + "m_hall1_2", QCTNAME(TP) + " pops up out of a " +
	      "hole in the floor!\n", TP);
    return 1;
}
