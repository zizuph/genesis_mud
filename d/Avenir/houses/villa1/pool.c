/*
 * villa1/pool.c
 *
 * Lilith, Feb 2022
 *
 * This is an emote room like the bathhouse in the City.
 *
 */

#pragma strict_types

#include "villa1.h"
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

inherit "/d/Gondor/common/lib/drink_water.c";
inherit V1 +"housebase";
inherit "/lib/commands";
inherit "/d/Avenir/inherit/emotes";

#define SEE_EAST    ({ V1 +"garden" })
#define SEE_WEST    ({ V1 +"terrace_w" })
#define SEE_SOUTH   ({ V1 +"living", })

public string
east_view(void)
{
    string str;
    object *live = get_view(SEE_EAST);

    if (!sizeof(live))
	return "From the east, the scent of herbs and flowers waft.";
    if (sizeof(live) > 1)
	str = "seem";
    else 
	str = "seems";
    return COMPOSITE_LIVE(live) +" "+ str +" to be enjoying the garden "+
    "just to the east. ";
}


public string
west_view(void)
{
    string str;
    object *live = get_view(SEE_WEST);

    if (!sizeof(live))
	return "A fire pit with seating around it lies directly west";
    if (sizeof(live) > 1)
	str = "appear";
    else 
	str = "appears";    
    return "Directly west is a fire pit with some seating, where "+
    COMPOSITE_LIVE(live) + " "+ str +" to be enjoying the sights";
}


/*
 * Function name:        create_house_room()
 * Description  :        Creates a house room from from the base file
 *                       "housebase.c"
 */

void 
create_house_room()
{
    add_exit("terrace_c", "south", 0, 0, 1);
    add_exit("garden",    "east", 0, 0, 1);
    add_exit("terrace_w", "west", 0, 0, 1);

    set_short("hot spring pool");
    set_long("Wisps of mist curl and glide across the surface of this "+
      "pool which is fed from below by a hot spring. Water dribbles "+
      "over the southern edge and down toward the beach. "+
      "The temperature is delicious: warm enough to tingle a bit "+
      "when you first enter, but not so hot that you can only spend a "+
      "few minutes enjoying it. "+
      "@@east_view@@ "+
      "South is the terrace that leads between the pool and "+
      "the lounging area that is at the center of the villa. "+
      "@@west_view@@."+
      "\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    set_drink_from(({"pool", "hot spring"}));

    set_items_outdoor();
    set_items_stone();

    add_help_topic("pool",  "/d/Avenir/houses/help/pool_help");
    add_help_topic("here",  "/d/Avenir/houses/help/pool_help");
    add_help_topic("room",  "/d/Avenir/houses/help/pool_help");


    add_item(({"pool edge", "southern edge", "edge" }),
      "The water dribbles over the southern edge of the pool "+
      "and down the rocks toward the beach below.\n");
    add_cmd_item(({"pool edge", "southern edge", "edge" }), "feel",
      "It has been worn smooth by the flow of the water.\n");
    add_item(({"pool", "hot spring pool", "bottom", "tiles",
	"lapis lazuli tiles", "lapis lazuli", "bottom of pool",
	"blue", "azure", "azure blue"}),
      "The bottom of the pool is tiled in lapis lazuli, "+
      "giving the warm water of the hot spring a stunning "+
      "azure blue color. Wisps of mist float here and there "+
      "along the surface of the water, evidence that it is "+
      "much warmer than the surrounding air.\n");	
    add_item(({"warm water"}), "The water is warm and clear.\n");
    add_cmd_item(({"water"}), "feel",
      "The water feels deliciously warm.\n");	
    add_item(({"garden", "herbs", "flowers"}),
      "The mists partially obscure the garden so that the "+
      "details are almost dreamlike in their softness.\n");
    add_item(({"firepit", "fire"}),
      "A hollow has been carved into the limestone and wood "+
      "stacked inside for a fire.\n");	
    add_item(({"living area", "lounging area"}),
      "There are some couches there, and a table.\n");		
    add_item(({"kitchen", "front hall", "bedroom", "water garden"}), 
      "You can't really see it from here.\n");
    add_item(({"east"}), "The garden lies east of here.\n");
    add_item(({"west"}), "There is a seating area there.\n");
    add_item(({"north"}), "You see the sea of Sybarus and some of "+
      "the islands.\n");
    add_item(({"south" }), "The main terrace is south of here.\n");


    start_room_tells();
    add_tell("A wisp of mist curls into the shape of a seahorse.\n");
    add_tell("The warm water soothes your tired body.\n");
    add_tell("A puff of herb-scented air wafts past.\n");
    add_tell("You marvel at the beauty of the lapis lazuli tiles "+
      "that form the bottom of the pool.\n");

}


public int
do_out(void)
{
    object last = TP->query_prop(LIVE_O_LAST_ROOM);

    if (!last || last == environment(TP))
	last = find_object(V1 + "terrace_c");

    say(QCTNAME(TP) +" leaves the pool for the terrace.\n");
    TP->move_living("X", last, 0);
    return 1;
}

public int
do_swim(string str)
{

    write("You swim around the pool at a languid pace.\n");
    say(QCTNAME(TP) + " swims lazily around the pool.\n");
    return 1;
}

public int
do_wash(string str)
{
    object ob;

    write("You wash away the marks of battle and travel.\n");
    say(QCTNAME(TP) + " washes away layers of dirt and grime.\n");

    while(ob = present("dirty",TP))
    {
	TP->catch_tell("You feel much less dirty now.\n");
	ob->remove_object();
    }

    return 1;
}

public int
do_splash(string str)
{
    if (!strlen(str))
    {
	write("You splash playfully in the water, feeling "
	  +"like a child again.\n");
	all(" splashes noisily about in the pool.\n");
	return 1;
    }

    object *oblist = parse_this(str, "[water] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Splash who?\n");
	return 0;
    }

    target(" splashes water in your face.", oblist);
    actor("You splash", oblist, " in the face with water.");
    all2act(" splashes", oblist, " in the face with water.");
    return 1;
}

public int
do_paddle(string str)
{
    write("You skillfully tread water.\n");
    say(QCTNAME(TP) + " looks like a dog paddling about in the pool.\n");
    return 1;
}

public int
do_dead(string str)
{
    write("Rolling onto your back, you float contentedly in the water.\n");
    say(QCTNAME(TP) + " floats on the surface of the water.\n");
    return 1;
}

public int
do_dive(string str)
{
    write("You dive under the water.\n");
    say(QCTNAME(TP) + " disappears beneath the water's surface.\n");
    return 1;
}

public int
do_dunk(string str)
{
    object *oblist;

    if (!strlen(str))
    {
	write("You dunk beneath the water. You can hear "
	  +"the sound of water lapping the pool's edge.\n");
	all(" dunks beneath the pool's surface.\n");
	return 1;
    }

    oblist = parse_this(str, "[beneath] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Dunk who?\n");
	return 0;
    }

    actor("You dunk", oblist, " underneath the water.");
    all2act(" dunks", oblist, " under the water.");
    target(" dunks your head beneath the water.", oblist);
    return 1;
}
/*
 * Function name: init
 * Description  : initialize time
 */

public void
init()
{   
    ::init();

    init_drink();

    add_action(emote,     "emote");
    add_action(do_out,    "exit");
    add_action(do_out,    "leave"); 
    add_action(do_out,    "out");	
    add_action(do_swim,   "swim");
    add_action(do_wash,   "wash");
    add_action(do_wash,   "bathe");
    add_action(do_splash, "splash");
    add_action(do_paddle, "paddle");
    add_action(do_paddle, "tread");
    add_action(do_dead,   "float");
    add_action(do_dive,   "dive");
    add_action(do_dunk,   "dunk");
}

/*
 * Function name:        drink_message
 * Description  :        Provides a description for drinking from the river
 */

public void
drink_message(string from)
{
    write("You scoop a handful of the warm spring water to your mouth " +
      "and drink it.\n");
    say(QCTNAME(TP) + " scoops a handful of the warm spring water and "+
      "drinks it.\n");
}

public int
query_prevent_snoop(void)       { return 1; }
