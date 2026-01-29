/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit TANTALLON_INSIDE;
		  
/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */

create_tantallon_room()
{
    set_short("The Giant Place");
    set_long(
	"You are in the Giant fellows place, mostly giants visit this\n" +
   "place since they are the only ones allowed in here. They don't\n" +
	"seem to notice you, maybe you are too small a being? There is\n" +
	"a big sign hanging at the bar on which you can read: \n\n" +
	"   Firstclass  beer      12 cc\n\n" +
	"You could go north back to the path. South is the back room\n" +
	"where the beer is being kept.\n" +
	"");

    add_item("bar", "A very big bar for big fellows.\n");
    add_item("giants",
    "They are frequently going towards the bar trading with the\n" +
	"bartender. They don't pay you any attention.\n");
    add_item("sign", "A big sign with big letters on.\n"); 
    add_cmd_item( ({ "sign", "letters" }), "read", "Firstclass beer 12 cc\n");

    add_exit(TDIR + "city10", "north", 0);
    add_exit(TDIR + "back5", "south", "@@block");

    INSIDE

    reset_room();
}

reset_tantallon_room()
{
    if (!present("bartender", TO))
	clone_object(MON + "bartender5")->move_living("xx", TO);
}

block()
{
    if (TP->query_invis())
    {
	write("You start to walk south but suddenly one giant from inside\n" +
	      "the tent takes a step towards you and you get scared that\n" +
              "he might step on you by accident since he can't see you.\n" +
	      "You take one step back instead.\n");
	return 1;
    }

    write("You start to walk south but suddenly one giant from inside\n"+
          "the tent takes a step towards you and you quickly decide\n" +
          "to stop moving.\n");
    say(QCTNAME(TP) + " starts to walk south but didn't get far.\n");
    return 1;
}


