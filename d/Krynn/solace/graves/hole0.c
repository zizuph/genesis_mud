/* The old graveyard
 *
 * Dorak
 */

#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit INSIDE_BASE;

void
create_solace_room()
{
    set_short("Empty Grave");
    set_long("You are standing in a big hole. It is dark down here and the\n"+
             "smell of fresh earth is strong in your nostrils. It is well\n"+
             "dug and deep.\n");

    add_item(({"hole", "big hole"}),
        "This is a very deep grave.  You wonder if it was dug for you.\n");
    add_item("dirt",
        "The walls of this grave are made of dirt. There are a few earth-\n"+
        "worms just vanishing from sight and some tree roots sticking out\n"+
        "of the east wall.\n");
    add_item(({"worms", "worm", "earthworms", "earthworm"}),
        "You don't see any more earthworms, they all vanished from \n"+
        "sight.\n");
    add_item(({"tree roots", "roots", "tree root", "root"}),
        "The grave digger missed a few roots, that still protrude out\n"+
        "into this empty grave.\n");
    add_item("east wall",
        "It looks much like all the other walls, except there are some \n"+
        "roots sticking out of it.\n");
    
    add_exit(TDIR + "grave14", "up", "@@up_msg");
    set_alarm(8.0,0.0,"diggerhere");
    set_alarm(20.0,0.0,"diggerarrive");

    LIGHT
}

up_msg()
{
     write("You get more dirt in your boots.\n");
     return 0;
}

void
diggerhere()
{ 
     seteuid(getuid(this_object()));
     if (!present("digger1"))
     	clone_object(MONSTER + "digger1")->move_living("xx", TO);
     set_alarm(10.0,0.0,"diggersay");
}

void
diggersay()
{
    object ob;

    if (ob = present("digger1"))
	ob->command("emote shouts: Hey, watch where you walk !! You might " +
	    "look where your\nwalking " +
            "once in a while, you clutz! HEY FRED, BRING ME MY SHOVEL !!!! " +
            "I'VE\nGOT AN INTRUDER HERE AND I WANT TO CHASE HIM OUT !! " +
	    "FRED!! " +
            "FRED, YOU LAZY GOOD\nFOR NOTHING WHERE ARE YOU.");
}

void
diggerarrive()
{
    object ob;

    seteuid(getuid(this_object()));
    if (!present("digger2"))
        clone_object(MONSTER + "digger2")->move_living("xx", TO);
    if (ob = present("digger2"))
    	ob->command("emote yells: " +
            "What are you shouting about, your shovel, it's\nmy shovel " +
	    "and I'd " +
            "like to know what YOU DID WITH IT. Intruder bah, I'm going\nto " +
            "BASH you!!!");
}
