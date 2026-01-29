// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/s7.c
// creator(s):       unknown
// revisions:        Casca, 11/13/99
// 		     Lucius & Zielia, AUG 2007
// purpose:          
// note:             
// bug(s):           
// to-do:            

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/dark/darkl2_base.c";

/* Include the local area defines, etc */
#include "../dark.h"  

/* Now create the room.  */
public void
create_tunnel_room(void)
{
    set_short("before the rift");
    set_long("The new tunnel that you have been traveling comes to a "+
        "dead-end here. The northwest wall shows a large rift that recent "+
        "construction efforts have unveiled. Pale light gleams against "+
	"the rough rock of the fissure from the room beyond. "+
        "Baskets and tools lay amid piles of recently extracted stone.\n");

    add_exit("s6","southeast",0);
    /*
     * Put additional add_items below. 
     */
    add_r_tunnel();
    add_new_tunnel();

    add_item(({"basket","baskets"}),
        "Several baskets are scattered about the area. They "
        + "are filled to various degrees with stones and "
        + "debris from the construction.\n");
    add_item("northwest wall",
        "The northwest wall is heavily scarred with pickaxe "
        + "and chisel marks. Running nearly from floor to ceiling "
	+ "is a large rent in its surface. It's apparent that construction "
        + "is still underway on this portion of wall.\n");
    add_item("tools",
        "You notice some chisels laying amidst the debris "
        + "as well as a couple sledgehammers leaning against "
        + "the wall.\n");
    add_item(({"rent","fissure","rift"}),
	"In the middle of the northwest wall is a newly uncovered "
	+ "rift. The fissure tears through the rock from nearly "
	+ "floor to ceiling. A pale glow rests on its rough "
	+ "contours from some inner source, revealing scratches "
	+ "on them.\n");
    add_item("scratches",
	"Looking closer, they appear to be fingernail, or even "
	+ "claw marks, as if one of the large goblin labourers "
	+ "had tried to crawl through.\n");
    add_item(({"glow","pale glow","light","pale light"}),
	"Gleaming on the rough, pickaxe-scarred walls of the "
	+ "fissure is a pale light, its source the room beyond.\n");
    add_item(({"other room","room beyond"}),
	"The rent in the northwest wall is actually curved "
	+ "slightly, making it impossible to find an angle "
	+ "of view into the room beyond.\n");

    reset_tunnel_room();
}

public int
f_crawl(string str)
{
    if (!strlen(str))
	return 0;

    if (!parse_command(str, ({}),
	    "'through' [the] 'rift' / 'fissure' / 'rent'"))
	return notify_fail("Crawl through what?\n");

    if (TP->query_race_name() == "ogre")
    {
	notify_fail("You're way too big to fit through there.\n");
	return 0;
    }	
	
    write("You crawl your way through the rent in the wall.\n");
    say(QCTNAME(TP) +" crawls through a rent in the wall.\n");

    TP->move_living("M", L2 + "rift_room", 1, 0);
    say(QCTNAME(TP) +" arrives crawling through a rent in the wall.\n");

    return 1;
}

public void
init(void)
{
    ::init();

    add_action(f_crawl, "crawl");
}
