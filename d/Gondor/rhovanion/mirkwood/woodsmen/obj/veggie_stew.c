inherit "/std/food";

#include "/d/Gondor/rhovanion/mirkwood/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <files.h>

int do_nibble(string str);
int do_sip(string str);
int do_devour(string str);
int do_stir(string str);

void
create_food() 
{
    set_name(({ "stew", "hearty stew", "vegetable stew" }));
    set_pname(({ "stews", "hearty stews", "vegetable stews" }));
    set_short("hearty, vegetable stew");
    set_pshort("hearty, vegetable stews");
    set_long("This pot holds a generous helping of what appears to be a " +
        "hearty vegetable stew. Inside the pot, you can see diced chunks " +
        "of cabbage, turnip, onion and mushroom mixed together with peas, " +
        "carrots and a variety of herbs. The pot is still warm, and even has " +
        "a chunk of brown bread to accompany the stew. The woodsmen of " +
        "Mirkwood often take helpings of this stew to help keep up their " +
        "energy as they work during the day.\n");
    add_item(({"bread", "brown bread"}),
        "This is a chunk of brown bread that goes with the vegetable stew. " +
        "You can nibble on it or even stir your stew with it.\n");
    add_item(({"pot"}),
        "This pot contains a generous serving of a delicious looking " +
        "vegetable stew. You can take a sip or even devour the whole " +
        "serving at once!\n");
    add_item(({"herbs", "herbs in stew"}),
        "You are not quite certain, but you think you can detect a variety " +
        "of herbs including saffron, ginger, anise, cinnamon and fennel.\n");
    add_item(({"vegetables"}),
        "There certainly seems to be a lot of vegetables in this stew! You " +
        "can see cabbage, turnip, onion, mushroom, carrot and peas.\n");
    add_item(({"cabbage"}),
        "You spy some cabbage mixed inside your stew.\n");
    add_item(({"turnip"}),
        "A large chunk of turnip in your stew catches your attention, " +
        "and you quickly fish it out and pop it in your mouth.\n");
    add_item(({"onion"}),
        "There are several large chunks of onion floating in your stew.\n");
    add_item(({"mushroom"}),
        "You can see several different types of mushrooms have been " +
        "added to your stew.\n");
    add_item(({"carrot"}),
        "There are several slices of orange carrot mixed into your stew.\n");
    add_item(({"peas"}),
        "As you poke around your stew, you can see that some peas have " +
        "been added in.\n");
    set_amount(135);
    add_prop(OBJ_I_WEIGHT,135);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE,0);
}

void

init()
{
    ::init();
    add_action("do_nibble","nibble");
    add_action("do_sip","sip");
    add_action("do_devour","devour");
    add_action("do_stir","stir");
}

int
do_nibble(string str)
{
    notify_fail("Nibble what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You take the chunk of brown bread that accompanies your stew and " +
         "begin to nibble on it absentmindedly. \n");
    SAYBB(" begins to nibble discreetly on a chunk of brown bread.");
    return 1;
}


int
do_sip(string str)
{
    notify_fail("Sip what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0;

    write("You open your pot of vegetable stew and take a quick sip. The " +
        "hearty broth trickles down your throat and creates a satisfying " +
        "warmth in your stomach.\n");
    SAYBB(" opens up a pot of stew to take a quick sip.\n");
    return 1;
}

int
do_devour(string str)
{
    notify_fail("Devour what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("Unable to resist temptation any longer, you open the pot of stew " +
        "and begin to devour it quickly. You savour every bite of the " +
        "vegetables, tasting the delicate seasoning of herbs which has " +
        "given it just the right flavour. You finally use the remaining heel " +
        "of brown bread to sop up the last drops as you finish the pot of " +
        "stew.\n");
    SAYBB(" opens up their pot of stew and devours it quickly.\n");
    TP->command("burp softly");
    TP->command("eat stew");
    return 1;
}

int
do_stir(string str)
{
    notify_fail("Stir what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You take up your chunk of brown bread and stir it in the " +
        "hearty, vegetable stew before taking a quick bite.\n");
    SAYBB(" stirs a pot of stew with a chunk of brown bread before " +
        "taking a small bite.\n");
    return 1;
}