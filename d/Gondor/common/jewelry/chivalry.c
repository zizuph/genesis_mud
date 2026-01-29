/*
 * /d/Gondor/common/jewelry/chivalry.c
 *
 * Here is where people can found an order of knighthood.
 * 
 * Brainchild of Auberon
 * Coded by Gwyneth, 8/02
 */
inherit "/d/Gondor/std/room.c";
inherit "/lib/trade.c";
inherit "/d/Gondor/open/fireplace/fireplace";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include "/d/Gondor/open/fireplace/fireplace.h"
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <money.h>
#include "jewelry.h"

/* Ex. gOrders = ([ "Laughing Kender" : ({ "gwyneth", "laughing kender", 
                    "orange", ({ "auberon", }), ({ "alto", }), ({}) }) ])
 gOrders = ([ Order Name : ([ Founder, emblem, colour, KGCs, KCs, Members }) ])
 */
mapping gOrders = ([]);

/* This is a list of order names which are forbidden, either in advance
   or as a result of players founding inappropriate names. This will also
   serve as the way to recall any regalia sold under inappropriate names. */
string *gForbidden = ({});

/* Ex. gUnpaid = ([ "Golden Toothbrush" : ({ "gwyneth",
                    "sparkly new toothbrush", "gold" }) ])
   gUnpaid = ([ Order Name : ({ Found Name, Order Emblem, Order Colour }) ])
   This is where the Orders being constructed are held.
 */
static mapping gUnpaid = ([]);

static object gKnight, gBook;

public string view_orders();

public void
reset_room()
{
    gKnight = clone_npc(gKnight, JEWELRY_DIR + "knight");

    gKnight->command("sit in chair");

    if (!objectp(gBook))
    {
        gBook = clone_object(JEWELRY_DIR + "book");
        gBook->move(this_object());
    }

    set_wood(100);
    if (query_fire_state() != FIRE_BURNING)
    {
        tell_room(TO,
            "A squire enters the room quietly, stokes the fire and leaves " +
            "leaves almost without a sound.\n");
        set_fire_state(FIRE_BURNING);
    }
}

public string
long_desc()
{
    string str;

    if (query_fire_state() == FIRE_BURNING)
        str = "crackling fire in the fireplace sends shadows dancing " +
            "across the walls";
    else
        str = "cold fireplace seems like it might keep this room very " +
            "warm if it were lit";

    return "Heavy tapestries line the walls to keep the cold away and " +
        "to entertain. The cold brick floor is covered with plush throw " +
        "rugs and a " + str + ". A high-backed chair is placed next to " +
        "the fireplace where it is warm. Next to the chair is a small " +
        "table, just large enough to hold the leather bound book that " +
        "is attached to it. A long scroll has been posted next to the " +
        "arched doorway that leads out to the south.\n";
}

public string
fire_desc()
{
    if (query_fire_state() < FIRE_BURNING)
        return "The fire in the fireplace has grown cold since the wood " +
            "has burned down to nothing but ashes. Dark soot stains mark " +
            "the sides of the fireplace from long use.\n";
    else
        return "The fire in the fireplace crackles and radiates warmth as " +
            "the wood burns. Dark soot stains mark the sides of the " +
            "fireplace from long use.\n";
}

public string
table_desc()
{
    if (objectp(gBook))
        return gBook->long();

    return "The table seems to be missing its book!\n";
}

public void
create_gondor()
{
    set_short("room of chivalric orders");
    set_long(&long_desc());
    add_prop(ROOM_I_INSIDE, 1);

    set_fire_container("fireplace");
    set_parse_pattern("[the] [brick] 'fireplace'");
    add_item(({ "scroll", "long scroll" }), &view_orders());
    add_cmd_item(({ "scroll", "long scroll" }), "read", &view_orders());
    add_item(({ "tapestry", "tapestries" }), "Glorious scenes " +
        "depict knights in shining armour battling horrid monsters " +
        "from your worst nightmares.\n");
    add_item(({ "doorway", "arched doorway"}), "An arched doorway leads " +
        "to the jeweller's store to the south.\n");
    add_item(({ "rug", "throw rug", "rugs", "throw rugs", "plush throw rugs",
        "plush throw rug" }), "The colours of the throw rugs are subdued, " +
        "and their thickness helps keep the warmth in the room. The rugs " +
        "near the fireplace are marred slightly by a few dirty tracks.\n");
    add_item(({ "tracks", "dirty tracks" }), "They lead both up to and away " +
        "from the fireplace.\n");
    add_item(({ "table", "small table" }), &table_desc());
    add_item(({ "chair", "high-backed chair" }), "This chair has been " +
        "beautifully upholstered in red velvet. Gold ornaments decorate " +
        "the dark walnut wood of the arms and the top of the chair where " +
        "there is no velvet.\n");
    add_item(({ "velvet", "red velvet" }), "The velvet covering the chair " +
        "is a deep blood-red colour.\n");
    add_item(({ "ornament", "ornaments", "gold ornaments", "gold ornmanet",
        "patterns", "gold patterns" }), "Gold patterns have been inlaid " +
        "in the wood of the chair.\n");
    add_item(({ "fire", "fireplace", "wood", "ashes" }), &fire_desc());
    add_item(({ "soot stains", "soot" }), "The soot stains the sides of " +
        "stone fireplace black, and threaten to do the same to anything " +
        "else it comes in contact with.\n");

    add_chair("high-backed chair", "[in] 'chair'", 1, "in");
    add_exit(JEWELRY_DIR + "jewelry_store", "south");
    restore_object(MASTER);
    config_default_trade();
    reset_room();
}

public string
case_check(string order)
{
    int end, i, size;
    string *text, *exceptions = ({ "a", "and", "the", "of", "an" });

    if (!strlen(order))
        return "";

    text = explode(order, " ");

    end = sizeof(text) - 1;
    if (end >= 2 &&
      lower_case(text[0]) == "order" &&
      lower_case(text[1]) == "of")
        text = text[2..end];
    else if (end >= 3 &&
      lower_case(text[0]) == "the" &&
      lower_case(text[1]) == "order" &&
      lower_case(text[2]) == "of")
        text = text[3..end];

    for (i = 0, size = sizeof(text); i < size; i++)
    {
        if (member_array(lower_case(text[i]), exceptions) == -1)
            text[i] = capitalize(text[i]);
        else
            text[i] = lower_case(text[i]);
    }

    return (implode(text, " "));
}

public string *
query_orders()
{
    return m_indexes(gOrders);
}

public mixed *
query_order(string order)
{
    if (!strlen(order))
        return ({});

    order = case_check(order);
    return gOrders[order];
}

public int
remove_forbidden(string order)
{
    if (!this_player()->query_wiz_level())
        return 0;

    if (!strlen(order))
    {
        notify_fail("Forbid <Order Name>?\n");
        return 0;
    }

    order = case_check(order);
    gForbidden -= ({ order });
    log_file("jewelry", extract(ctime(time()), 4, 15) + " " +
        capitalize(this_player()->query_real_name()) +
        " unforbade " + order + " as an order name.\n");
    save_object(MASTER);
    return 1;
}

public int
query_forbidden(string order)
{
    if (!strlen(order))
        return 0;

    order = case_check(order);
    if (member_array(order, gForbidden) != -1)
        return 1;

    return 0;
}

public int
add_forbidden(string order)
{
    if (!this_player()->query_wiz_level())
        return 0;

    if (!strlen(order))
    {
        notify_fail("Forbid <Order Name>?\n");
        return 0;
    }

    order = case_check(order);

    if (member_array(order, query_orders()) != -1)
        gOrders = m_delete(gOrders, order);

    gForbidden += ({ order });
    log_file("jewelry", extract(ctime(time()), 4, 15) + " " +
        capitalize(this_player()->query_real_name()) +
        " forbade " + order + " as an order name.\n");
    save_object(MASTER);
    return 1;
}

public string
view_orders()
{
    int i;
    string txt, *orders = query_orders();

    if (!sizeof(orders))
        return "No orders of chivalry have been established yet.\n";

    txt = "The following orders of chivalry have been established. " +
        "More details on each of the orders can be found in the book " +
        "on the table.\n";
    for (i = sizeof(orders)-1; i >= 0; i--)
        txt += capitalize(orders[i]) + "\n";

    return txt;
}

public int
find_rank(string order, string name)
{
    int rank;

    if (!strlen(name))
        return -1;
    if (!strlen(order))
        return -1;

    name = capitalize(name);
    order = case_check(order);

    if (member_array(order, m_indexes(gOrders)) == -1)
        return -1;

    rank = member_array(name, gOrders[order][3]);
    if (rank == -1)
    {
        rank = member_array(name, gOrders[order][4]);
        if (rank == -1)
        {
            rank = member_array(name, gOrders[order][5]);
            if (rank == -1)
            {
                return -1;
            }
            else
                rank = MEMBER_RANK;
        }
        else
            rank = KC_RANK;
    }
    else
        rank = KGC_RANK;

    return rank;
}

public varargs void
info(string text, object who)
{
    if (!strlen(text))
        return;

    if (!objectp(who))
        who = this_player();

    if (!present(gKnight, this_object()))
        who->catch_tell(text + "\n");
    else
    {
        who->catch_tell(gKnight->query_The_name(who) + " says to you: " + 
            text + "\n");
        tell_room(this_object(), QCTNAME(gKnight) + " says to " + QTNAME(who) +
            ": " + text + "\n", ({ who }));
    }
    return;
}

public int
found_order(string str)
{
    if (!strlen(str))
    {
        notify_fail("Found <Order Name>.\n");
        return 0;
    }

    if ((this_player()->query_guild_style_lay() == "thief" ||
      this_player()->query_guild_style_occ() == "thief") &&
      this_player()->query_alignment() < 0)
    {
        gKnight->command("peer suspiciously at " + OB_NAME(this_player()));
        info("I'm sorry, I don't feel that I trust you enough to do " +
            "business with you for more than a few gold.\n");
        return 1;
    }

    if (this_player()->query_race_name() == "goblin")
    {
        info("That's ridiculous! Who would follow " +
            LANG_ADDART(this_player()->query_race()) + "?\n");
        return 1;
    }

    str = case_check(str);

    if (query_forbidden(str))
    {
        info("I'm sorry, but that name has been forbidden. Please " +
            "choose another.");
        return 1;
    }

    if (member_array(str, m_indexes(gOrders) + m_indexes(gUnpaid)) != -1)
    {
        info("I'm sorry. There is already an order of chivalry by that " +
            "name.");
        return 1;
    }

    gUnpaid += ([ str : ({ capitalize(this_player()->query_real_name()), 
        "", "" }) ]);
    info("You have chosen to found the Order of " + str + ".");
    info("You may now 'select emblem <emblem> for " + str + "'. This can be " +
        "something along the lines of \"a golden dragon\" or " +
        "\"St. George slaying the dragon\". Also, 'select colour <colour> " +
        "for " + str + "'. This can be anything from \"red\" to \"pure " +
        "white\". To complete the founding, you must 'pay for " + str + 
        "' (" + MONEY_TEXT_SPLIT(FOUND_COST) + ").");
    return 1;
}

public int
select(string str)
{
    string option, selection, order;

    if (!strlen(str))
    {
        notify_fail("Select <emblem/colour> <choice> for <order name>.\n");
        return 0;
    }

    if (!parse_command(str, ({}), "%w %s 'for' %s", option, selection, order))
    {
        notify_fail("Select <emblem/colour> <choice> for <order name>.\n");
        return 0;
    }

    order = case_check(order);

    if (member_array(order, m_indexes(gOrders)) != -1)
    {
        info("I'm sorry. This order is already established.\n");
        return 1;
    }

    if (member_array(order, m_indexes(gUnpaid)) == -1)
    {
        info("I'm sorry. You have not founded the Order of " + order + ".");
        return 1;
    }

    if (gUnpaid[order][0] != capitalize(this_player()->query_real_name()))
    {
        info("You aren't the founding member!");
        return 1;
    }

    if (option == "emblem")
    {
        gUnpaid[order][1] = selection;
        info("You have selected " + selection + " for the emblem of the " +
            "Order of " + order + ". You may change it again, but only " +
            "before you have paid me.");
        return 1;
    }

    if (option == "colour" || option == "color")
    {
        gUnpaid[order][2] = selection;
        info("You have selected " + selection + " for the colour of the " +
            "Order of " + order + ". You may change it again, but only " +
            "before you have paid me.");
        return 1;
    }

    notify_fail("Select <emblem/colour> <choice> for <order name>.\n");
    return 0;
}

public int
pay_for(string str)
{
    string order;

    if (!strlen(str))
    {
        notify_fail("Pay for <Order Name>?\n");
        return 0;
    }

    if (!parse_command(str, ({}), "'for' %s", order))
    {
        notify_fail("Pay for <Order Name>?\n");
        return 0;
    }

    order = case_check(order);

    if (member_array(order, m_indexes(gOrders)) != -1)
    {
        info("The Order of " + order + " has already been paid for.");
        return 1;
    }

    if (member_array(order, m_indexes(gUnpaid)) == -1)
    {
        info("There is no such Order! If you would like to create the " +
            "Order of " + order + ", you may 'found " + order + ".");
        return 1;
    }

    if (capitalize(this_player()->query_real_name()) != gUnpaid[order][0])
    {
        info("The Order of " + order + " is not one that you have founded.");
        return 1;
    }

    if (!strlen(gUnpaid[order][1]) || !strlen(gUnpaid[order][2]))
    {
        info("You haven't finished the selection process yet.");
        return 1;
    }

    if (!can_pay(FOUND_COST, this_player()))
    {
        info("Come back when you can pay!");
        return 1;
    }

    pay(FOUND_COST);
    write("You pay " + MONEY_TEXT_SPLIT(FOUND_COST) + ".\n");

    log_file("jewelry", extract(ctime(time()), 4, 15) + " " +
        capitalize(this_player()->query_real_name()) +
        " founded the Order of " + order + " with emblem " +
        gUnpaid[order][1] + " and colour " + gUnpaid[order][2] + ".\n");

    this_player()->add_prop(PLAYER_I_GM_FREEBIE, 1);

    gOrders += ([ order : gUnpaid[order] + 
        ({ ({ capitalize(this_player()->query_real_name()) }) }) + 
        ({ ({ }) }) + ({ ({ }) }) ]);
    gUnpaid = m_delete(gUnpaid, order);
    save_object(MASTER);
    info("Congratulations! You are the new Grandmaster of the Order of " +
        order + "! You may pick up your regalia next door at the jewelry " +
        "shop for free when you 'order regalia'.");
    return 1;
}

public int
admit(string str)
{
    string name, who, rank, order;

    if (!strlen(str))
    {
        notify_fail("Admit <who> as a <m/kc/kgc> to <Order Name>?\n");
        return 0;
    }

    if (!parse_command(str, ({}), "%w 'as' 'a' %w 'to' %s", who, rank, order))
    {
        notify_fail("Admit <who> as a <m/kc/kgc> to <Order Name>?\n");
        return 0;
    }

    name = capitalize(this_player()->query_real_name());
    who = capitalize(who);
    rank = lower_case(rank);
    order = case_check(order);

    if (member_array(order, m_indexes(gOrders)) == -1)
    {
        info("The Order of " + order + " does not exist.");
        return 1;
    }

    if (find_rank(order, who) != -1)
    {
        info(who + " is already a member of the Order of " + order + ".");
        return 1;
    }
    
    if (name != gOrders[order][0] && !this_player()->query_wiz_level())
    {
        info("You are not the Grandmaster of the Order of " + order + ".");
        return 1;
    }

    if (!SECURITY->exist_player(who))
    {
        info("I'm sorry, I don't think I know " + LANG_ADDART(who) + 
            ". Perhaps you meant a different name?");
        return 1;
    }

    
    switch(rank)
    {
    case "m":
        rank = "Member";
        gOrders[order][5] += ({ who });
        break;
    case "kc":
        rank = "Knight Commander";
        gOrders[order][4] += ({ who });
        break;
    case "kgc":
        rank = "Knight Grand Cross";
        gOrders[order][3] += ({ who });
        break;
    default:
        info("What rank is that? Please use the abbreviations: 'm', 'kc' " +
            "and 'kgc' for \"Member\", \"Knight Commander\" and \"Knight " +
            "Grand Cross\".\n");
        return 1;
    }

    save_object(MASTER);
    log_file("jewelry", extract(ctime(time()), 4, 15) + " " +
        capitalize(this_player()->query_real_name()) +
        " admitted " + who + " as a " + rank + " of the Order of " +
        order + ".\n");
    info(who + " has been admitted as a " + rank + " of the " +
        "Order of " + order + "!");
    return 1;
}

public int
expel(string str)
{
    int rank;
    string who, order;

    if (!strlen(str))
    {
        notify_fail("Expel <who/myself> from <Order Name>?\n");
        return 0;
    }

    if (!parse_command(str, ({}), "%w 'from' %s", who, order))
    {
        notify_fail("Expel <who/myself> from <Order Name>?\n");
        return 0;
    }

    order = case_check(order);

    if (member_array(order, m_indexes(gOrders)) == -1)
    {
        info("There is no such order, " + order + ".");
        return 1;
    }

    if (who == "myself")
    {
        who = capitalize(this_player()->query_real_name());
        rank = find_rank(order, who);
        if (rank == -1)
        {
            info("Perhaps you would like to expel yourself from an " +
                "order that you actually belong to.");
            return 1;
        }

        info("Very well, " + who + ". You are no longer a member of " +
            "the Order of " + order + ".");
        gOrders[order][5 - rank] -= ({ who });
        log_file("jewelry", extract(ctime(time()), 4, 15) + " " +
            capitalize(this_player()->query_real_name()) +
            " expelled self from the Order of " + order + ".\n");
        save_object(MASTER);
        return 1;
    }

    if (capitalize(this_player()->query_real_name()) != gOrders[order][0])
    {
        info("You cannot expel anyone from the Order of " + order + ", as " +
            "you are not the Grandmaster.");
        return 1;
    }

    who = capitalize(who);

    if (who == capitalize(this_player()->query_real_name()))
    {
        info("Expel yourself? If you don't want to be the Grandmaster " +
            "anymore, you must pass the office on to someone else.");
        return 1;
    }

    rank = find_rank(order, who);
    if (rank == -1)
    {
        info("You cannot expel a non-member.");
        return 1;
    }

    gOrders[order][5 - rank] -= ({ who });
    save_object(MASTER);
    log_file("jewelry", extract(ctime(time()), 4, 15) + " " +
        capitalize(this_player()->query_real_name()) +
        " expelled " + who + " from the Order of " + order + ".\n");
    info(who + " has been expelled from the Order of " + order + ".");
    return 1;
}

public int
demote(string str)
{
    int current_rank;
    string who, order, rank;

    if (!strlen(str))
    {
        notify_fail("Demote <who> to <m/kc> in <Order Name>?\n");
        return 0;
    }

    if (!parse_command(str, ({}), "%w 'to' %w 'in' %s", who, rank, order))
    {
        notify_fail("Demote <who> to <m/kc> in <Order Name>?\n");
        return 0;
    }

    order = case_check(order);

    if (member_array(order, m_indexes(gOrders)) == -1)
    {
        info("There is no such order, " + order + ".");
        return 1;
    }

    if (capitalize(this_player()->query_real_name()) != gOrders[order][0])
    {
        info("You cannot demote anyone in the Order of " + order + ", as " +
            "you are not the Grandmaster.");
        return 1;
    }

    who = capitalize(who);
    if (who == capitalize(this_player()->query_real_name()))
    {
        info("Demote yourself? If you don't want to be the Grandmaster " +
            "anymore, you must pass the office on to someone else.");
        return 1;
    }

    current_rank = find_rank(order, who);
    if (current_rank == -1)
    {
        info("You cannot demote a non-member.");
        return 1;
    }

    if (rank == "kc" && current_rank == KGC_RANK)
        gOrders[order][4] += ({ who });
    else if (rank == "m" && 
      (current_rank == KGC_RANK || current_rank == KC_RANK))
        gOrders[order][5] += ({ who });
    else
    {
        info(who + " cannot be demoted to that level.");
        return 1;
    }

    gOrders[order][5 - current_rank] -= ({ who });
    save_object(MASTER);
    log_file("jewelry", extract(ctime(time()), 4, 15) + " " +
        capitalize(this_player()->query_real_name()) +
        " demoted " + who + " to " + 
        (rank == "kc" ? "Knight Commander" : "Member") + 
        " of the Order of " + order + ".\n");
    info(who + " has been demoted to " + (rank == "kc" ? "Knight Commander" :
        "Member") + " of the Order of " + order + ".");
    return 1;
}

public int
promote(string str)
{
    int current_rank;
    string who, rank, order;

    if (!strlen(str))
    {
        notify_fail("Promote who to <kc/kgc> in <Order Name>?\n");
        return 0;
    }

    if (!parse_command(str, ({}), "%w 'to' %w 'in' %s", who, rank, order))
    {
        notify_fail("Promote who to <kc/kgc> in <Order Name>?\n");
        return 0;
    }

    order = case_check(order);

    if (member_array(order, m_indexes(gOrders)) == -1)
    {
        info("There is no such order, " + order + ".");
        return 1;
    }

    if (capitalize(this_player()->query_real_name()) != gOrders[order][0])
    {
        info("You cannot promote anyone in the Order of " + order + ", as " +
            "you are not the Grandmaster.");
        return 1;
    }

    rank = lower_case(rank);
    who = capitalize(who);
    current_rank = find_rank(order, who);
    if (current_rank == -1)
    {
        info(who + " must be admitted to the Order of " + order + " first.");
        return 1;
    }

    if (rank == "kc")
    {
        if (current_rank == MEMBER_RANK)
        {
            gOrders[order][5] -= ({ who });
            gOrders[order][4] += ({ who });
            log_file("jewelry", extract(ctime(time()), 4, 15) + " " +
                capitalize(this_player()->query_real_name()) +
                " promoted " + who + " to Knight Commander of the Order " +
                " of " + order + ".\n");
            save_object(MASTER);
            info(who + " is now promoted to Knight Commander of the Order " +
                "of " + order + "!");
        }
        else if (current_rank == KC_RANK)
            info(who + " is already a Knight Commander of the Order of " +
                order + ".");
        else
            info(who + " is a Knight Grand Cross of the Order of " + order +
                ". You may expel him or demote him, but " + who + " can " +
                "not be promoted anymore.");

        return 1;
    }

    if (rank == "kgc")
    {
        if (current_rank == MEMBER_RANK)
            gOrders[order][5] -= ({ who });
        else if (current_rank == KC_RANK)
            gOrders[order][4] -= ({ who });
        else
        {
            info(who + " is already a Knight Grand Cross of the Order of " +
                order + ".");
            return 1;
        }

        info(who + " is now promoted to Knight Grand Cross of the Order " +
            "of " + order + "!");
        log_file("jewelry", extract(ctime(time()), 4, 15) + " " +
            capitalize(this_player()->query_real_name()) +
            " promoted " + who + " to Knight Grand Cross of the Order " +
            " of " + order + ".\n");
        gOrders[order][3] += ({ who });
        save_object(MASTER);
        return 1;
    }

    info("I don't understand. What rank did you which to promote " + who +
        " to? Use the abbreviations kc or kgc.");
    return 1;
}

public int
pass(string str)
{
    string name, who, order;

    if (!strlen(str))
    {
        notify_fail("Pass Grandmaster of <Order Name> to who?\n");
        return 0;
    }

    if (!parse_command(str, ({}),
      "'grandmaster' / 'Grandmaster' 'of' %s 'to' %w", order, who))
    {
        notify_fail("Pass Grandmaster of <Order Name> to who?\n");
        return 0;
    }

    order = case_check(order);

    if (member_array(order, m_indexes(gOrders)) == -1)
    {
        info("The Order of " + order + " does not exist.\n");
        return 1;
    }

    who = capitalize(who);
    name = capitalize(this_player()->query_real_name());

    if (gOrders[order][0] != name)
    {
        info("But you are not the Grandmaster of the Order of " + order + "!");
        return 1;
    }

    if (!SECURITY->exist_player(lower_case(who)))
    {
        info("I'm sorry, I don't think I know " + LANG_ADDART(who) + ".");
        return 1;
    }

    if (who == name)
    {
        info("I'm puzzled, what did you want me to do?");
        return 1;
    }

    if (find_rank(order, who) != KGC_RANK)
    {
        info("You can only pass the office on to a Knight Grand Cross of " +
            "the Order of " + order + ".");
        return 1;
    }

    gOrders[order][0] = who;
    save_object(MASTER);
    log_file("jewelry", extract(ctime(time()), 4, 15) + " " +
        capitalize(this_player()->query_real_name()) +
        " passed the office of Grandmaster of the Order of " + order +
        " to " + name + ".\n");
    info(who + " is now the Grandmaster of the Order of " + order + "!" +
        " Enjoy your retirement, " + name + ".");
    gKnight->command("bow solemnly");
    return 1;
}

public int
enter_fire(string str)
{
    int hp, i, size;
    object *team;

    if (!strlen(str))
    {
        notify_fail("Enter what?\n");
        return 0;
    }

    if (str != "fire" && str != "fireplace")
    {
        notify_fail("Enter what?\n");
        return 0;
    }

    if (query_fire_state() == FIRE_BURNING)
    {
        write("You set your foot into the burning fire, and quickly " +
            "withdraw it. Ouch!\n");
        hp = this_player()->query_hp();
        this_player()->set_hp(hp - 100);
        return 1;
    }
    else
    {
        write("You enter the sooty fireplace.\n");
        say(QCTNAME(this_player()) + " enters the sooty fireplace.\n");
        tell_room(JEWELRY_DIR + "fireplace", QCTNAME(this_player()) +
            " enters the fireplace.\n");
        this_player()->move_living("M", JEWELRY_DIR + "fireplace", 1, 0);
        team = this_player()->query_team();
        if (!sizeof(team))
            return 1;

        for (i = 0, size = sizeof(team); i < size; i++)
        {
            if (present(team[i], this_object()))
            {
                team[i]->catch_tell("You follow " +
                    this_player()->query_the_name(team[i]) + " into the " +
                    "fireplace.\n");
                tell_room(JEWELRY_DIR + "fireplace", QCTNAME(team[i]) +
                    " enters the fireplace.\n");
                team[i]->move_living("M", JEWELRY_DIR + "fireplace", 1, 0);
                tell_room(this_object(), QCTNAME(team[i]) + " follows " +
                    QTNAME(this_player()) + " into the fireplace.\n");
            }
        }

        return 1;
    }
}

public void
extinguish_fire()
{
    set_fire_state(FIRE_UNLIT_WOOD);
    tell_room(this_object(), "The fire goes out with a sharp hiss.\n");
}

public void
init()
{
    ::init();

    add_action(found_order, "found");
    add_action(select, "select");
    add_action(pay_for, "pay");
    add_action(admit, "admit");
    add_action(expel, "expel");
    add_action(promote, "promote");
    add_action(demote, "demote");
    add_action(pass, "pass");
    add_action(add_forbidden, "forbid");
    add_action(remove_forbidden, "unforbid");
    add_action(enter_fire, "enter");
    init_room_chairs();
    init_fire();
}

public void
leave_inv(object ob, object to)
{
    object book;

    ::leave_inv(ob, to);

    if (!living(ob))
        return;

    book = present("_chivalric_order_book_", ob);
    if (objectp(book))
    {
        book->move(present("_chivalric_order_table_", this_object()));
        ob->catch_tell("You put the book back on the table as you leave.\n");
        return;
    }
}
