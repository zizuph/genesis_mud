/*
 * /d/Gondor/common/jewelry/jewelry_shop.c
 *
 * A shop where one can purchase a large variety of jewelry and adornment
 * which autoloads. Only 5 pieces may be kept through reboots.
 * This is also where one may establish or join a Knightly Order.
 *
 * Coded by Gwyneth and Auberon, 08/26/02
 */
inherit "/d/Gondor/std/room.c";
inherit "/lib/shop.c";

#include <composite.h>
#include <macros.h>
#include <money.h>
#include "jewelry.h"

/* Ex. gOrders = ([ "gwyneth" : ({ "knightly", "silver", "circlet", "ruby", 
                     10, "pearl", 5, 0, 12960, pickup_time, 
                     "To my love, from Gwyneth." }), 
                     "auberon" : ({ "ducal", "gold", "coronet", 
                    "ruby", 25, "n", 0, 1, 1036800, pickup_time, "" }) ])
  ([ name : ({ adjective, metal, type, gem1, number-of-gem1, gem2, 
     number-of-gem2, paid, cost, time-to-pick-up, engraving }) ])
  ([ name : ({ "regalia", order, rank, emblem, colour, gem1, num1, gem2,
     num2, paid, cost, time-to-pick-up }) ])
*/

/* Used to keep track of which variable belongs in which index of gOrders */
#define ADJV_IND 0
#define METL_IND 1
#define TYPE_IND 2
#define GEM1_IND 3
#define NUM1_IND 4
#define GEM2_IND 5
#define NUM2_IND 6
#define PAID_IND 7
#define COST_IND 8
#define TIME_IND 9
#define ENGR_IND 10
#define JEWELLER_GAVE_INFO "_jeweller_gave_info_"

mapping gOrders = ([]);

/* Ex. gGemsNeed = ([ "auberon" : ({ "ruby", 10, "diamond", 15 }) ]) 
   both gems and their number */
mapping gGemsNeed = ([]);
object  gKeeper, gCounter;
int gAlarm;

public string keeper_price(string str);
public int keeper_say(string str, object who);
public string regalia_say();

public void
reset_room()
{
    gKeeper = clone_npc(gKeeper, JEWELRY_DIR + "jeweller");
    if (!objectp(gCounter))
    {
        gCounter = clone_object(JEWELRY_DIR + "counter");
        gCounter->move(this_object());
    }
}

public void
shop_info(object who)
{
    keeper_say("Please examine each of the items in the display case for " +
        "examples of my work. I will also buy jewelry and regalia that " +
        "come from my shop. You'll find that mine are the best prices " +
        "anywhere! Read the instructions if you want to know how to order.",
        who);

    who->add_prop(JEWELLER_GAVE_INFO, 1);

    return;
}

public string
read_sign()
{
    if (!this_player()->query_prop(JEWELLER_GAVE_INFO))
        set_alarm(1.0, 0.0, &shop_info(this_player()));

    return "" +
    "    Jewelry .......... Plats ...... Metal .. Gems\n" +
    "\n" +
    "    Rings ............ 10-26 ...... Any .... 0 to 3\n" +
    "    Bracelets ........ 2-18 ....... Any .... 0 or 25\n" +
    "    Anklets .......... 4-20 ....... Any .... 0 or 40\n" +
    "    Necklaces ........ 8-24 ....... Any .... 0 to 100\n" +
    "    Pendants ......... 8-24 ....... Any .... 1\n" +
    "    Chokers .......... 8-24 ....... Any .... 0 or 45\n" +
    "    Torcs\n" +
    "      Ribbon  ........ 16-32 ...... B/S/G .. 0\n" +
    "      Braided ........ 165-320 .... B/S/G .. 0\n" +
    "    Medals ........... 50-66 ...... Any .... 0 to 5\n" +
    "    Circlets\n" +
    "      Simple ......... 15-35 ...... B/S .... 0 or 5\n" +
    "      Knightly ....... 75-100 ..... S/E .... 0 or 10\n" +
    "    Coronets\n" +
    "      Baronial ....... 250-400 .... E/G .... 0 or 15\n" +
    "      Ducal .......... 600-750 .... G/P .... 25\n" +
    "    Crowns\n" +
    "      Princely ....... 850-1000 ... G/P/M .. 35\n" +
    "      Royal .......... 1200-2000 .. G/P/M .. 50\n" +
    "    Equestrian Ring .. 25 ......... G ...... 0\n" +
    "    Collars .......... 125-175 .... S/E/G .. 0\n" +
    "    Member Medals .... 50 ......... G ...... 0\n" +
    "    Collar of KC ..... 150 ........ G ...... 0 or 5\n" +
    "    Collar of KGC .... 250 ........ G ...... 0 or 10\n" +
    "\n" +
    "    B = Bronze S = Silver   E = Electrum,\n" +
    "    G = Gold   P = Platinum M = Mithril\n" +
    "    All items save, though you aren't allowed to\n" +
    "    retain more than five pieces of jewelry (non-regalia).\n";
}

public string
instructions()
{
    return "" +
    "    Order with 'order <jewelry>'. I will ask you for details.\n\n" +
    "    Offer gems needed by placing the exact number of gems on the\n" +
    "    counter, and then 'offer gems' when you are done ordering.\n" +
    "    I will not begin my work until I have all the needed gems.\n\n" +
    "    Retrieve gems mistakenly placed on the counter with 'retrieve'.\n" +
    "    Only you may retrieve the gems you placed on the counter.\n\n" +
    "    Cancel before paying with 'cancel'.\n\n" +
    "    I will send a messenger if you aren't here when your order is " +
    "done.\n\n" +
    "    Collect your completed order with 'pay' or 'collect'.\n\n" +
    "    Read the sign for details on the jewelry crafted here.\n";
}

public void
create_gondor()
{
    set_long("Light floods in through the large glass windows of this " +
        "shop, making the gems and jewelry sparkle brilliantly. A glass " +
        "counter takes up much of the room with its displays of everything " +
        "from the smallest bronze bracelet to a gemstone-encrusted royal " +
        "crown. A sign on the counter displays a list of the jeweller's " +
        "prices and next to it, some instructions explain how the shop " +
        "works. The artwork hanging from the walls and the soothing pattern " +
        "on the stone floor make you feel relaxed and ready to indulge " +
        "yourself with a precious new piece of jewelry. The jeweller " +
        "eagerly awaits your business on the other side of the counter. " +
        "Two doorways lead east and north.\n");
    set_short("jewelry shop");
    config_default_trade();

    add_item(({ "window", "windows", "large window", "large windows",
        "glass window", "glass windows", "large glass window",
        "large glass windows" }), "Such large sheets of glass must have " +
        "cost the owner of this shop a small fortune. They are strategically " +
        "placed to let the sunlight shine onto the more expensive items.\n");
    add_item(({ "artwork", "walls", "wall" }), "The artwork hanging from " +
        "the walls depicts lovely maidens or goddesses dressed in flowing " +
        "gowns and sparkling jewelry.\n");
    add_item(({ "pattern", "floor", "stone floor" }), "Individual coloured " +
        "stones make up the floor. They are pleasing to they eye, yet do " +
        "not overtly draw your attention.\n");
    add_item(({ "ring", "rings" }), &keeper_price("ring"));
    add_item(({ "bracelet", "bracelets" }), &keeper_price("bracelet"));
    add_item(({ "anklet", "anklets" }), &keeper_price("anklet"));
    add_item(({ "necklace", "necklaces" }), &keeper_price("necklace"));
    add_item(({ "pendant", "pendants" }), &keeper_price("pendant"));
    add_item(({ "choker", "chokers" }), &keeper_price("choker"));
    add_item(({ "torc", "torcs" }), &keeper_price("torc"));
    add_item(({ "ribbon torc", "ribbon torcs" }), &keeper_price("ribbon torc"));
    add_item(({ "braided torc", "braided torcs" }),
        &keeper_price("braided torc"));
    add_item(({ "medal", "medals" }), &keeper_price("medal"));
    add_item(({ "collar", "collars", "collar of office", "collars of office"}),
         &keeper_price("collar"));
    add_item(({ "circlet", "circlets" }), "You see simple circlets and " +
        "knightly circlets. Perhaps you could take a closer look.\n");
    add_item(({ "coronet", "coronets" }), "You see baronial coronets and " +
        "ducal coronets. Perhaps you could take a closer look.\n");
    add_item(({ "crown", "crowns" }), "You see princely crowns and " +
        "royal crowns. Perhaps you could take a closer look.\n");
    add_item(({ "simple circlet", "simple circlets" }),
        &keeper_price("simple circlet"));
    add_item(({ "knightly circlet", "knightly circlets" }),
        &keeper_price("knightly circlet"));
    add_item(({ "baronial coronet", "baronial coronets" }),
        &keeper_price("baronial coronet"));
    add_item(({ "ducal coronet", "ducal coronets" }),
        &keeper_price("ducal coronet"));
    add_item(({ "princely crown", "princely crowns" }),
        &keeper_price("princely crown"));
    add_item(({ "royal crown", "royal crowns",
        "gemstone-encrusted royal crown" }), &keeper_price("royal crown"));
    add_item(({ "regalia", "collars of the knight grand cross",
        "collars of the knight commander", "gold medal", "gold medals",
        "gold medals of membership", "gold medal", "gold medal of membership",
        "collar of the knight commander", "collar of the knight grand cross"}),
        &regalia_say());
    add_item(({ "list", "sign" }), &read_sign());
    add_item("instructions", &instructions());
    add_cmd_item(({ "list", "sign" }), "read", &read_sign());
    add_cmd_item("instructions", "read", &instructions());
    set_store_room(JEWELRY_DIR + "store_room");
    set_money_give_max(3456000);
    set_money_give_out(({500, 500, 500, 2000}));
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(JEWELRY_DIR + "chivalry", "north");
    add_exit("/d/Gondor/pelargir/misc/jewel_shop", "east");
    reset_room();
}

public string
regalia_say()
{
    keeper_say("You can find out more about regalia and orders of " +
        "chivalry to the north.", this_player());
    return "";
}

public string
keeper_price(string str)
{
    int price_low = 0, price_high = 0;
    object who = this_player();
    string desc;

    switch(str)
    {
    case "ring":
        desc = "You see rings made out of all sorts " +
        "of metals.  Some rings are simple bands with no gems, while others " +
        "have one, two or even three gems adorning them.  You also see " +
        "some equestrian rings.  These simple but elegant gold rings " +
        "traditionally identify members of the hereditary knightly classes. " +
        "The perfect gift for a Solamnian Knight of the Sword, who might " +
        "feel prohibited by the rules of that order from owning anything " +
        "more extravagant.\n";
        set_alarm(1.0, 0.0, &keeper_say("The equestrian ring is " + 
            MONEY_TEXT_SPLIT(EQS_RING_PRICE) + ", while the others " +
            "range from " + MONEY_TEXT_SPLIT(RING_PRICE+BRONZE_PRICE) +
            " to " + MONEY_TEXT_SPLIT(RING_PRICE+MITHRIL_PRICE) + ".", who));
        return desc;
    case "bracelet":
        desc = "You see bracelets made out of all sorts of metals.  Some " +
            "bracelets are chains with no gems, while the others have " +
            "25 gems.\n";
        price_low = BRACELET_PRICE + BRONZE_PRICE;
        price_high = BRACELET_PRICE + MITHRIL_PRICE;
        break;
    case "anklet":
        desc = "You see anklets made out of all sorts of metals.  Some " +
            "anklets are chains with no gems, while the others have 40 gems.\n";
        price_low = ANKLET_PRICE + BRONZE_PRICE;
        price_high = ANKLET_PRICE + MITHRIL_PRICE;
        break;
    case "choker":
        desc = "You see chokers made out of all sorts of metals.  They all " +
            "have 45 gems.\n";
        price_low = NECKLACE_PRICE + BRONZE_PRICE;
        price_high = NECKLACE_PRICE + MITHRIL_PRICE;
        break;
    case "necklace":
        desc = "You see necklaces made out of all sorts of metals.  Some " +
            "necklaces are chains with no gems, while others have anywhere " +
            "from one to 100 gems.\n";
        price_low = NECKLACE_PRICE + BRONZE_PRICE;
        price_high = NECKLACE_PRICE + MITHRIL_PRICE;
        break;
    case "pendant":
        desc = "You see pendants made out of all sorts of metals.  They " +
            "all have a single gemstone.\n";
        price_low = NECKLACE_PRICE + BRONZE_PRICE;
        price_high = NECKLACE_PRICE + MITHRIL_PRICE;
        break;
    case "medal":
        desc = "You see medals made out of all sorts of metals.  Some " +
            "medals have no gemstones, while others have anywhere from " +
            "one to five gems.\n";
        price_low = MEDAL_PRICE + BRONZE_PRICE;
        price_high = MEDAL_PRICE + MITHRIL_PRICE;
        break;
    case "torc":
        desc = "You see ribbon torcs and braided torcs of bronze, silver " +
            "and gold. Perhaps you could examine each closer?\n";
        price_low = TORC_PRICE + BRONZE_PRICE;
        price_high = 10*(TORC_PRICE + MITHRIL_PRICE);
        break;
    case "braided torc":
        desc = "This piece of neckwear looks like a finely twisted cable " +
            "or rope of metal, with solid loops at the front. The metal " +
            "indicates the rank and level of religious responsibility of " +
            "the wearer. Gold is usually reserved for clerics, or those " +
            "who rule by the will of the gods. Silver indicates status as " +
            "a minor cleric, or warrior with significant duties to the " +
            "deities. Bronze is what is worn by the great majority of the " +
            "free, property-owning population. The design is vaguely " +
            "reminiscent of a garotte, making one think that perhaps the " +
            "wearers were symbolically offering themselves to the gods by " +
            "wearing them.\n";
        price_low = 10*(TORC_PRICE + BRONZE_PRICE);
        price_high = 10*(TORC_PRICE + MITHRIL_PRICE);
        break;
    case "ribbon torc":
        desc = "This piece of neckwear is made of a strip of metal about " +
            "three quarters of an inch wide, which has been twisted into " +
            "a helix, then bent into an almost complete circle. The metal " +
            "indicates the rank and level of religious responsibility of " +
            "the wearer. Gold is usually reserved for clerics, or those " +
            "who rule by the will of the gods. Silver indicates status as " +
            "a minor cleric, or warrior with significant duties to the " +
            "deities. Bronze is what is worn by the great majority of the " +
            "free, property-owning population. The design is vaguely " +
            "reminiscent of a garotte, making one think that perhaps the " +
            "wearers were symbolically offering themselves to the gods by " +
            "wearing them.\n";
        price_low = TORC_PRICE + BRONZE_PRICE;
        price_high = TORC_PRICE + MITHRIL_PRICE;
        break;
    case "collar":
        desc = "These fine collars of office are suitable for heralds, " +
            "ambassadors, justices of high courts, mayors of major cities " +
            "and the like.  They resemble the collars worn by Knights Grand " +
            "Cross, except that they do not have the pendant of an order " +
            "of knighthood attached.  They are also known as \"Collars of " +
            "SS\" as the links resemble the letter \"S.\" You see collars " +
            "made only out of silver, electrum and gold.\n";
        set_alarm(1.0, 0.0, &keeper_say("The collars of office range from " + 
            MONEY_TEXT_SPLIT(COLLAR_SILVER_PRICE) + " to " + 
            MONEY_TEXT_SPLIT(COLLAR_GOLD_PRICE) + ".", who));
        return desc;
    case "simple circlet":
        desc = "The perfect gift for most individuals, this is a " +
            "well-crafted circlet which can be worn on the head or fitted " +
            "over a helmet.  Five stones may be mounted in the circlet at " +
            "the buyer's option.\n";
        price_low = SIMPLE_BRONZE_PRICE;
        price_high = SIMPLE_SILVER_PRICE;
        break;
    case "knightly circlet":
        desc = "This circlet is wider and more substantial than the basic " +
            "model, and implies that the wearer is, or has served as a " +
            "knight, or at minimum is the child or wife of a knight.  Use " +
            "by others is likely to be viewed as somewhat pompous.  Ten " +
            "stones may optionally be mounted in this beautifully finished " +
            "piece.\n";
        price_low = KNIGHTLY_SILVER_PRICE;
        price_high = KNIGHTLY_ELECTRUM_PRICE;
        break;
    case "baronial coronet":
        desc = "This coronet falls somewhere between the knight's circlet " +
            "and a traditional crown, with decorative details not found on " +
            "the humbler pieces, and a few pearls around the top.  Fifteen " +
            "stones may be added at the the buyer's option.  This " +
            "beautiful piece is suitable for those who command a number of " +
            "cavalry, or a very large contingent of footsoldiers.  Use by " +
            "others might be considered in questionable taste, or (in some " +
            "jurisdictions) even treasonous.\n";
        price_low = BARONIAL_ELECTRUM_PRICE;
        price_high = BARONIAL_GOLD_PRICE;
        break;
    case "ducal coronet":
        desc = "This coronet is a more modest version of the royal " +
            "crown, with beautiful leaf-shaped decorations and pearls " +
            "around the top, and twenty-five gems of your choice " +
            "arranged around the lower part. On crowns of this rank or " +
            "above, the gemstones are not optional, as the wearer is " +
            "assumed to have vast estates, the right to mete out justice, " +
            "levy taxes, and so forth -- which means great wealth. Like " +
            "the higher-ranking crowns, this piece is lined with ermine " +
            "fur.\n";
        price_low = DUCAL_GOLD_PRICE;
        price_high = DUCAL_PLAT_PRICE;
        break;
    case "princely crown":
        desc = "This crown differs from the royal crown only in that " +
            "it does not have bars running across the top.  Extensively " +
            "decorated in gold, pearls and 35 gemstones, this piece is " +
            "worthy of those who command sovereign orders of knighthood " +
            "or semi-autonomous nation states, as well as heirs-apparent " +
            "to kingdoms.\n";
        price_low = PRINCELY_GOLD_PRICE;
        price_high = PRINCELY_MITHRIL_PRICE;
        break;
    case "royal crown":
        desc = "Worthy of any king or queen, this grandly-scaled piece " +
            "is coated in 50 gemstones, ermine lined, and ornately " +
            "embellished.  Four gold bars gracefully arc cross the top, " +
            "which is trimmed with many small pearls and ornamented at " +
            "the apex.  The perfect crown for one who rules a major, " +
            "autonomous nation.  Keep your bodyguard with you, everyone " +
            "will be jealous!\n";
        price_low = ROYAL_GOLD_PRICE;
        price_high = ROYAL_MITHRIL_PRICE;
        break;
    default:
        return "";
    }

    set_alarm(1.0, 0.0, &keeper_say("The " + LANG_PWORD(str) + " range from " + 
        MONEY_TEXT_SPLIT(price_low) + " to " +
        MONEY_TEXT_SPLIT(price_high) + ".", who));
    return desc;
}

public int
keeper_say(string str, object who)
{
    if (!present(who))
        return 0;

    if (objectp(gKeeper) && present(gKeeper, this_object()))
    {
        who->catch_tell(gKeeper->query_The_name(who) + " says to you: " + 
            str + "\n");
        tell_room(this_object(), QCTNAME(gKeeper) + " says to " + QTNAME(who) +
            ": " + str + "\n", ({ who }));
        return 1;
    }
    else
        return 2;
}

public string
list_gems_need(string name)
{
    int size, num;
    string *text = ({});

    if (member_array(name, m_indexes(gGemsNeed)) == -1)
        return "";

    size = sizeof(gGemsNeed[name]);

    if (!size)
        return "";

    if (size >= 2)
    {
        num = gGemsNeed[name][1];
        /* 2 rubies */
        text += ({ num + " " + (num > 1 ? LANG_PWORD(gGemsNeed[name][0]) : 
            gGemsNeed[name][0])});
    }

    if (size >= 4)
    {
        /* 1 diamond */
        num = gGemsNeed[name][3];
        text += ({ num + " " + (num > 1 ? LANG_PWORD(gGemsNeed[name][2]) : 
            gGemsNeed[name][2])});
    }

    return COMPOSITE_WORDS(text);
}

public string
list_ordered(string name)
{
    int num;
    string text, gem, *gems = ({});

    if (member_array(name, m_indexes(gOrders)) == -1)
        return "";

    if (gOrders[name][0] == "regalia")
    {
        text = "You have ordered a "; 
        if (gOrders[name][2] == MEMBER_RANK)
            text += "gold medal";
        else
            text += "gold collar of a Knight " + (gOrders[name][2] == KC_RANK ? 
                "Commander" : "Grand Cross");

        text += " for the Order of " + gOrders[name][1];

        if (!gOrders[name][6])
            return text + ".\n";

        text += ". It has ";
        num = gOrders[name][6];
        if (num == 1)
            text += "one " + gOrders[name][5];
        else
            text += LANG_NUM2WORD(num) + " " + LANG_PWORD(gOrders[name][5]);

        num = gOrders[name][8];
        if (!num)
            return (text + ".\n");
        else if (num == 1)
            text += " and one " + gOrders[name][7];
        else
            text += " and " + LANG_NUM2WORD(num) + " " +
                LANG_PWORD(gOrders[name][7]);

        return (text + ".\n");
    }

    /* Adjective, if any */
    if (strlen(gOrders[name][ADJV_IND]))
        text = "You have ordered " + LANG_ADDART(gOrders[name][ADJV_IND]) + 
            " " + gOrders[name][TYPE_IND] + " of " + gOrders[name][METL_IND] +
            ".";
    else
        text = "You have ordered " + LANG_ADDART(gOrders[name][METL_IND]) + 
            " " + gOrders[name][TYPE_IND] + ".";

    if (!gOrders[name][NUM1_IND])
    {
        if (strlen(gOrders[name][ENGR_IND]))
            text += " It is engraved with the words: " +
            gOrders[name][ENGR_IND] + ".";
        return (text + "\n");
    }

    text += " It has ";
    num = gOrders[name][NUM1_IND];
    if (num == 1)
        text += "one " + gOrders[name][GEM1_IND];
    else
        text += LANG_NUM2WORD(num) + " " + LANG_PWORD(gOrders[name][GEM1_IND]);

    num = gOrders[name][NUM2_IND];
    if (!num)
        return (text + ".\n");
    else if (num == 1)
        text += " and one " + gOrders[name][GEM2_IND];
    else
        text += " and " + LANG_NUM2WORD(num) + " " + 
            LANG_PWORD(gOrders[name][GEM2_IND]);

    if (strlen(gOrders[name][ENGR_IND]))
        text += " It is engraved with the words: " + gOrders[name][ENGR_IND];

    return (text + "\n");
}

public void
pickup_msg(string name)
{
    int index;
    object who = find_living(name);

    index = member_array(name, m_indexes(gOrders));
    if (index == -1)
        return;

    if (!objectp(who))
    {
        gOrders = m_delete(gOrders, name);
        return;
    }

    if (!present(who, this_object()))
        who->catch_tell("A messenger boy runs up to you and tells you that " +
            "the jeweller has completed your order. You may 'collect' it " +
            "at your convenience.\n");
    else
        who->catch_tell(gKeeper->query_The_name(who) + " has completed your " +
            "order. You may 'collect' it at your convenience.\n");
    return;
}

public void
set_orders(string name, string desc, string metal, string jtype, 
  string gem1, int num1, string gem2, int num2, int pickup, int cost,
  string engrave)
{
    gOrders += ([ name : ({ desc, metal, jtype, gem1, num1, gem2, num2, 
        0, cost, pickup, engrave }) ]);
    keeper_say(list_ordered(name), find_player(name));
    keeper_say("That will be " + MONEY_TEXT_SPLIT(cost) + ". Pay " +
        "me when the " + jtype + " is finished.", find_player(name));

    if (num1)
    {
        gGemsNeed[name] = ({ gem1, num1 });

        if (num2 > 0)
            gGemsNeed[name] += ({ gem2, num2 });

        keeper_say("I will start my work as soon as I have " +
            list_gems_need(name) + ". Put your gems on the " +
            "counter and 'offer' them to me when you are ready. Ask me if " +
            "you don't understand how to offer me the gems.", 
            find_player(name));
    }
    else
        set_alarm(CONSTRUCT_TIME, 0.0, &pickup_msg(name));
    return;
}

public void
set_regalia_orders(string name, string order, int rank, string emblem,
  string colour, string gem1, int num1, string gem2, int num2, int pickup,
  int cost)
{
    gOrders += ([ name : ({ "regalia", order, rank, emblem, colour, 
        gem1, num1, gem2, num2, 0, cost, pickup }) ]);

    keeper_say(list_ordered(name), find_player(name));
    keeper_say("That will be " + MONEY_TEXT_SPLIT(cost) + ". Pay " +
        "me when the regalia is finished.", find_player(name));

    if (num1)
    {
        gGemsNeed[name] = ({ gem1, num1 });

        if (num2 > 0)
            gGemsNeed[name] += ({ gem2, num2 });

        keeper_say("I will start my work as soon as I have " +
            list_gems_need(name) + ". Put your gems on the " +
            "counter and 'offer' them to me when you are ready. Ask me if " +
            "you don't understand how to offer the gems.", 
            find_player(name));
    }
    else
        set_alarm(CONSTRUCT_TIME, 0.0, &pickup_msg(name));
    return;
}

public int
order(string str)
{
    int i;
    object *jewelry, order_obj;
    string name = this_player()->query_real_name();

    if (!strlen(str))
    {
        notify_fail("Order necklace? Order ring? What do you want to order?\n");
        return 0;
    }

    if (member_array(name, m_indexes(gOrders)) != -1)
    {
        if (gOrders[name][0] == "regalia")
            keeper_say("You have already ordered regalia. If you want, you " +
                "can cancel your order.", this_player());
        else
            keeper_say("You have already ordered " + 
                LANG_ADDART(gOrders[name][TYPE_IND]) + ". If you want, you " +
                "can cancel your order.", this_player());

        return 1;
    }

    jewelry = deep_inventory(this_player());
    for (i = sizeof(jewelry) - 1; i >= 0; i--)
        if (!jewelry[i]->id(JEWELRY_ID))
            jewelry -= ({ jewelry[i] });

    if (str != "regalia" && sizeof(jewelry) >= 5)
    {
        keeper_say("You can order a piece of jewelry, but you must first " +
            "get rid of one of your other pieces. You can only have " +
            "five at a time.", this_player());
        return 1;
    }

    str = lower_case(str);

    switch(str)
    {
    case "circlet":
    case "coronet":
    case "crown":
    case "ring":
    case "necklace":
    case "choker":
    case "pendant":
    case "bracelet":
    case "anklet":
    case "torc":
    case "medal":
    case "collar":
    case "collar of office":
    case "regalia":
        order_obj = clone_object(JEWELRY_DIR + "order_obj");
        order_obj->move(this_player(), 1);
        order_obj->order(str);
        return 1;
    default:
        keeper_say("That is not an option. Please read the sign and " +
            "try again.", this_player());
        return 1;
    }
}

public int
collect(string str)
{
    int *arr, ms = sizeof(MONEY_TYPES), pickup, paid, cost;
    object jewelry;
    string kind, txt, name = this_player()->query_real_name();
    mixed *details;

    if (member_array(name, m_indexes(gOrders)) == -1)
    {
        keeper_say("You haven't completed an order. Please read the sign.",
            this_player());
        return 1;
    }


    pickup = (gOrders[name][0] == "regalia" ? gOrders[name][11] :
        gOrders[name][TIME_IND]);

    if (pickup <= time())
    {
        details = gOrders[name];

        paid = (details[0] == "regalia" ? details[9] : details[PAID_IND]);
        cost = (details[0] == "regalia" ? details[10] : details[COST_IND]);
            
        if (!can_pay(cost, this_player()))
        {
            keeper_say("All this work for nothing! Come back when you can " +
                "afford it!", this_player());
            return 1;
        }

        pay(cost, this_player());

        /* Keep track that they paid. */
        if (details[0] == "regalia")
            details[9] = 1;
        else
            details[PAID_IND] = 1;

        if (!cost && this_player()->query_prop(PLAYER_I_GM_FREEBIE))
        {
            this_player()->remove_prop(PLAYER_I_GM_FREEBIE);
            log_file("jewelry", extract(ctime(time()), 4, 15) + " " +
                capitalize(this_player()->query_real_name()) +
               " received a free regalia with the founding of an order.\n");
        }

        kind = (details[0] == "regalia" ? details[0] : details[TYPE_IND]);
        switch(kind)
        {
        case "circlet":
            txt = "I hope this circlet pleases you!";
            break;
        case "coronet":
            txt = "I'm sure this will please your Master! " +
                "Please give my regards to his ";
            if (details[ADJV_IND] == "baronial")
                txt += "lordship"; 
            else
                txt += "grace";
            break;
        case "crown":
            txt = "I'm sure this will please your Master! " +
            "Please give my regards to his ";
            if (details[ADJV_IND] == "princely")
                txt += "highness!";
            else
                txt += "majesty!";
            break;
        case "ring":
            txt = ({ "My best work yet!",
                     "What a lovely ring!",
                     "See how the light sparkles off your ring!",
                     "I must say, this is a masterpiece!" })[random(4)];
            break;
        case "necklace":
        case "choker":
        case "pendant":
        case "bracelet":
        case "anklet":
            txt = ({ "What a lovely " + details[TYPE_IND] + "!",
                     "Ahh, this is sure to grace a lovely lady.",
                     "My best work yet!",
                     "I hope you are pleased with your " + 
                         details[TYPE_IND] + "!",
                     "Fit for a goddess!" })[random(5)];
            break;
        case "torc":
        case "collar":
            txt = ({ "My best work yet!",
                     "What a lovely " + details[TYPE_IND] + "!",
                     "I must say, this is a masterpiece!",
                     "I hope you are pleased!" })[random(4)];
            break;
        case "medal":
            txt = "I hope you are pleased!";
            break;
        case "regalia":
            txt = ({ "My best work yet!", "I hope you are pleased!",
                     "I must say, this is a masterpiece!" })[random(3)];
            break;
        default:
            txt = "Something has gone wrong. Please make a bug report.";
            break;
        }

  
        if (details[0] == "regalia")
        {
            jewelry = clone_object(JEWELRY_DIR + "regalia");
            jewelry->set_owner(name);
            jewelry->set_order(details[1]);
            jewelry->set_order_rank(details[2]);
            jewelry->set_emblem(details[3]);
            jewelry->set_colour(details[4]);
            jewelry->set_gems(details[5], details[6], details[7], details[8]);
            jewelry->init_regalia();
        }
        else
        {
            jewelry = clone_object(JEWELRY_DIR + "jewelry");
            jewelry->set_desc(details[ADJV_IND]);
            jewelry->set_metal(details[METL_IND]);
            jewelry->set_gems(details[GEM1_IND], details[NUM1_IND],
                details[GEM2_IND], details[NUM2_IND]);
            jewelry->set_type(details[TYPE_IND]);
            jewelry->set_engrave(details[ENGR_IND]);
            jewelry->init_jewelry();

        }

        if (!jewelry->move(this_player()))
        {
            keeper_say(txt, this_player());
            write("You collect your " + jewelry->short() + " from " +
                gKeeper->query_the_name(this_player()) + ".\n");
            say(QCTNAME(this_player()) + " collects " + 
                this_player()->query_possessive() + " " + jewelry->short() +
                " from " + QTNAME(gKeeper) + ".\n");
            gOrders = m_delete(gOrders, name);
            log_file("jewelry",  extract(ctime(time()), 4, 15) + " " +
                capitalize(name) + " ordered a " + 
                jewelry->short() + " for " + (cost/1728) + "pc.\n");
            return 1;
        }
        else
        {
            write("You can't take your " + jewelry->short() + ".\n");
            keeper_say("I'll just keep this here. You can collect it " +
                "when you can carry it.", this_player());
            jewelry->remove_object();
            return 1;
        }
    }

    write("Your order isn't ready yet.\n");
    return 1;
}

public int
cancel(string str)
{
    int paid;
    string name;

    if (!strlen(str) || (str != "order" && str != "my order"))
    {
        notify_fail("Cancel your order?\n");
        return 0;
    }

    name = this_player()->query_real_name();

    if (member_array(name, m_indexes(gOrders)) == -1)
    {
        notify_fail("You haven't placed an order.\n");
        return 0;
    }

    paid = (gOrders[name][0] == "regalia" ? gOrders[name][9] : 
        gOrders[name][PAID_IND]);

    if (paid)
    {
        keeper_say("I'm sorry. I've already crafted your order, and " +
            "you've already paid me. Collect it from me, and you can " +
            "order something else.", this_player());
        return 1;
    }

    keeper_say("I've cancelled your order. Can I get you something else?",
        this_player());
    gKeeper->command("emote smiles hopefully.");
    present(ORDER_OBJ_ID, this_player())->remove_object();
    gOrders = m_delete(gOrders, this_player()->query_real_name());
    return 1;
}

public mixed *
query_gems_need(string name)
{
    if (member_array(name, m_indexes(gGemsNeed)) != -1)
        return gGemsNeed[name];
    else
        return ({});
}

public void
rem_gems_need(string name)
{
    gGemsNeed = m_delete(gGemsNeed, name);
}

public int
shop_hook_allow_sell(object ob)
{
    if (!ob->id(JEWELRY_ID) && !ob->id("regalia"))
    {
        notify_fail("I'm sorry, I only buy jewelry and regalia.\n");
        return 0;
    }

    return 1;
}

public void
leave_inv(object ob, object dest)
{
    object slip;

    ::leave_inv(ob, dest);

    if (!living(ob))
        return;

    slip = present(ORDER_OBJ_ID, ob);
    if (!objectp(slip))
        return;

    slip->remove_order_obj();
    return;
}

public int
do_buy(string str)
{
    notify_fail("Read the sign.\n");
    return 0;
}

public int
do_read(string str)
{
    return 0;
}

public void
init()
{
    ::init();

    init_shop();
    add_action(order, "order");
    add_action(collect, "collect");
    add_action(collect, "pay");
    add_action(cancel, "cancel");
}
