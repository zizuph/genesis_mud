/*
 * /d/Gondor/common/jewelry/book.c
 *
 * This book explains knightly orders.
 *
 * Coded by Gwyneth, 08/02
 */
inherit "/std/book";

#include "jewelry.h"
#include <composite.h>
#include <macros.h>
#include <money.h>

public string
long_desc()
{
    string str = "This fine leather book on the table explains all about " +
        "the orders of chivalry, and how to found them.";
    if (book_is_closed)
        return str + " The book is closed.\n";
    else
        return str + " The book is open. Perhaps you could read it or " +
            "'turn page [to number].\n";
}

public string
short_desc()
{
    return (book_is_closed ? "closed " : "open ") + "leather book on a table";
    
}

public void
create_book()
{
    set_max_pages(6);
    set_name("book");
    add_name("_chivalric_order_book_");
    set_adj(({ "leather", "bound" }));
    set_short(&short_desc());
    book_is_closed = 0;
    set_long(&long_desc());
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_M_NO_GET, "The book is attached to the table.\n");
    add_prop(OBJ_I_VOLUME, 100);
}

varargs void
read_book_at_page(int which, string verb)
{
    int i, size;
    mixed *order;
    object room;
    string *orders, txt = "", colour;

    switch (which)
    {
    case 1:
        txt = "Page 1: ...............  Index\n" +
              "Page 2: ...............  History\n" +
              "Page 3: ...............  Founding an Order\n" +
              "Page 4: ...............  Membership and Regalia\n" +
              "Page 5: ...............  Existing Orders\n" +
              "Page 6: ...............  Command Lists\n\n" +
              "Turn page [to number]\n";
        break;
    case 2:
        txt = "Orders of knighthood have existed for centuries.  The " +
              "first were autonomous military organizations, consisting " +
              "of a large number of knights and a few commanders, who " +
              "eventually became identified by emblems of rank which they " +
              "would wear.  After a time, various kings and princes wished " +
              "to have their own orders of knighthood, and founded small " +
              "groups of knights, often no more than a dozen, who would " +
              "wear special insignia to show the honour conferred on them.  " +
              "In some of these orders, lower ranks of membership were " +
              "created to allow for bestowing of membership upon those who " +
              "had acted heroically, but who for one reason or another were " +
              "considered as yet unsuited to the highest rank.  Some orders " +
              "were only quasi-military, such as those founded to run " +
              "hospitals in locations where foreign campaigns were " +
              "underway.  As members returned, they constructed hospitals " +
              "in their native lands, and their orders gradually shifted " +
              "from military to charitable in nature, and it became " +
              "acceptable to award an order of chivalry to those who " +
              "performed beneficial civilian actions for society or in " +
              "service of their ruler.\n\n" +  
              "Because orders of knighthood originated in serving of a " +
              "common purpose, and did not pay homage to any particular " +
              "state or ruler, anyone can found an order of chivalry.  How " +
              "seriously people will take it obviously depends on how well " +
              "you select your members.  Some of the most prestigious " +
              "orders never created lower-ranking memberships, and these " +
              "also often limited themselves to members chosen from royal " +
              "families and the very highest ranks of the nobility.  Anyone " +
              "can wear a flashy insignia, but the respect it commands is " +
              "almost entirely a function of the selection process.\n";

        break;
    case 3:
        txt = "If you wish to found an order of chivalry, you may do so " +
              "for 500 platinum coins.  You will be able to create an " +
              "emblem for your members, and you will have the exclusive " +
              "right to the name you choose.  Naturally you will be able " +
              "to decide who is admitted to the ranks, although we cannot " +
              "control what happens to the regalia after they leave the " +
              "shop.  Your 500 platinum in fees also cover the cost of your " +
              "own regalia as a Knight Grand Cross/Grandmaster of the " +
              "order, which you may pick up next door when you 'order " +
              "regalia' after you pay for your order of chivalry.  Be sure " +
              "to order it before Armageddon, or you will have to pay the " +
              "full price of 250 platinum coins. Members " +
              "of an order of chivalry are usually expected to pay for " +
              "their own insignia. One may found more than one order, as " +
              "well as belong to more than one order.\n\nImportant " +
              "Warning!!\n\nAny orders " +
              "which are inappropriately named will be removed with No " +
              "Refund. Choose names that will not be offensive, such as " +
              "an order named <playername> is a Dork or any orders with a " +
              "player's name in it that is not the founder's name. Also, do " +
              "not choose names that are overly close to other named orders. " +
              "For example, if an order is called the Golden Dragon, do not " +
              "name your order the Gold Dragon.\n";
        break;
    case 4:
        txt = "We sell the following regalia for orders of chivalry:\n\n" +
            "The collar of a Knight Grand Cross\n" +
            "A Knight Grand Cross is a member of the highest rank, with " +
            "the exception of the head of the order.  Bestowing of a KGC " +
            "implies the very highest degree of trust in the recipient.  " +
            "Knights Grand Cross should be referred to as \"Sir\" or " +
            "\"Dame.\"  They wear a massive and elaborate chain with an " +
            "emblem of their order around their necks. Cost: 250 platinum, " +
            "with the option to use 10 stones (provided by the buyer) in " +
            "the collar.\n\n" +
            "The collar of a Knight Commander\n" +
            "A Knight Commander is a member of the second highest rank, " +
            "and wears an ornament hanging from a ribbon around their " +
            "neck.  Like a KGC, they should be addressed as \"Sir\" or " +
            "\"Dame\" unless they have a higher office or rank.  Cost of " +
            "regalia is 150 platinum, and 5 stones may optionally be " +
            "mounted on the collar.\n\n" +
            "The breast badge of a member\n" +
            "A member of an order is one who has contributed to the " +
            "mission of the order in some way, and who has allegiance to " +
            "the order.  Their title does not change as a result of their " +
            "membership, so members of orders should be addressed as suits " +
            "their station otherwise.  Members wear a medal with the " +
            "insignia of the order upon their chest.  Cost is 50 platinum " +
            "coins.\n\nRegalia for orders of chivalry may be purchased " +
            "next door at the jewelry store when you 'purchase regalia'.\n";
        break;
    case 5:
        room = find_object(JEWELRY_DIR + "chivalry");
        orders = room->query_orders();
        if (!sizeof(orders))
        {
            txt = "There are no orders of chivalry yet.\n";
            break;
        }

        for (i = 0, size = sizeof(orders); i < size; i++)
        {
            order = room->query_order(orders[i]);
            colour = (member_array("and", explode(order[2], " ")) == -1 ? 
                "colour is " : "colours are ");
            txt += "The Order of " + orders[i] + " was founded by " +
                capitalize(order[0]) + ".\nIts emblem is " + order[1] +
                " and its " + colour + order[2] + ".\n";
            if (sizeof(order[3]))
                txt += "Knights Grand Cross: " + 
                    COMPOSITE_WORDS(order[3]) + ".\n";
            if (sizeof(order[4]))
                txt += "Knights Commander: " +
                    COMPOSITE_WORDS(order[4]) + ".\n";
            if (sizeof(order[5]))
                txt += "Members: " + COMPOSITE_WORDS(order[5]) + ".\n";
            txt += "\n";
        }
        break;
    case 6:
        txt = "To found an order, you must 'found <Order Name>', " +
              "then 'select emblem <emblem> for <Order Name>' " +
              "and 'select colour <colour> for <Order Name>'. " +
              "Once you have chosen the name, emblem and colour, " +
              "you must 'pay for <Order Name>'. This will cost " +
              "you " + MONEY_TEXT_SPLIT(FOUND_COST) + ", but " +
              "comes with the collar of a Knight Grand Cross. You " +
              "will then be the Grandmaster of your new order.\n\n" +
              "If you are the Grandmaster of an order, you may:\n" +
              "Pass Grandmaster of <Order Name> to <name>\n" +
              "Expel <name> from <Order Name>\n" +
              "Admit <name> as a <m/kc/kgc> to <Order Name>\n" +
              "Promote <name> to <kc/kgc> in <Order Name>\n" +
              "Demote <name> to <m/kc> in <Order Name>\n" +
              "Where m is Member, kc is Knight Commander and kgc is " +
              "Knight Grand Cross\n\n" +
              "If you belong to an order of chivalry, you may:\n" +
              "Purchase regalia for <Order Name> (Next door at the " +
              "jewelry store)\n" +
              "Expel myself from <Order Name>\n\n" +
              "Grandmasters must first pass their office to another " +
              "before they may expel themselves.\n";
        break;
    default:
        txt = "The page is empty.\n";
    }

    this_player()->more(txt);
    return;
}

void
open_me()
{
    if (!book_is_closed)
    {
        write("The leather book on the table is already open.\n");
        return;
    }

    what_page = 1;

    write("You open the leather book on the table at page " +
        LANG_WNUM(what_page) + ".\n");
    say(QCTNAME(this_player()) + " opens the leather book on the table.\n");
    book_is_closed = 0;
}

/*
 * Function name: close_me
 * Description:   closes the book again
 */
void
close_me()
{
    if (book_is_closed)
    {
        write("The leather book is already closed.\n");
        return;
    }

    write("You close the leather book.\n");
    say(QCTNAME(this_player()) + " closes the leather book.\n");

    what_page = 1;
    book_is_closed = 1;
}
