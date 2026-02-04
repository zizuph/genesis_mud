
inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define WELL "/d/Terel/common/town/mansion/crt/well"
#define BASKET "/d/Terel/common/town/mansion/crt/basket"
#define DIR "east"

#define INITADD add_action("do_dive","dive"); \
	add_action("do_breath","take"); \
	this_player()->add_prop("_breath",6); \
	this_player()->add_prop("_breath_int",2); \
	this_player()->add_prop("_breath_int_times",7);

/* THIS_LEVEL: level used for well-basket */

#define THIS_LEVEL 4

#include "level.h"

int
do_dive(string str)
{
    write(break_string("As you dive into the water, you suddenly become " +
	"aware that there's no air available under water - you hope you " +
	"took breath before you dived... otherwise you could drown, and " +
	"that means die... so take care for your health state and don't " +
	"stay under water for too long!!\n",70));
    this_player()->move_living("into the water",MANSION + "crt/Dive1");
    return 1;
}

int
do_breath(string str)
{
    if (str != "breath") return 0;
    this_player()->add_prop("_breath",10);
    write("You take a deep breath of air and prepare to dive...\n");
    say(QCTNAME(this_player()) + 
	" takes a deep breath of air and prepares to dive...\n");
    return 1;
}


create_room() {
    set_short("In the well");
    set_long("@@long_desc2");
    add_item("basket","@@desc_basket");
    add_item("rope","@@desc_rope");
    add_item("loam","You had better not touch that disgusting humid loam..\n");
    add_item("stones","Those stones are scattered on the shaft of the well.\n");
    add_item("ledge","This is a very narrow ledge, so you had better take care.\n");
    add_item("water",break_string(
	"The water looks very dirty and smells of decay. " +
	"There must be some ground water at this depth. There seems to be " +
	"a sort of underwater tunnel system below...\n",70));
    add_item("tunnel",break_string(
	"You really can't make out the tunnel system from here because the " +
	"water is too dirty. I guess you can't avoid going underwater to " +
	"get more to know about it....\n",70));
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_HAS_WATER,1);
}

string
long_desc2()
{
    return(break_string("You find yourself at the bottom of a very, very deep " +
	"well. Hopefully you'll manage to get out of it again... " +
	(basket_here() ? "Good thing the basket with the rope " +
		"is here!" : "There's no basket visible.... you " +
		"feel very lost and alone down here...") +
	" Unlike the " +
	"areas above, this location is very humid. Actually, you're " +
	"standing in dirty water up to your knees. You wonder " +
	"where all the water comes from. It's too dirty to see from " +
	"here, but there seems to be a sort of underwater tunnel " +
	"system below, deep in the water. The walls here " +
	"consist of humid, dirty loam that build, together with " +
	"scattered stones, the wall of the shaft. It smells of " +
	"decay.\n",70));
}


