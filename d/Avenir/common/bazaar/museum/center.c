// -*-C++-*-
// file name:	coffee_house.c	
// creator(s): 	sirra  march 98
// modification history:
//	Lilith Aug 1998: updated desc, added pillows, etc
//	Manat  12/00 Changed rise to give messages in the right order.
//	             Changed so that one rises before one leaves the room.
//	             Changed sit so that one can change how one is sitting.
//      Manat   1/01 Additional changes... added prevent_leave.
// Sirra Nov 2002 Added table as a container as suggested
//					 in Mortal Idea Report.
//  Lilith Oct 2021: added same add_items as rest of the museum via add_descs()
// purpose:     Center of museum: coffee house/sells food as well.
// note:        Liqour healing          10 + (alco * alco / 10)
//              Food                     5 + (amount * amount / 600)
// bug(s):
// to-do:

#pragma strict_types

inherit "/d/Avenir/common/bazaar/museum/std_museum";
inherit "/lib/trade";
#include "museum.h"
#include "gallery.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <cmdparse.h>
#include "/d/Avenir/include/relation.h"

#define PLAYER_M_SITTING ("_player_m_sitting")
#define TYP sizeof(MONEY_TYPES)

object host, board, table;
int    test;

static object *sitting = ({ });
static mapping in_lap = ([ ]);

int    move_item(mixed arg);

string my_long();
string cushion_desc();
string sitting_on_cushion(string seated);
int do_rise(string str);

/*
 * Function name: reset_room
 * Description  : Called to clone in a new waitress if she has
 *                disappeared.
 */
public void
reset_room()
{
    if (!host)
    {
        host = clone_object("/d/Avenir/common/bazaar/NPCS/cafe_waitress");
        host->move_living("xxx", TO);
    }
}

/*
 * Function name: leave_the_room
 * Description  : rise the sitting persons before they leave.
 * Returns      : (int) 0 - always allow the leaving.
 */
public int
leave_the_room(void)
{
    object who = this_player();

    if (who->query_prop(PLAYER_M_SITTING) &&
        (query_verb() != "In") &&
        (query_verb() != "At"))
    {
        do_rise(0);
    }

    return 0;
}

/*
 * Function name: create_room
 * Description  : creator of rooms.
 */
public void
create_room()
{
    set_short("Goatfeathers Cafe");
    set_long(my_long);

    add_item(({"candles", "bowls", "stained-glass bowls"}), 
        "The flames within the stained glass " +
        "bowls dance and flicker, casting shadows across " +
        "the room at random.\n");
    add_item(({"patron", "patrons"}), "A female elf looks " +
        "up at you, and coldly stares back.\n");
    add_item(({"seating", "seating areas"}), "The seating areas " +
        "consist of comfortable cushions cast about low tables.\n");     
	 add_item(({"cushion", "cushions", "plump cushion", "plump cushions"}),
        cushion_desc);
    add_item(({"sipping bowl", "sipping bowls"}), "Small bowls that " +
        "fit comfortably in the hand and are used for drinking warm " +
        "beverages.\n");
    add_item(({"tapestry", "tapestries", "walls"}),
        "Tapestries hang from the dome above, creating an enclosed space. "+
        "Each one depicts goats, feathers, or a combination of the two, " +
        "in surrealistic poses and colours.\n");

    if (!board)
    {
		  board = clone_object("/d/Avenir/common/bazaar/museum/obj/board");
		  board->move(TO);
	 }

	 if (!table)
	 {
		table = clone_object("/d/Avenir/common/bazaar/museum/obj/table");
		table->move(TO);
	 }

	 add_exit(STAT7,  "north",     "@@leave_the_room@@");
	 add_exit(STAT6,  "south",     "@@leave_the_room@@");
	 add_exit(STAT14, "west",      "@@leave_the_room@@", 0, 1);
	 add_exit(STAT9,  "east",      "@@leave_the_room@@", 0, 1);
	 add_exit(STAT15, "northwest", "@@leave_the_room@@", 0, 1);
	 add_exit(STAT8,  "northeast", "@@leave_the_room@@", 0, 1);

    config_default_trade();    
    reset_room();

    add_descs();

}

/*
 * Function name: cushion_desc
 * Description  : Describe the cushions and show who is sitting in them.
 * Returns      : (string)the description
 */
public string
cushion_desc()
{
    return ("Comfortable cushions, nice and plump, are scattered " +
           "throughout the room in intimate clusters.\n ") +
           sitting_on_cushion("");
}

/*
 * Function name: sitting_on_cushion
 * Description  : Combine those sitting into a nicely formatted string.
 * Arguments    : string seated - predefined text.
 * Returns      : (string) the formatted text.
 */
public string
sitting_on_cushion(string seated)
{
    string *text;
    object *laps;
    object lap;
    int size;

    if (!sizeof(sitting))
    {
        return (strlen(seated) ? (seated) : "");
    }

    seated = (strlen(seated) ? (seated + " ") : "");
    
    if (member_array(TP, sitting) != -1)
    {
        seated += ("You are seated on a plump cushion" +
            ((sizeof(sitting) == 1) ? "." : (", as is " +
            COMPOSITE_WORDS(map((sitting - ({ TP }) ),
            &->query_the_name(TP))) + ".\n")));
    }
    else
    {
        seated += (capitalize(COMPOSITE_WORDS(map(sitting,
            &->query_the_name(TP)))) +
            ((sizeof(sitting) == 1) ? " is" : " are") +
            " seated on cushions.\n");
    }

    if (m_sizeof(in_lap))
    {
        seated += " ";

        laps = m_indices(in_lap);

        if (objectp(in_lap[TP]))
        {
            text = ({ (in_lap[TP]->query_The_name(TP) +
                " is sitting in your lap") });
            laps -= ({ TP });
	}
        else if (objectp(lap = TP->query_prop(PLAYER_M_SITTING)))
        {
            text = ({ ("You are sitting in " +
		    lap->query_the_possessive_name(TP) + " lap") });
            laps -= ({ lap });
        }
        else
        {
            text = ({ (in_lap[laps[0]]->query_The_name(TP) +
        	" is sitting in " + laps[0]->query_the_possessive_name(TP) +
		" lap") });
            laps -= ({ laps[0] });
        }

        size = sizeof(laps);
        while(--size >= 0)
        {
            text += ({ (in_lap[laps[size]]->query_the_name(TP) + " in " +
        	laps[size]->query_the_possessive_name(TP)) });
        }

        seated += COMPOSITE_WORDS(text) + ".";
    }

    return (strlen(seated) ? (seated) : "") +"\n";
}

/*
 * Function name: my_long
 * Description  : The description of this room.
 * Returns      : (string)description
 */
public string
my_long()
{
    string str;

    str = "This is the GoatFeathers Cafe, a special haven in the "+
        "heart of the museum. Short candles housed " +
        "in stained-glass bowls cast small pools of light that " +
        "set private seating areas aglow. Some patrons sit " +
        "alone, murmuring to themselves over the latest " +
        "poetry, quill-pens in one hand and sipping-bowls of " +
        "kahve in the other. Tapestries hang upon the walls, " +
        "and the floor is scattered with layers of thick " +
        "carpets, all of which serve to muffle sound and set " +
        "an intimate mood. There are several slips of paper " +
        "pinned to a large cork board leaning against one " +
        "wall.\n";

    return str + sitting_on_cushion("");
}

/*
 * Function name: do_rise
 * Description  : command to rise
 * Argument     : string str - the argument to the command
 * Returns      : (int) 1/0 - I handled this / SEP
 */
public int
do_rise(string str)
{
    object lap, tp;
    int tmp;

    if (stringp(str))
    {
        notify_fail("Rise what?\n");
        return 0;
    }

    tp = this_player();
    lap = tp->query_prop(PLAYER_M_SITTING);
    tmp = member_array(tp, sitting);
    if (!objectp(lap) && tmp == -1)
    {
        notify_fail("You are not seated.\n");
        return 0;
    }

    if (objectp(lap))
    {
        tp->catch_msg("You get up from " + QTPNAME(lap) + " lap.\n");
        lap->catch_msg(QCTNAME(tp) + " gets up from your lap.\n");
        tell_room(this_object(), QCTNAME(tp) + " gets up from " +
	    QTPNAME(lap) + " lap.\n", ({ tp, lap }) );
        in_lap = m_delete(in_lap, lap);
    }
    else if (tmp != -1)
    {
        if (objectp(lap = in_lap[tp]))
        {
            lap->catch_msg("As " + QTNAME(tp) + " is about to rise " +
                           "you get up from " + tp->query_possessive() +
                           " lap and find yourself a cushion.\n");
            tp->catch_msg(QCTNAME(lap) + " gets up from your lap and sits "+
		"on a cushion nearby.\n");
            tell_room(this_object(), QCTNAME(lap) + " get up from " +
		QTPNAME(tp) + " lap and sits down on a cushion nearby.\n",
                      ({ tp, lap }), lap );
            in_lap = m_delete(in_lap, tp);
            sitting += ({ lap });
            lap->add_prop(PLAYER_M_SITTING, 1);
        }

        write("You get up from your comfy cushion.\n");
        tell_room(this_object(), QCTNAME(tp) + " gets up from the cushion " +
                                 tp->query_pronoun() + " was sitting on.\n",
                                 ({ tp }), tp );
        sitting -= ({ tp });
    }

    tp->unset_no_show_composite();
    tp->remove_prop(PLAYER_M_SITTING);
    return 1;
}

/*
 * Function name: do_sit
 * Description  : The function for sitting down.
 * Arguments    : The arguments for the command
 * Returns      : (int)1/0 - I handle this / Not my problem
 */
public int
do_sit(string str)
{
    object *oblist, pre_lap, lap, tp;

    tp = this_player ();
#if 0
    if ((member_array(TP, sitting) != -1) ||
	(member_array(TP, m_values(in_lap)) != -1))
    {
        notify_fail("You are already sitting down.\n");
        return 0;
    }
#endif /* 0 */

    if (!stringp(str) || str == "down" || str == "cushion" ||
        parse_command(str, ({ }), "[down] [on] [the] [plump] [comfortable] 'cushion'"))
    {
        if (member_array(tp, sitting) != -1)
        {
            notify_fail("You are already sitting down.\n");
            return 0;
        }
        if (objectp(lap = tp->query_prop(PLAYER_M_SITTING)))
        {
            tp->catch_msg("You get up from " + QTPNAME(lap) +
		" lap and find yourself a cushion.\n");
            lap->catch_msg(QCTNAME(tp) + " gets up from your lap and sits on a " +
                           "cushion nearby.\n");
            tell_room(this_object(), QCTNAME(tp) + " get up from " +
		QTPNAME(lap) + " lap and sits down on a cushion nearby.\n",
                      ({ tp, lap }), tp );
            in_lap = m_delete(in_lap, lap);
        }
        else
        {
            write("You sink into the nice plump cushion.\n");
            say(QCTNAME(tp) + " sinks down into a nice plump cushion.\n");
        }
        sitting += ({ tp });
        tp->set_no_show_composite(1);
        tp->add_prop(PLAYER_M_SITTING, 1);
        return 1;
    }

    oblist = PARSE_THIS(str, "[on] [in] [the] [lap] [of] [the] %l");
    if (!sizeof(oblist))
    {
        notify_fail("Sit where?\n");
        return 0;
    }

    if (sizeof(oblist) != 1)
    {
        notify_fail("Sit in whose lap? " +
            "You can only sit in one persons lap at a time.\n");
        return 0;
    }

    if (!oblist[0]->query_prop(PLAYER_M_SITTING))
    {
        notify_fail(oblist[0]->query_The_name(tp) + " is not seated.\n");
        return 0;
    }

    if (objectp(lap = in_lap[oblist[0]]) && lap != tp)
    {
        notify_fail(lap->query_The_name(tp) + " is already sitting in the " +
                    "lap of " + oblist[0]->query_the_name(tp) + ".\n");
        return 0;
    }
    if (lap == tp)
    {
        notify_fail("You are already sitting in the lap of " +
                    oblist[0]->query_the_name(tp) + ".\n");
    }

    if (objectp(lap = oblist[0]->query_prop(PLAYER_M_SITTING)) && lap != tp)
    {
        notify_fail(oblist[0]->query_The_name(tp) + " is sitting in the " +
                    "lap of " + lap->query_the_name(tp) + ".\n");
        return 0;
    }

    if (objectp(lap = in_lap[tp]))
    {
        lap->catch_msg("As " + QTNAME(tp) + " is about to rise " +
                       "you get up from " + tp->query_possessive() + " " +
                       "lap and find yourself a cushion.\n");
        tp->catch_msg(QCTNAME(lap) + " gets up from your lap and sits on a " +
                      "cushion nearby.\n");
        tell_room(this_object(), QCTNAME(lap) + " get up from " +
	    QTPNAME(tp) + " lap and sits down on a cushion nearby.\n",
                  ({ tp, lap }), lap );
        in_lap = m_delete(in_lap, tp);
        sitting += ({ lap });
        lap->add_prop(PLAYER_M_SITTING, 1);
    }

    lap = oblist[0];
    if (objectp(pre_lap = tp->query_prop(PLAYER_M_SITTING)) && pre_lap != lap)
    {
        tp->catch_msg("You get up from " + QTPNAME(lap) + " lap and sit " +
                      "down in " + QTPNAME(pre_lap) + " lap.\n");
        pre_lap->catch_msg(QCTNAME(tp) + " gets up from your lap and sits " +
                      "down in " + QTPNAME(pre_lap) + " lap.\n");
        lap->catch_msg(QCTNAME(tp) + " gets up from " + QTPNAME(pre_lap) +
                       " lap and down in your lap.\n");
        tell_room(this_object(), QCTNAME(tp) + " get up from " +
                                 QTPNAME(pre_lap) + " lap and sits " +
                                 "down in " + QTPNAME(lap) + " lap.\n",
                  ({ tp, pre_lap, lap }), tp );
        in_lap = m_delete(in_lap, pre_lap);
    }
    else if (pre_lap == lap)
    {
        tp->catch_msg("You readjust yourself in " +
	    QTPNAME(lap) + " lap.\n");
        lap->catch_msg(QCTNAME(tp) + " readjust " +
                       QMET("query_objective", tp) + "self in your lap.\n");
        tell_room(this_object(), QCTNAME(tp) + " readjust " +
                                 QMET("query_objective", tp) + "self in " +
                                 QTPNAME(lap) + " lap.\n",
                  ({ tp, lap }), tp);
    }
    else if (tp->query_prop(PLAYER_M_SITTING))
    {
        tp->catch_msg("You get up from your cushion to sit down in " +
                      QTPNAME(lap) + " lap.\n");
        lap->catch_msg(QCTNAME(tp) + " gets up from " +
                       tp->query_possessive() + " cushion to sits down " +
                       "in your lap.\n");
        tell_room(this_object(), QCTNAME(tp) + " gets up from " +
                                 tp->query_possessive() + " cushion to " +
                                 "sits down in " + QTPNAME(lap) + " lap.\n",
                  ({ tp, lap }), tp);
        sitting -= ({ tp });
    }
    else
    {
        tp->catch_msg("You sit down in " + QTPNAME(lap) + " lap.\n");
        lap->catch_msg(QCTNAME(tp) + " sits down in your lap.\n");
        tell_room(this_object(), QCTNAME(tp) + " sits down in " +
                                 QTPNAME(lap) + " lap.\n",
                  ({ tp, lap }), tp);
    }
    tp->set_no_show_composite(1);
    tp->add_prop(PLAYER_M_SITTING, lap);
    in_lap[lap] = tp;
    return 1;
}

/*
 * Function name: do_stand
 * Description  : Command to stand up.
 * Arguments    : string str - the argument to the command.
 * Returns      : (int)1/0 - I handle this/ Not my problem
 */
public int
do_stand(string str)
{
    if (str != "up")
    {
        notify_fail("Stand what? Stand up perhaps?\n");
        return 0;
    }

    return do_rise(0);
}

/*
 * Function name: prevent_leave
 * Description  : Check if anyone is going to leave.
 * Arguments    : The object that is going to leave.
 * Returns      : (int)0 - I never prevent leaving.
 */
public int
prevent_leave(object ob)
{
    if (::prevent_leave(ob))
        return 1;
    
    if (ob->query_prop(PLAYER_M_SITTING) &&
        (query_verb() != "In") &&
        (query_verb() != "At"))
    {
        set_this_player(ob);
        do_rise(0);
    }
    return 0;
}

/*
 * Function name: leave_inv
 * Description  : Elvis has left the building... make sure
 *                he is not sitting down.
 * Arguments    : object ob - the object that left.
 *                mixed  to - where the object left.
 */
public void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);

    if (ob->query_prop(PLAYER_M_SITTING) &&
        (query_verb() != "In") &&
        (query_verb() != "At"))
    {
        set_this_player(ob);
        do_rise(0);
    }
}

/*
 * Function name: order
 * Description  : The order command.
 * Arguments    : The arguments to the command.
 * Returns      : (int)1/0 - My command/ Someone else got to handle this.
 */
public int
order(string str)
{
    string name, str1, str2, str3;
    int *arr, price, num;

    if (!host || !present(host, TO))
    {
        notify_fail("The server isn't here to take your order.\n");
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Buy what?\n");
        return 0;
    }

    if (IS_INFIDEL(this_player()))
    {
        tell_object(this_player(), "She frowns furiously "+
            "and waves you away.\n");
        return 1;
    }
    // Check for specified coins and what change to get back 
    if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3)
    {
        str3 = "";
        if (sscanf(str, "%s with %s", str1, str2) != 2)
        {
            str2 = "";
            str1 = str;
        }
    }

    if (sscanf(str1, "%d %s", num, str1) != 2)
        num = 1;

    switch(str1)
    {
        case "kahve":
        case "kahves":
        case "coffee":
        case "hot kahve":
        case "bowl of kahve":
        case "sybarun kahve":
            name = "coffee";
            price = num * 40;
            break;
	    case "spiked kahve":
        case "spiked hot kahve":
            name = "spiked_kahve";
            price = num * 250;
            break;			
        case "bread":
        case "loaf":
        case "loaves":
        case "zuccarrot bread":
        case "loaf of bread":
        case "loaf of zuccarrot bread":
            name = "bread";
            price = num * 160;  
            break;
        case "eggplant":
        case "stuffed eggplant":
        case "eggplants":
            name = "eggplant";
            /* 500g * 500g / 600 + 5 = 422 */ 
            price = num * 425;
            break;
        case "jelly":
        case "rose jelly":
        case "jellies":
        case "rose jellies":
        case "jam":
            name = "jam";
            price = num * 12;
            break;
        case "sardine":
        case "sardines":
        case "sardine in grape leaves":
            name = "sardine";
            price = num * 36;
            break;
        case "tabuele":
        case "tabueles":
        case "plate":
        case "plates":
        case "plate of tabuele":
        case "plates of tabuele":
            name = "tabuele";
            price = num * 120;
            break;
        default:
        notify_fail("I don't understand what you want to buy.\n");
        return 0;
    }

    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
        return 0;  /* pay() handles notify_fail() */

    write("You pay " + text(exclude_array(arr, TYP, TYP * 2 - 1)) + ".\n");
    if (text(exclude_array(arr, 0, TYP - 1)))
        write("You get " + text(exclude_array(arr, 0, TYP - 1)) + ".\n");
    return move_item(({name, num, TP}));
}

int
move_item(mixed arg)
{
    object drink, ob;
    string file, name;
    int i, num, inum;

    name = arg[0];
    num = arg[1];
    inum = arg[1];
    ob = arg[2];

    for (i = 0; i < inum; i++)
    {
        num--;
        file = MUS_OBJ + name;
        drink = clone_object(file);

        if (!test && (drink->move(ob)))
        {
            ob->catch_msg("You order "+ drink->query_short()+ ". "+
                "You drop "+ drink->query_short() +" on the floor.\n");
            say(QCTNAME(ob) + " drops " + drink->query_short() +".\n");
            drink->move(TO);
        } 
        else if (!test) 
        {
            if (num == 0)
            {
                if (arg[1] > 1)
                {
                    ob->catch_msg("You order "+ drink->short() + 
                        " from Mirmarin.\nShe gives you "+ arg[1] +".\n");
                    say(QCTNAME(ob) + " orders " + drink->short() +" from "+
                        "Mirmarin.\nShe gives "+ ob->query_objective() +" "+ 
                        inum +".\n", ob);
                } 
                else 
                {
                    ob->catch_msg("You buy " + drink->short() + " from her.\n");
                    say(QCTNAME(ob) + " buys " + drink->short() + ".\n",
                        ob);
                }
            }
        } 
        else 
        {
            say(QCTNAME(ob) + " seems to be estimating something.\n", ob);
            return 1;
        }
        if (num < 1)
            break;
    }
    if (num > 0)
        set_alarm(1.0,0.0,"move_item", ({name, num, ob}));
    return 1;
}

/*
 * Function name: test
 * Description:   To allow the buyer to see what would happen with change and
 *                payment depending on how the buyer chooses to pay.
 * Arguments:     str - name of drink an possibly description on how to pay and
 *                      get the change
 */
public int
test(string str)
{
    int i = 0;
    string str1 = "";

    if (sscanf(str, "buy %s", str1)) 
    {
        test = 1;
        write("This would be the result of a buy:\n");
        i = order(str1);
        test = 0;
    }
    else
        notify_fail("Test what?\n");
    return i;
}

/*
 * Function name: init
 * Description  : Init the local command set.
 */
public void
init()
{
    ::init();

    add_action(do_rise,  "rise");
    add_action(do_sit,   "sit");
    add_action(do_sit,   "sink");
    add_action(do_stand, "stand");
    add_action(order,    "buy");
    add_action(order,    "order");
}
