/*
 * File         : /d/Genesis/start/hobbit/town/pub.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 3/6/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        A normal pub with beer, ale, coffee and liqueur. The owner is a
 *        big sturdy old hobbit with bad temper which is unusual for a
 *        hobbit. He was one of Tondurs closest men and got severly
 *        wounded in the leg in the last big battle. The pain from the
 *        stiff leg makes his anger sudden. The only food in this pub is
 *        grilled salt fish in a cut bread. There is a doorway through to
 *        the Adventurers guild that shares the same building but has also
 *        a separate entrance to the street. The pub owner sometimes goes
 *        fishing with his friends.
 * 
 * TODO         :
 *        Add more brews and food, Fix the pricelist, Let beers take some
 *         time to drink using a sequence so that folks don't buy 20 beers
 *         and drink them at once.
 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

#pragma strict_types

/* inherits */
inherit "/std/room";
inherit "/lib/pub";


/* includes */
#include <stdproperties.h> 
#include <macros.h> 
#include <cmdparse.h>
#include <money.h>
#include <ss_types.h>
#include "../hobbit.h"

/* defines */



/* prototypes */
void create_room();
void reset_room();
string read_pricelist();
string read_note();


/* globals */
object Publican;

/*
 * Function name:       create_room
 * Description  :       set up the room
 */
void
create_room()
{
    set_short("The Iron Peace");
    set_long(
      "A dense and very special smell of pub hangs thick in the air of " +
      "this dimly lit room. Most tables are occupied by people from the " +
      "village and a couple of aventurers are sitting at stools at the " +
      "counter telling each other about their recent travells. The fire " +
      "has burnt to live coal in the fireplace which spreads a cosy " +
      "warmth throughout the room. A pricelist hangs by the counter.\n");
    add_item("barrel", 
      "The barrel behind the counter has the lid slightly ajar and " +
      "reveals some salted fish. \n");
    add_item("barrels", 
      "Barrels are used as stools around the counter. \n");
    add_item("cap", 
      "It is an ordinary cap with a feather and some fishing hooks " +
      "attached. \n");
    add_item("ceiling", 
      "The ceiling is made of wooden beams covered with a straw roof " +
      "on the outside. \n");
    add_item("counter", 
      "The counter is surrounded by sturdy bar stools and behind it " +
      "is a barrel and some fishing equipment. \n");
    add_item("east wall", 
      "A cap and a fishing rod hangs on the wall behind the counter " +
      "together with a small note. \n");
    add_item("fire", 
      "It is too late to look at the fire, it is already burnt out. \n");
    add_item("fireplace", 
      "It is a rather small fireplace with some remains of burnt out " +
      "firewood still present. \n");
    add_item("floor", 
      "The floor is made of wooden planks and is very dirty \n");
    add_item(({ "furniture", "furnitures" }), 
      "The furnitures here looks really sturdy. \n");
    add_item("north wall", 
      "On the northern wall a huge stuffed pike is hanging on a piece " +
      "of plank with a plaque attached. \n");
    add_item("pike", 
      "It is a huge pike grinning grimly with a glaring glance in its " +
      "eyes. It is stuffed and is hanging on the wall. \n");
    add_item("plank", 
      "The pice of plank seem to be driftwood and has been used as a " +
      "background for a stuffed pike. \n");
    add_item("plaque", 
      "It is a slightly rusty piece of metal with some crummy letters " +
      "on. \n");
    add_item("pricelist", 
      "The pricelist is framed and nailed firmly to the corner post " +
      "of the counter. \n");
    add_item("pub", 
      "The pub is well visited and with very robust furnitures. \n");
    add_item(({ "remains", "firewood", "coal" }), 
      "It looks like firewood burnt to coal. \n");
    add_item(({ "salted fish", "fish" }), 
      "The smell of salted fish originates from behind the counter. \n");
    add_item(({ "smoke", "smell" }), 
      "The smell in the pub is a mix comming from salt fish, tobacco " +
      "smoke and the fire. \n");
    add_item(({ "stool", "stools" }), 
      "All stools are assembled by an empty barrel and a cushion made " +
      "of a potatoe sack stuffed with hay on top. \n");
    add_item(({ "table", "tables" }), 
      "These tables are pretty clean except for some bread crumbs " +
      "here and there. \n");
    add_item(({ "walls", "wall" }), 
      "The walls of the pub are decorated with things making up the " +
      "cosy atmosphere. \n");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_S_DARK_LONG,
      "A dark pub, you can't see anything.\n");
    add_prop(ROOM_S_DARK_MSG,
      "The darkness makes it impossible to");
    add_prop(ROOM_S_EXIT_FROM_DESC,
      "from the pub.");
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 3/6/99.\n");
    
    add_exit("advguild.c", "north");
    add_exit("villageroad4.c", "west");
    
    
    add_cmd_item("pricelist", "read",  read_pricelist);
    add_cmd_item("note",      "read",  read_note);
    add_cmd_item("plaque",    "read", 
        "The plaque reads:\n\n  Catched by Tan.\n");
    add_drink( ({ "beer", "beers", "dark", "dark beer" }),
        "beer", "dark", 100, 3, 10, 0, 0,
        "It's a dark foaming beer.\n", 0);
    
    add_drink( ({ "beer", "beers", "light", "light beer" }),
        "beer", "light", 100, 2, 8, 0, 0,
        "It's a pale light beer.\n", 0);
    
    reset_room();
}
/*
 * Function name:       reset_room
 * Description  :       replenish npc & stuff, if needed
 */
void
reset_room()
{
    setuid();
    seteuid(getuid());
    if (!objectp(Publican))
    {
        Publican = clone_object(EX_MON + "publican");
        Publican->move(this_object(), 1);
        tell_room(TO, QCTNAME(Publican) + " arrives limping.\n");
    }
    
}

/*
 * Function name: init
 * Description:   Initalize the pub actions
 */
void
init()
{
    ::init(); /* Since it's a room this must be done. */
    init_pub();
    
    // Check if the NPC is here and let him check the player
    if (Publican && present(Publican))
    {
        Publican->set_visitor(this_player());
    }
}

/*
 * Function name: gender_title(str)
 * Argument     : The object
 * Returns      : correct title for a specific gender
 */
string
gender_title(object ob)
{
    string title;
    if (ob->query_gender())
    {
        title = "my lady";
    }
    else
    {
        title = "mister";
    }
    return title;
}

/*
 * Function name: pub_hook_invalid_order(str)
 * Argument     : what the player wanted to order
 * Description  : reacts on an invalid order from a player
 * Returns      : 1 always
 */
int
pub_hook_invalid_order(string str)
{
    object *fishes;
    object ob;
    string food;
    
    if (Publican && present(Publican))
    {
        if (member_array(str, ({"bread", "fish bread",
            "roasted fish bread"})) >= 0)
        {
            Publican->command("say to " + OB_NAME(TP) +
                " Ahhh, so you have heard of my speciality!");
            Publican->command("say to " + OB_NAME(TP) +
                " Let me just check that I got what it takes to make it.");
            Publican->command("emote removes the lid of a barrel behind " +
                "the counter and examines the content carefully.");
            
            // Check if we got any fishes available
            fishes = FIND_STR_IN_OBJECT("fishes", Publican);
            if (sizeof(fishes)) // Yep there are some in stock
            {
                Publican->command("smile cheer at " + OB_NAME(TP));
                Publican->command("say to " + OB_NAME(TP) +
                    " He-he, look here what I found.");
                Publican->command("emote cuts a bread with a rusty scimitar.");
                Publican->command("whistle cheer");
                Publican->command("emote prepares the fish and puts it between " +
                    "the bread pieces.");
                Publican->command("shrug");
                Publican->command("emote adds a few spicy herbs and some red sauce " +
                    "from a slightly cracked pot he got behind the counter.");
                Publican->command("smile happ at " + OB_NAME(TP));
                Publican->command("say to " + OB_NAME(TP) +
                    " That would be 12 coppers " + gender_title(TP) + ".");
                ob = clone_object(EX_OBJ + "roasted_fish_bread");
                food = "bread";
                
                // Ok lets see if the player got enough money to pay for it.
                if (!MONEY_ADD(TP, -12)) // Nope (s)he hasn't :(
                {
                    pub_hook_cant_pay(12);
                    Publican->command("roar");
                    Publican->command("shout" +
                        " Get out, you crummy piece of a wrecked wessel!");
                    Publican->command("point west");
                    Publican->command("shout" +
                        " And don't come back until you can pay for what you order.");
                    ob->move(Publican, 1);
                    Publican->command("eat " + OB_NAME(ob));
                }
                else // The player has enough cash to pay for the bread. :)
                {
                    pub_hook_player_buys(ob, 12);  // Let the player pay
                    
                    // Is the player too small to digest the bread?
                    if ((TP->query_stat(SS_CON) * 8) <=  
                        ob->query_prop(OBJ_I_WEIGHT))   // yep, let's slice it
                    {
                        ob->remove_object();
                        ob = clone_object(EX_OBJ + "sliced_roasted_fish_bread");
                        ob->set_heap_size(5);
                        food = "slices";
                        Publican->command("peer at " + OB_NAME(TP));
                        Publican->command("emote chops the bread into slices " +
                            "with a rusty scimitar.");
                    }
                    ob->move(Publican, 1);         // Give the player the bread
                    Publican->command("give " + food + " to " + OB_NAME(TP));
                    fishes[0]->remove_object();    // Decrease number of fishes by 1
                }
            }
            else   // Nope no fishes in stock :(
            {
                Publican->command("sigh deep");
                Publican->command("say to " + OB_NAME(TP) +
                    " It seems that I am out of fish for the moment.");
                Publican->command("pat");
                Publican->command("say to " + OB_NAME(TP) +
                    " You don't know anyone that could sell me some fish, do you?");
                Publican->command("say to " + OB_NAME(TP) +
                    " I would pay well for fish right now.");
            }
        }
        else // The player tried to order something unknown
        {
            Publican->command("sigh deep");
            Publican->command("emote points at the pricelist.");
            Publican->command("say to " + OB_NAME(TP) + 
                " Read it! If you can, that is.");
        }
    }
    return 1;
    
}
/*
 * Function name: pub_hook_syntax_failure(str)
 * Argument     : what the player said
 * Description  : reacts on an invalid order from a player
 * Returns      : 1 always
 */
int
pub_hook_syntax_failure(string str)
{
    if (Publican)
    {
        Publican->command("pat " + TP->query_name());
        Publican->command("say to " + TP->query_name()+ " Are you trying to be funny?");
    }
    return 1;
}

/*
 * Function name: pay_hook_player_buys
 * Description:   A hook to redefine if you want own message when player
 *                gets his/hers order.
 * Arguments:     ob - The object player ordered
 *                price - The price the player payed for the object
 */
void
pub_hook_player_buys(object ob, int price)
{
    write("You pay " + price + " coppers for " + ob->short() + ".\n");
    say(QCTNAME(this_player()) + " pays for " + ob->short() + ".\n");
}

/*
* Function name: read_pricelist
* Description:   Read the menu
*/
string
read_pricelist()
{
    cat(EX_ROOM + "pubmenu.txt");
    return "";
}

/*
* Function name: read
* Description:   Read the note
*/
string
read_note()
{
    cat(EX_ROOM + "pubnote.txt");
    return "";
}


