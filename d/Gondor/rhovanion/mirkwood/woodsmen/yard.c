/*
 * Side yard - Gairent.
 * April 2015
 */

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <files.h>

inherit MIRKWOOD_STD_DIR + "room";

int do_climb(string str);
int do_count(string str);

void create_room()
{
    
    set_short("Side yard");
    set_long("You are currently standing in a small yard east of the " +
        "smithy in Gairent. Scattered across the yard are several " +
        "barrels, boxes, crates and assorted items too numerous " +
        "to count. In the middle of the yard, a large cart rests " +
        "up against a tall, slender maple tree. To the west, the " +
        "wall of the smithy is unbroken save for a narrow doorway. " +
        "A low, wooden fence with a locked gate surrounds the rest of the " +
        "yard, making your only way out back into the smithy.\n");

    add_item_light(({"moon","stars","sun","rising sun","setting sun","noon sun",
        "night stars", "night moon", "afternoon sun", "morning sun"}),
        "Your eyes drink in the " + VBFC("light_type") + " from " +
        "the " + VBFC("day_desc") + " " + VBFC("sun_moon") + " as it shines " +
        "all over the village of Gairent.\n", LIGHT_ALL);
    add_item_light(({"forest", "mirkwood", "Mirkwood"}),
        "This is the legendary Mirkwood forest. There have always " +
        "been stories of how dangerous this forest has been for " +
        "the unwary traveller. Here in the village of Gairent, " +
        "you are able to take a brief respite from your travels " +
        "in Mirkwood.\n", LIGHT_ALL);
    add_item_light(({"road","path","ground", "down"}),
        "While you are currently stuck inside the fenced yard, " +
        "there are several, well-worn dirt paths crossing through the " +
        "village of Gairent. Most paths connect to the shacks " +
        "and buildings of the village itself, before they eventually " +
        "combine into one larger path which leads through the western " +
        "gate before climbing the ravine and leading back into " +
        "Mirkwood forest.\n", LIGHT_ALL);
    add_item_light(({"sky", "light", "up"}),
        "You are actually able to see some of the sky here, unlike just about " +
        "anywhere else in Mirkwood. The " + VBFC("light_type") + " from " +
        "the " + VBFC("day_desc") + " " + VBFC("sun_moon") + " shines " +
        "brightly, shedding its light across the entire village. \n",
        LIGHT_ALL);
    add_item_light(({"shadow", "shadows"}),
        "The forest of Mirkwood, which completely surrounds the village" +
        "you are currently standing in, is full of sinister looking shadows " +
        "which give you the impression they are looking for victims.\n", LIGHT_ALL);
    add_item_light(({"village", "gairent"}),
        "You are currently in the village of Garient, a small village of " +
        "woodsmen hidden deep within Mirkwood forest.\n", LIGHT_ALL);
    add_item_light(({"buildings","houses","shacks", "shelters", "building", "house", "shack", "shelter", }),
        "There are dozens of tiny shacks here, dwellings for the woodsmen who " +
        "live inside Mirkwood forest. These houses are all made of wood and " +
        "are just big enough to give a small family enough room to eat and " +
        "sleep. You can also see the larger building of the smithy to the west.\n", LIGHT_ALL);
    add_item_light(({"smithy", "blacksmith", "blacksmith's smithy", "wall", "west wall"}),
        "The blacksmith's smithy is a very important building in a small village like " +
        "Garient. You are currently standing in the yard of the smithy, and can " +
        "enter the smithy proper by going through the narrow doorway to the west.\n", LIGHT_ALL);
    add_item_light(({"yard", "blacksmith's yard"}),
        "This is a small yard east of the " +
        "smithy in Gairent. Scattered across the yard are several " +
        "barrels, boxes, crates and assorted items too numerous " +
        "to count. In the middle of the yard, a large cart rests " +
        "up against a tall, slender maple tree. To the west, the " +
        "wall of the smithy is unbroken save for a narrow doorway. " +
        "A low, wooden fence with a locked gate surrounds the rest of the yard, making " +
        "your only way out back into the smithy.\n", LIGHT_ALL);
    add_item_light(({"cart", "woodcart", "wood cart", "large cart", "wooden cart"}),
        "This large, wooden cart seems to have been designed to carry raw lumber for " +
        "the woodsmen. It has four sturdy wheels supporting the cart itself, which " +
        "appears to have been constructed out of many thick boards. " +
        "the blacksmith needs 17 carts\n", LIGHT_ALL);
    add_item_light(({"wheel", "wheels", "sturdy wheels", "rim", "iron bands", "bands", "iron"}),
        "The wheels of the woodcart are made of wood and have been reinforced " +
        "with bands of iron which cover the rim.\n", LIGHT_ALL);
    add_item_light(({"tree", "slender tree", "maple tree"}),
        "In the middle of the yard is a slender, maple tree which spreads shade " +
        "generously, making this a wonderful spot to relax outside on a sunny day. " +
        "Currently, the blacksmith has left a cart leaning up against the side " +
        "of the tree.\n", LIGHT_ALL);
    add_item_light(({"board", "boards","thick boards", "wooden boards", "boards on cart"}),
        "These thick, wooden boards are what have been used to build the bulk of this lumber " +
        "cart. Each board is about four feet long, six inches high and one inch thick and is " +
        "dotted with several rough, iron nails which have been hammered into place.\n", LIGHT_ALL);
    add_item_light(({"nail", "nails", "rough nails", "iron nails", "nails in boards"}),
        "There are plenty of rough, iron nails which have been hammered into the boards " +
        "of the wooden cart. You could probably count them if you wanted.\n", LIGHT_ALL);
    add_item_light(({"barrel", "barrels"}),
        "There are several stout, wooden barrels scattered around the yard. These barrles " +
        "appear to be watertight, as most of the barrels which stand upright are partially " +
        "filled with rainwater.\n", LIGHT_ALL);
    add_item_light(({"water", "rainwater"}),
        "As you peek inside some of the barrels in the yard, you can see that some of " +
        "them are partially filled with rainwater.\n", LIGHT_ALL);
    add_item_light(({"crate", "crates", "box", "boxes"}),
        "There are several boxes and crates scattered around the yard, often arranged in " +
        "tidy stacks. The boxes and crates are mostly empty, although a few of them " +
        "are filled with assorted junk that the blacksmith probably should have thrown " +
        "away, but for some reason has decided to keep.\n", LIGHT_ALL);
    add_item_light(({"door", "doorway"}),
        "This narrow doorway allows you to leave the yard and go back inside the smithy.\n", LIGHT_ALL);
    add_item_light(({"items", "assorted items", "junk", "assorted junk"}),
        "The blacksmith apparently uses this side yard as additional storage for anything " +
        "he would like to keep, but does not have space for. You get the distinct feeling " +
        "that he is a bit of a packrat.\n", LIGHT_ALL);
    add_item_light(({"fence", "wooden fence", "low fence"}),
        "This is a low fence made from wooden logs, which encircles the blacksmiths yard. " +
        "The only gate is firmly locked, leaving you the option of going " +
        "back into the smithy if you wanted to leave the yard.\n", LIGHT_ALL);
    add_item_light(({"gate", "locked gate", "lock", "chain"}),
        "This gate is in the middle of the south wall of the fence. It is firmly " +
        "chained and locked, preventing anyone other than the blacksmith from opening " +
        "it.\n", LIGHT_ALL);

    add_exit("gairent_forge", "west");
}    


void

init()
{
    ::init();
    add_action("do_climb","climb");
    add_action("do_count","count");
    add_action("do_open","open");
}

int
do_climb(string str)
{
    notify_fail("Climb what?\n");
    if (!str || !strlen(str)) return 0;

    if (parse_command(str, ({}), "[low] [wooden] 'fence'")) {
        write("You climb over the low fence and out into the "
            + "village of Gairent.\n\n" 
            + "The village is not very large and you "
            + "quickly find yourself in the middle "
            + "again.\n\n");

        SAYBB(" climbs over the wooden fence.");
        TP->move_living("M","/d/Gondor/rhovanion/mirkwood/woodsmen/gairent2",1,0);
        SAYBB(" emerges from between two shacks at the north end of the village.");
        return 1;
    }

    if (parse_command(str, ({}), "[slender] [maple] 'tree'")) {
        write("You climb up to the top of the tall maple tree.");
        TP->move_living("M","/d/Gondor/rhovanion/mirkwood/woodsmen/tree",1,0);
        SAYBB(" climbs up from down below.");
        return 1;
    }

    return 0;
}

int
do_count(string str)
{
    notify_fail("Count what?\n");
    if (!str || !strlen(str)) return 0;

    string stop_function;
    string target;

    if (parse_command(str, ({}), "[wide] [wooden] 'boards'")) 
    {
        stop_function = "stop_counting_boards";
        target = "the wooden boards";
    }

    if (parse_command(str, ({}), "[rough] [iron] 'nails'")) 
    {
        stop_function = "stop_counting_nails";
        target = "the iron nails";
    }

    if (!stringp(stop_function) || !strlen(stop_function)) return 0;

    setuid();
    seteuid(getuid());
    object paralyze = clone_object(PARALYZE_OBJECT);
    paralyze->set_standard_paralyze("counting");
    paralyze->set_stop_fun(stop_function);
    paralyze->set_combat_stop(1);
    paralyze->set_remove_time(5);
    paralyze->move(this_player(), 1);

    write("You start counting " + target + ".\n");
    return 1;
}

int
stop_counting_boards(mixed arg) 
{
    if (objectp(arg))
    {
        write("You make your way around the cart, carefully counting, and find " +
            "that it would take 271 boards to make a new cart.\n");
        this_player()->add_prop(GAIRENT_CART_QUEST_COUNTED_BOARDS, 1);
    }

    return 0;
}

int
stop_counting_nails(mixed arg)
{
    if (objectp(arg))
    {
        write("You carefully count and find that each board uses 15 nails.\n");
        this_player()->add_prop(GAIRENT_CART_QUEST_COUNTED_NAILS, 1);
    }

    return 0;
}

int
do_open(string str)
{
    notify_fail("open what?\n");
    if (!str || !strlen(str)) return 0;

    if (parse_command(str, ({}), "[chained] [locked] 'gate'")) {
        write("You try to open the locked gate, but it is useless. " +
            "You will have to try something else instead.\n ");

        SAYBB(" tries in vain to unlock the gate.\n");

        return 1;
    }

    if (parse_command(str, ({}), "[narrow] 'door'")) {
        write("The door is already open, you can simply go west " +
            "back into the smithy.\n");
        
        return 1;
    }

    return 0;
}