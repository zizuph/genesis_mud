/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * path3.c
 *
 * Vader
 * modified by Sorgum 950707
 *
 *  Modified: 3 May 2003, by Bleys
 *      - fixed some typos
 *
 *  Modified: 19 Sep 2003, by Bleys
 *      - fixed a typo in do_enter()
 *
 *
 */

#include "/d/Terel/include/Terel.h"
#include <cmdparse.h>

inherit STDROOM;

#define MOQ_DIR             "/d/Terel/mecien/valley/guild/quest/"
#define NO_OF_FLOWERS       3

int nof;

int pick(string str);
int enter(string str);

public void  
reset_room()
{
    ::reset_room();
    nof = NO_OF_FLOWERS;
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    add_action(enter, "enter");
    add_action(pick, "pick"); 
    ::init();
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("An icy road");
    set_long("You are now at the edge of an icy cliff.  " +
	     "Looking down, you can barely make out a small settlement.  " +
	     "This settlement, however, appears inaccessible. It is " +
	     "surrounded entirely by cliffs similar to this one. You " +
	     "wonder how anyone got down there. It is bitterly cold " + 
	     "here. Your hair is literally frozen. You notice that " +
	     "there are green bushes on the ground of a variety that " +
	     "don't do well in the cold. It is strange that they could be " +
	     "alive!\n");

    add_item(({"bush", "bushes"}),
	     "They are lush, tall, and green bushes  that look like " +
	     "they do not belong here.  One bush in particular looks " +
	     "darker than the others.\n");
    
    add_item(({"darker bush", "dark bush"}),
	     "This bush is darker than the rest.  Perhaps " +
	     "there is something behind it.\n");
    
    add_item(({"ground"}),
	     "On the frozen ground some flowers grow beside the bushes.\n");

   add_item(({"flower", "flowers"}), "They are glorious orange flowers " +
  "that shine brilliant, blooming up to the sun.\n");

    add_exit(RIBOS_DIR + "path2", "east", 0);
    set_dircmd("bush");
    reset_room(); 
}

/*
 * Function name: enter
 * Description:   Handle the enter action
 * Returns:       1/0
 */
public int
enter(string str)
{
    if(!str || (str != "bush")){
	NF("Enter what?\n");
	return 0;
    }
    this_player()->move_living("through the bush",
			       RIBOS_DIR + "cave_entrance", 1);
    return 1;
}

/*
 * Function name: pick
 * Description:   Handle the pick action
 * Returns:       1/0
 */
public int
pick(string what)
{
    object ob;

    NF("Pick what?\n");
    
    if ((!what) || (what != "flower"))
	return 0;

    if (nof <= 0) {
	write("There are no flowers left to pick!\n");
	return 1;
    }

    nof--;
    ob = clone_object(MOQ_DIR + "flower");
    ob->move(TP);
    write("You pick a flower.\n");
    say(QCTNAME(TP) + " picks a flower.\n");
    return 1;
}
