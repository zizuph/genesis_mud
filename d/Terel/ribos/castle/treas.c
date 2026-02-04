/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * m_hall1_1.c
 *
 * Vader
 * Recoded by Sorgum 950708
 *
 * Updates:
 * Lilith, Dec 2021 typo fixed immeadiatly -> immediately
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDROOM;

public int enter(string str);
int rtime;

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({CASTLE_DIR + "monster/trsguard2",
	     CASTLE_DIR + "monster/trsguard",
             CASTLE_DIR + "obj/treas_chest" });		 
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    
    ::create_room();
    set_short("Treasury");
    set_long("Here is where the Kingdom of Ribos keeps all of its precious " +
	     "valuables.  Not just gold coins, but priceless jewels, rare " +
	     "tapestries, and even its important papers.  You get the " +
	     "feeling that they were expecting people like you.  Virtually " +
	     "all of the valuables are protected by magic.  There is no way " +
	     "you can take anything, at least, not without the help of a " +
	     "great magician.  Along the west wall, you see a huge " +
	     "tapestry.  It covers the entire wall.\n");

    add_item(({"tapestry"}), 
	     "This is a huge tapestry.  It is unlike any you " +
	     "have seen before, because instead of an image of " +
	     "a great battle, or elegant people, " +
	     "it is a picture of a stone spiral staircase.\n");

   add_item(({"coins", "gold", "gold coins"}), 
	    "Stacks upon stacks of gold coins.....enough to last you an " +
	    "eternity, awaits you behind the unstoppable wall of a magic " +
	    "spell.\n");

    add_item(({"jewels", "jewelry"}), 
	     "These fine items are only worn by the royal family.  You " +
	     "have never seen anything of the like before.  They look to " +
	     "be worth a great deal of platinum, but your dreams of " +
	     "wealth are extinguished by the barrier of a magic spell.\n");

    add_item(({"tapestries"}), 
	     "These are rare tapestries, kept in mint condition, and too " +
	     "valuable to hang in the castle, where the elements could " +
	     "cause them to deteriorate.\n");

    add_item(({"papers", "important papers"}), 
	     "Blah blah blah.  Boring stuff.  Treaties, historic orders, " +
	     "and other dull stuff.  You notice that one set of papers " +
	     "are rather new and not protected by a magic spell.\n");

    FIX_EUID;
    clone_object(DOOR_DIR + "t_out")->move(TO);
    
    INSIDE;

    reset_room();
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
   ::init();
   add_action(enter, "enter");
}

/*
 * Function name: enter
 * Description:   Handle the enter action
 * Returns:       1/0
 */
public int
enter(string str)
{
    if(!strlen(str) || (str != "tapestry")) {
	NF("Enter what?\n");
	return 0;
    }
    
    write("Like an utter fool, you walk into the tapestry, knowing full " +
	  "well that you will break your nose on the wall that is " +
	  "behind it.  You prepare yourself for the impact, closing " +
	  "your eyes in anticipation of the pain. Instead of a " +
	  "collision, you pass through the tapestry.  You don't " +
	  "notice that the stairs start immediately at the edge of " +
	  "the tapestry.  You tumble down two flights of stone " +
	  "spiral stairs, landing in a heap at the bottom.\n");

    TP->move_living("through the tapestry", CASTLE_DIR + "storage7");

    say(QCTNAME(TP) + " walks into the tapestry....and disappears!\n");
    
    (RIBOS_DIR + "dragon_cave")->open_the_door();
    return 1;
}

void
enter_inv(object ob, object from)
{
    object scrappy, chest;
    
    ::enter_inv(ob, from);


    if (time() > rtime)
    {
        chest = present("box");
        chest->reset_chest();
        rtime = time() + 22000;
    }

    if (!interactive(ob) || ob->query_wiz_level())
	return;
    
    scrappy = present("scrappy");

    if (scrappy)
	set_alarm(1.0, -1.0, "do_it", ob, scrappy);	
}

do_it(object ob, object scrappy)
{
    scrappy->lambaste(ob);
}
