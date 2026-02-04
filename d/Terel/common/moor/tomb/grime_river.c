// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc


/* From the imagination of Lord Sorgum ;)  */


#include "/d/Terel/include/Terel.h"
inherit MOOR_DIR +"tomb/tomb_base";
#include "../local.h"

void
init()
{
     add_action("do_dive", "dive");
     add_action("do_dive", "jump");     	 
     add_action("do_dive", "enter");
     add_action("do_dive", "swim");          
     ::init();     
}

int
do_dive(string str)
{
    if (!strlen(str) || !parse_command(str, ({ }),
    " [down] [in] / [into] / [through] / [across] [the] 'grime' / 'mire' / 'river'", str))
    {
        notify_fail("Dive into what, the mire?\n");
        return 0;
    }

    write("You swim scross the grimy mire.\nYou are lucky this " +
          "time. You managed to find your way through it. Next time " +
          "you come here it might not be so easy!\n");
    TP->move_living("into the mire", TOMBDIR + "gore_chamber");

    return 1;     
}
     
void
create_room()
{
	::create_room();
	
	add_npc(MOBDIR +"dweller3", 2);
	add_npc(MOBDIR +"dweller4", 1);

    set_short("Grime river");
    set_long(
	"You are following a slimy expanse of hellish black mire " +
	"which extends in monotonous undulations as far as you can see. " +
	"In the air is a sinister quality that chills you to the core. " +
	"This region is putrid with carcasses of dying fish and " +
	"other more horrifying things which you see protruding from the " +
	"nasty grime.\n"
    );
  
    add_item(({"fish", "carcass", "carcasses", "tentacles", "fins"}),
    "The carcasses reek of decay.  Various tentacles and fins of " +
    "strange fish and other water creatures look gruesome.\n"
    );

    add_item(({"grime", "mire", "river"}), 
	"It looks just awful, this river of grime. "+
    "Part of you wants to dive in and explore, "+
    "but some instinct is warning you that something "+
    "terrible might happen to you if you do.\n"
    );
    
	
    add_exit("tomb_core", "south", 0);
}

