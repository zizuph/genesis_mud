
inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BASKET "/d/Terel/common/town/mansion/crt/basket"

/* THIS_LEVEL: level used for well-basket */

#define THIS_LEVEL 0

/* basket_here: returns 1 if basket is on this level */
int
basket_here()
{
    seteuid(getuid());
    if (THIS_LEVEL == BASKET->query_level())
	return 1;
    return 0;
}

/* rope_here: returns 1 if rope is visible */
int
rope_here()
{
    seteuid(getuid());
    if (THIS_LEVEL <= BASKET->query_level())
	return 1;
    return 0;
}

create_room() {
    set_short("At the well");
    set_long("@@long_desc");
    add_item("basket","@@desc_basket");
    add_item("rope","@@desc_rope");
    add_item("handle","It looks like an ordinary handle you often " +
	"find on those wells.\n");
    add_item("water","You don't see any water - maybe there's some " +
	"at the bottom of the well?\n");
    add_item("well",break_string("You recognize that well as one of " +
	"those you often see with a basket on a rope and a handle " +
	"on its side. This well seems " +
	"to be very deep though, you can't figure out it's bottom..\n",70));
    add_item("bench",break_string("This bench looks very old and rotten. " +
	"it looks so unstable you decide not to sit on it - moreover it's " +
	"covered with old and dried bird shit...\n",70));
    add_item("weeds","The weeds look like extremely resistant weeds...\n");
    add_item("mushrooms",break_string("There are different mushrooms " +
	"in different strange colors growing around the rim of the well. " +
	"Better you don't try to eat them..\n",70));
    add_item("bird shit","Oh boy, if your mother knew that you play with " +
	"bird shit all day long!\n");
    add_item("shit","Oh boy, if your mother knew that you play with " +
	"bird shit all day long!\n");
    add_exit(MANSION + "crt/gard22","northwest",0);
    add_exit(MANSION + "crt/gard23","northeast",0);
    add_exit(MANSION + "crt/gard32","southwest",0);
    add_exit(MANSION + "crt/gard33","southeast",0);
}

string
desc_rope()
{
    if (rope_here())
	return(break_string("The rope is connected to the " +
	"handle of the well. You can't make out the other end " +
	"of the rope, but you imagine there's something hanging " +
	"on it inside the well.\n",70));
    return("Hmmm... you don't see any rope here...\n");
}

string
desc_basket()
{
    if (basket_here())
	return BASKET->query_desc();
    return("Hmmm... you don't see any basket here...\n");
}

init()
{
    ::init();
    add_action("enter_basket","enter");
    add_action("turn_handle","turn");
    add_action("turn_handle","crank");
    add_action("pull_rope","pull");
}

int
enter_basket(string str)
{
    notify_fail("Enter what?\n");
    if (str != "basket") return 0;
    notify_fail("But there's no basket here..\n");
    if (!basket_here()) return 0;
    notify_fail("But the basket is already occupied..\n");
    if (BASKET->TAS()) return 0;
    this_player()->move_living("into basket",BASKET);
    return 1;
}


int
pull_rope(string str)
{
    notify_fail("Pull what?\n");
    if (str != "rope") return 0;
    notify_fail("But there's no rope here...\n");
    if (!rope_here()) return 0;
    BASKET->pull_notify(0);
    write("You pull the rope...\n");
    say(QCTNAME(this_player()) + " pulls the rope.\n");
    return 1;
}

int
turn_handle(string str)
{
    string *arr;
    int i,dir;

    notify_fail("Yes, but what exactly you try to turn or wind? " +
	"your destiny? ;--)\n");
    if (strlen(str) < 6) return 0;
    arr = explode(str," ");
    if (arr[0] != "handle") return 0;
    notify_fail("Yes, but to what direction?\n");
    dir = 0;
    for (i=1; i<sizeof(arr); i++)
    {
	if (arr[i] == "left" || arr[i] == "counterclockwise") {dir = 1; break;}
	if (arr[i] == "right" || arr[i] == "clockwise") {dir = 2; break;}
    }
    if (!dir) return 0;
    notify_fail("You try to turn the handle to the left, but it blocks.\n");
    if (dir == 1)
    {
	if (!(BASKET->query_level())) return 0; /* basket is at top alrady */
	notify_fail(break_string(
	   "You try to turn the handle to the left, but it seems " +
	   "the weight hanging on the rope is too heavy for you to lift. " +
	   "Either you're too weak, or you carry too much stuff...\n",70));
	if (this_player()->query_prop(OBJ_I_WEIGHT) + BASKET->query_load()
		> this_player()->query_prop(CONT_I_MAX_WEIGHT))
	{
	    BASKET->notify_tooheavy();
	    return 0;
	}
        notify_fail("You try to turn the handle to the left, but it blocks.\n");
	if (!(BASKET->up())) return 0;
	write("You turn the handle to the left.\n");
	say(QCTNAME(this_player()) + " turns the handle to the left.\n");
	return 1;
    }
    notify_fail("You try to turn the handle to the right, but it blocks.\n");
    if (!(BASKET->down())) return 0;
    write("You turn the handle to the right.\n");
    say(QCTNAME(this_player()) + " turns the handle to the right.\n");
    return 1;
}
    
notify(string arrdep, string dir)
{
    tell_room(this_object(),
	"Suddenly, a basket on a rope " + arrdep + dir + ".\n");
}

pull_notify()
{
    tell_room(this_object(),
	"Suddenly, the rope moves. Probably somebody pulled it below.\n");
}

string
long_desc()
{
    return(break_string("You find yourself in the middle of a " +
	"wicked garden, on the top of a small hill. Four paths " +
	"lead down to the garden. " +
	"This place looks very scary. It must once have " +
	"been a very nice location, with a well and a bench next to it - " +
	"the well probably once supplied the mansion with water, and you " +
	"can imagine people relaxed on the bench enjoying the flowers " +
	"and the sun. Nothing remained of those days though... The well is " +
	"dried out, or the water is very low so you can't see it. " +
	(basket_here() ? "There's a huge basket on a rope in the well, " +
		"but it doesn't look very stable. " : 
		"There's a rope hanging in the well, but you can't " +
		"make out its end. ") +
	"The bench looks rotten and you decide better not to sit on it. The " +
	"flowers of past times have decayed, only some weeds and mushrooms " +
	"survived.\n",70));
}


