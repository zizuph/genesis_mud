/* Hoopak store, Gwyneth July, 1999*/

#pragma save_binary

#include <stdproperties.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit "/lib/shop";
inherit KENDERMORE_IN;
inherit STREET_DESC;

#define STORE_ROOM KROOM + "hoopak_store2.c"

object hoopak_seller;

void
reset_kendermore_room()
{
    if (!hoopak_seller)
    {
        hoopak_seller = clone_object(KNPC + "hoopak_seller");
        hoopak_seller->move(TO);
    }
}

void
create_kendermore_room()
{
    config_default_trade();
    set_short("Hoopak maker's tent");
    set_long("@@long_descr");

    add_item("tent", "This tent is very spacious, with bright blue " + 
        "canvas walls. It looks like it could be bundled up into a " + 
        "portable package.\n");
    add_item(({"wall", "walls", "canvas walls", "blue walls",
        "bright blue walls", "bright walls", "first side", "second side",
        "third side", "first wall", "second wall", "third wall", "sides"}), 
        "The bright blue dyed canvas surrounds you on " + 
        "three sides. It keeps out most of the wind, and leaves a soft " + 
        "blue light on everything inside.\n");
    add_item(({"fourth wall", "fourth side"}), "The fourth side has been " + 
        "tied back with a leather thong to reveal the street, and to " + 
        "let in some air.\n");
    add_item(({"thong", "leather thong"}), "It is tied securely in place, " + 
        "holding the tent open.\n");
    add_item(({"out", "street"}), "@@street_descr@@\n");
    add_item(({"piles", "wood", "stacks"}), "There are stacks of yew, " + 
        "lemonwood, hickory and oak wood piled against one wall.\n");
    add_item(({"yew", "yew wood", "yew pile",}), "This is a stack of yew " + 
        "wood. Yew is a very strong, very flexible wood. It is springy, " + 
        "but will shatter violently if broken. The colouring is a light " + 
        "brown, but with no noticeable grain.\n");
    add_item(({"lemonwood", "lemonwood wood", "lemonwood pile"}), "This " + 
        "is a stack of lemonwood wood. Lemonwood is very strong and " + 
        "flexible, much like yew, but not as good. It will also " + 
        "shatter violently if broken. The colouring of lemonwood " + 
        "is a light yellow brown with no noticeable grain.\n");
    add_item(({"hickory", "hickory wood", "hickory pile"}), "Hickory is " + 
        "not as springy as yew or lemonwood, but very tough and hard. " + 
        "It's colouring is a light to medium brown with dark grayish " + 
        "or even black lines which show where the grain is. If sanded, " + 
        "the lines are even a bit indented into the wood.\n");
    add_item(({"oak", "oak wood", "oak pile"}), "Oak is hard, but not " + 
        "very flexible. It is a light brown in colour, with uneven grain.\n");
    add_item("carpet", "It is a very wide red and brown carpet that the " + 
        "hoopak maker sits on when carving her wood.\n");
    add_item(({"chip", "wood chip", "wood chips", "chips"}), "They are " + 
        "what is left over after the hoopak maker has whittled down the " + 
        "pieces of wood into long staves.\n");
    add_item("ground", "The ground is unadorned dirt.\n");
    add_item("dirt", "It's rather dry and hard packed.\n");
 
    add_item("sign", "   Welcome to Danalin's Hoopak Shop!\n" + 
                     "   I have several different types of\n" +
                     "   hoopaks for you to choose from.\n" + 
                     "   To order, just do 'order <type>',\n" + 
                     "   and I will make a hoopak of that type\n" + 
                     "   for you to buy.\n" +
                     "\n" + 
                     "   Available Types, from best to worst:\n" + 
                     "   Yew, lemonwood, hickory and oak.\n" +
                     "   \n" + 
                     "   Note: All hoopaks but oak hoopaks\n" + 
                     "   are made to be used two-handed.\n" + 
                     "\n");

    add_prop(ROOM_M_NO_ATTACK, "@@no_attack");
    add_prop(ROOM_M_NO_MAGIC_ATTACK, "@@no_attack");
    add_exit(KROOM + "in_gate", "out", 0);
    add_invis_exit(STORE_ROOM, "east", "@@wiz_check");
    set_store_room(KROOM + "hoopak_store2");
    query_store_room()->load_me();
    reset_kendermore_room();
    return;
}

string
no_attack()
{
    TP->add_prop(LIVE_S_EXTRA_SHORT, " spluttering furiously");

    tell_room(environment(TP), QCTNAME(TP) + " prepares to attack, " +
        "but out of nowhere a kender jumps in front of " + HIM(TP) +
        " and knocks " + HIS(TP) + " feet out from under " + HIM(TP) +
        "! " + C(HE(TP)) + " splutters furiously as " + HE(TP) + " tries " +
        "to reach " + HIS(TP) + " opponent, but the kender skips " +
        "away delighted with his prank.\n", TP);

    return "You prepare to attack, but out of nowhere a kender " +
        "jumps in front of you and knocks your feet out from " +
        "under you! You splutter furiously as you try to reach " +
        "your opponent, but he skips away from you delighted with " +
        "his prank.\n";
}

/* Function name : long_descr
 * Returns : Returns the long description, based on the presence of
 *     the hoopak maker.
*/

string
long_descr()
{
    string sitting;

    if (!present(hoopak_seller))
        sitting = ("Nobody is sitting on the carpet right now.");
    else
        sitting = ("A cheerful looking kender, that you suppose is " + 
            "the hoopak maker, is sitting on the carpet. She whittles " + 
            "away at the wood, whistling a happy tune.");

    return("This is the hoopak maker's tent. You are surrounded on " +  
        "three sides by the bright blue tent. The fourth side has " + 
        "been tied back to reveal the street. Piles of yew, lemonwood, " +
        "hickory, and oak wood are stacked against one side of the bright " +
        "tent. A carpet has been placed in front of the stacks of wood, " + 
        "perhaps acting as a backrest for one sitting on the carpet. " + 
        sitting + " A sign has been propped up amid the wood chips that " + 
        "litter the carpet and spill out onto the " + 
        "ground.\n"); 
}

/* Function name : Init
 * Description : Allows someone to order a hoopak of the desired type. 
 * Returns : Null
*/

void
init()
{
    ::init();
    init_shop();
    add_action("load_hoopak", "order");
}

/* Function name : Enter inventory
 * Description : Starts the room tells when a PC enters the room.
 * Returns : Null
*/

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}

/* Function name : Wiz check
 * Description : Blocks mortals from entering the storeroom.
 * Returns : 1 or 0
*/

int
wiz_check()
{
    if (TP->query_wiz_level())
        return 0;
    write("There is no obvious exit east.\n");
    return 1;
}

/* Function name : Read sign
 * Description : Shows the sign with instructions.
 * Returns : 1
*/

int
do_read(string str)
{
    if (str == "sign")
    {
        write("   Welcome to Danalin's Hoopak Shop!\n" + 
              "   I have several different types of\n" + 
              "   hoopaks for you to choose from.\n" + 
              "   To order, just do 'order <type>',\n" + 
              "   and I will make a hoopak of that type\n" + 
              "   for you to buy.\n" + 
              "   \n" + 
              "   Available Types, from best to worst:\n" + 
              "   Yew, lemonwood, hickory, and oak.\n" + 
              "   \n" +
              "   Note: All hoopaks but oak hoopaks\n" +
              "   are made to be used two-handed.\n" +
              "   \n"); 
        return 1;
    }
    
}              

/* Functin name : Sell
 * Description : Blocks items from being sold here.
 * Returns : 0
*/

int
do_sell(string str)
{
    NF("I don't buy anything here. I just sell hoopaks. Read the sign!\n");
    return 0;
}

/* Function : Buy
 * Description : Allows buying while the shopkeeper is present.
 * Returns : 0 or the buy string
*/

int
do_buy(string str)
{
    NF("Danalin must have gotten a severe case of wanderlust and " + 
        "cannot sell you anything.\n");
    if (!P(hoopak_seller, TO))
        return 0;

    if (KMASTER->query_enemy(this_player()->query_real_name()))
    {
        write("The hoopak maker won't deal with the likes of you!\n");
        return 1;
    }

    return ::do_buy(str);
}

/* Function name : Load hoopak
 * Description : Starts Danalin making a hoopak of the desired type.
 *     Checks to see if Danalin is present.
 * Returns : Null
*/

string
load_hoopak(string str)
{
    object hoopak;
    object room = environment(TP);
    string str1, str2;

    if (!strlen(str))
    {
        NF("Order what kind of hoopak?\n");
        return 0;
    }
    
    sscanf(str, "%s", str1);
    sscanf(str, "%s %s", str1, str2);

    if (hoopak_seller)
    {
        if ((str1 == "yew") || (str1 == "lemonwood") || 
          (str1 == "hickory"))
        {
            write("You ask Danalin for a " + str1 + " hoopak.\n");
            say(QCTNAME(TP) + " asks Danalin for a " + str1 + " hoopak.\n");
            hoopak_seller->check_id(str1);
            return "";
        }
        if (str == "oak")
        {
            write("You ask Danalin for an " + str1 + " hoopak.\n");
            say(QCTNAME(TP) + " asks Danalin for a " + str1 + " hoopak.\n");
            hoopak_seller->check_id(str1);
            return "";
         }
    }

    if (!hoopak_seller)
    {
        write("Danalin isn't here to order from. She must have gotten a " + 
            "severe case of wanderlust, not uncommon for kender.\n"); 
        return "";
    }

    else
    {
        write("Order what kind of hoopak?\n");
        return "";
    }
}

