#include "/d/Shire/sys/defs.h"
#include "hobbit.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include <std.h>

inherit "/lib/trade";
inherit SHIRE_ROOM;

#define PARTY_PRICE   25
#define FREE_FOOD     20
#define COSTUMES       5
#define PARTY_MASTER  ("/d/Shire/party/master")
#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

#define CHECK_HOBBIT { if (!present(gHobbit, TO)) return 0; }
#define CHECK_PLAYER { if (objectp(gBuyer) && TP != gBuyer) return 0; }

// Global Vars
int gPrice, gStage, gAlarm;
object gBuyer, gHobbit;

void
create_room()
{
   add_prop(ROOM_S_MAP_FILE, "michel_delving.txt");

    set_short("A small quiet alcove");
    set_long("This small alcove is quite bare, with the exceptions "+
      "for a few noticeable items. A small brass bell sits on a nearby "+
      "ledge of a window, under which hangs a sign. Only way out of here "+
      "is to go back from where you came.\n");

    add_item("window","A small steamed up window.\n");
    add_item("bell","A nice brightly polished bell, which you can ring.\n");
    add_item("sign", "Maybe you should read it?\n");
    add_cmd_item("sign","read","The sign reads:  If you wish to order a "+
      "party, please ring the bell for service.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK, 1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);

    config_default_trade();  /* Set up the trading system */

    add_exit(HOBGLD_DIR + "entrance", "east", 0, 1);
}

void
remove_hobbit()
{
    if (objectp(gBuyer))
	return;

    tell_room(TO, QCTNAME(gHobbit) + " makes "+HIS_HER(gHobbit)+
      " way behind the window.\n");
    gHobbit->remove_object();
    remove_alarm(gAlarm);
    gAlarm = 0;
}

void
reset_buying(int flag)
{
    if (flag)
	PARTY_MASTER->reset_party();
    gBuyer = 0;
    gPrice = 0;
    gStage = 0;
    if (!gAlarm && objectp(gHobbit))
	gAlarm = set_alarm(30.0, 60.0, remove_hobbit);
}

varargs string *
valid_players(string str, int flag)
{
    string *parts = explode(str, " "), *names = ({});
    int i = -1;

    while (++i < sizeof(parts))
    {
	if (SECURITY->exist_player(parts[i]))
	    names += ({ parts[i] });
	else if (flag)
	    if (PARTY_MASTER->valid_guild_short(parts[i]))
		names += ({ parts[i] });
    }
    return names;
}

int
buy_party(string str)
{
    CHECK_HOBBIT;
    CHECK_PLAYER;
    if (str != "party")
    {
        NF("Order what? A party perhaps?\n");
        return 0;
    }

    if (PARTY_MASTER->query_is_party())
    {
        gHobbit->command("say I'm sorry, but there is already a party going on.");
        return 1;
    }

    gBuyer = this_player();
    gStage += 1;
    gPrice = PARTY_PRICE;
    PARTY_MASTER->add_host(gBuyer->query_real_name());
    gHobbit->command("say So, you want to purchase a party? Well, a simple " +
        "party costs " + PARTY_PRICE + " platinum. Since you are " +
        "the one paying for this party, you automatically become the " +
        "party host.");
    gHobbit->command("say Do you want other players as co-hosts? " +
        "If you do, do:\n" +
        ">  \"host <name1> <name2> .. <nameN>\"\n\n" +
        "or, if you are the only host, do:\n" +
        ">  \"host none\"");
    return 1;
}

int
add_hosts(string str)
{
    string *hosts;

    CHECK_HOBBIT;
    CHECK_PLAYER;
    if (gStage != 1)
    {
        NF("It isn't the correct time to add another host.\n");
        return 0;
    }

    if (!str || !strlen(str))
    {
        NF("Add whom as a host?\n");
        return 0;
    }

    if (str != "none")
    {
    	if (!sizeof(hosts = valid_players(str)))
	    {
            gHobbit->command("say I'm sorry, but I couldn't find the " +
                "player named " + str + ".");
            gHobbit->command("say Please try again.");
            return 1;
	    }

    	PARTY_MASTER->add_host(hosts);
    }

    gStage += 1;
    gHobbit->command("say Ok, is this party for anyone in particular? " +
        "To add honoured guests, do:\n" +
        ">  \"for <name1> <name2> .. <nameN>\"\n\n"+
        "or, if this party isn't for anyone, do:\n" +
        ">  \"for none\"");
    return 1;
}

int
set_for_who(string str)
{
    string *guests;

    CHECK_HOBBIT;
    CHECK_PLAYER;
    if (gStage != 2)
    {
        NF("It isn't the correct time to add guests of honour.\n");
        return 0;
    }

    if (!str || !strlen(str))
    {
        NF("Who do you want to add as a guest of honour?\n");
        return 0;
    }

    if (str != "none")
    {
    	if (!sizeof(guests = valid_players(str)))
	    {
	        gHobbit->command("say I'm sorry, but I couldn't find a player " +
                "named " + str + ".");
	        gHobbit->command("say Please try again.");
	        return 1;
	    }
    	PARTY_MASTER->add_guest_of_honour(guests);
    }

    gStage += 1;
    gHobbit->command("say Is this party to celebrate a birthday, marriage, " +
        "a special occasion, or something else? Please keep in mind " +
        "the invitations will be printed in this following format:\n\n" +
        "You have been invited to " +
            LANG_POSS(PARTY_MASTER->query_hosts())+" party to celebrate " +
            (stringp(str = PARTY_MASTER->query_for_whom()) ? LANG_POSS(str) +
                " " :"") + "<text>.");
    gHobbit->command("say Please state the reason for this party by "+
        "typing:\n" +
        ">  \"reason <text>\"\n");

    return 1;
}

int
set_reason(string str)
{
    CHECK_HOBBIT;
    CHECK_PLAYER;
    if (gStage != 3)
    {
    	NF("It isn't the correct time to give a reason for the party.");
	    return 0;
    }

    if (!str || !strlen(str))
    {
    	NF("Come on, you got to have a reason to hold this party.\n");
	    return 0;
    }

    PARTY_MASTER->set_reason(str);
    gStage += 1;
    gHobbit->command("say Ok, who are you inviting to this grand party "+
        "of yours? To add players as guests to this party, do:\n" +
        ">  \"guests <name1> <name2> .. <nameN>\"\n\n" +
        "To invite everyone, do:\n" +
        ">  \"invite all\"\n\n" +
        "or you may invite whole guilds if you wish.");
    gHobbit->command("say For a listing of guilds, do:\n" +
         ">  \"list guilds\"\n\n");
    return 1;
}

int
set_guests(string str)
{
    string *guests;

    CHECK_HOBBIT;
    CHECK_PLAYER;
    if (gStage != 4)
    {
	    NF("It isn't the correct time to add guests.\n");
	    return 0;
    }

    if (!str || !strlen(str))
    {
        NF("Who do you want to invite as guests?\n");
        return 0;
    }

    if (str != "all" && str != "wizards")
    {
    	if (!sizeof(guests = valid_players(str, 1)))
	    {
	        gHobbit->command("say I'm sorry, but I couldn't find anyone " +
                "by that name or a guild named " + str + ".");
	        gHobbit->command("say Please try again.");
	        return 1;
	    }
    }
    else
    {
        guests = ({ str });
        PARTY_MASTER->add_guest(guests);
        gStage += 1;
        gHobbit->command("say Now, do you wish to pick up the tab for " +
            "all the food and drinks at the party? The charge will be " + 
            FREE_FOOD + " platinum. Do:\n" +
            ">  \"food yes\"\n\n" + 
            "or if you want your guests to pay for their food and " +
            "drinks, do:\n" +
            ">  \"food no\"\n");
        return 1;
    }
}

int
set_food(string str)
{
    CHECK_HOBBIT;
    CHECK_PLAYER;
    if (gStage != 5)
    {
	NF("It isn't the correct time to decide on the food.\n");
	return 0;
    }
    switch(str)
    {
    case "yes": case "y":
	PARTY_MASTER->set_free_food();
	gPrice += FREE_FOOD;
	break;
    case "no": case "n":
	break;
    default:
	gHobbit->command("say You must reply with either yes or no.");
	return 1;
    }
    gStage += 1;
    gHobbit->command("say For a small fee of " + COSTUMES + " platinum coins, you "+
      "may have costumes at the party. They are useful if you want to have a costume "+
      "ball, celebrate All Hallows' Eve, or some other festive event.");
    gHobbit->command("say If you want to pay the fee for costumes, do:\n" +
        ">  \"costumes yes\"\n\n" +
        "If you don't want costumes, do:\n" +
        ">  \"costumes no\"\n\n");
    return 1;
}

int
set_costumes(string str)
{
    CHECK_HOBBIT;
    CHECK_PLAYER;
    if (gStage != 6)
    {
	NF("It isn't the correct time to decide on the costumes.\n");
	return 0;
    }
    switch(str)
    {
    case "yes": case "y":
	PARTY_MASTER->set_costumes();
	gPrice += COSTUMES;
	break;
    case "no": case "n":
	break;
    default:
	gHobbit->command("say You must reply with either yes or no.");
	return 1;
    }
    gStage += 1;
    gHobbit->command("say There, your party is set up and ready to go.");
    gHobbit->command("say The fee for this party will be " + gPrice +
      " platinum coins.");
    gHobbit->command("say If you find this acceptable, do:\n" +
        ">  \"accept party\"\n\n"+
        "if you have changed your mind, or want to cancel, or start over, do:\n" +
        ">  \"cancel party\"\n\n");
    return 1;
}

int
pay_for_party(string str)
{
    int *money_arr, price;
    string coin_get_text, coin_pay_text;

    CHECK_HOBBIT;
    CHECK_PLAYER;
    if (gStage != 7)
    {
	NF("But you haven't finished setting up the party yet!\n");
	return 0;
    }
    if (str != "party")
    {
	NF("Accept what? The party maybe?\n");
	return 0;
    }
    // Check if the party is set and ready to go.
    if (!PARTY_MASTER->check_party_ready())
    {
	gHobbit->command("say Hmmm for some reason the party isn't set up right.\n" +
        "Please try again, and if the problem continues, leave a bug report.");
	reset_buying(1);
	return 1;
    }
    //  Make them pay
    if (TP->query_wiz_level())
    {
	gHobbit->command("say Since you are a wizard, the party will not cost you anything, but you best have a good reason for throwing it.");
    }
    else
    {
	price = gPrice * 12 * 12 * 12;
	if (sizeof(money_arr = pay(price)) == 1)
	{
	    gHobbit->command("say But you don't have the nessacery funds to pay for the party!\n");
	    return 1;
	}
	coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
	coin_get_text = text(exclude_array(money_arr, 0, NUM-1));
	write("You pay " + coin_pay_text + " for your party, which starts immediately.\n");
	say(QCTNAME(TP) + " pays for a party.\n");
	if (coin_get_text)
	    write("You get " + coin_get_text + " back.\n");
    }
    PARTY_MASTER->start_party();
    reset_buying(0);
    return 1;
}

int
cancel_party(string str)
{
    CHECK_HOBBIT;
    CHECK_PLAYER;
    if (str != "party")
    {
	NF("Cancel what? The party?\n");
	return 0;
    }
    gHobbit->command("say Ok, canceling your order for a party.");
    reset_buying(1);
    return 1;
}

int
list_guilds(string str)
{
    mapping guilds;
    string *indices;
    int i = -1;

    if (str != "guilds")
    {
	NF("List what? Guilds maybe?\n");
	return 0;
    }
    guilds = PARTY_MASTER->query_guilds();
    indices = m_indexes(guilds);
    indices = sort_array(indices);
    write("Guild Short Name     Guild Name.\n" +
    "--------------------------------------------------------------------------\n");
    while (++i < sizeof(indices))
    {
	write(sprintf("%-20s", indices[i])+" " + guilds[indices[i]][0] + ".\n");
    }
    return 1;
}

int
ring_bell(string str)
{
    if (str != "bell")
    {
	NF("Ring what? The bell maybe?\n");
	return 0;
    }
    write("Ring!\n\nRing!\n\n");
    say(QCTNAME(TP) + " rings the bell.\n");
    if (!objectp(gHobbit))
    {
	setuid(); seteuid(getuid());
	gHobbit = clone_object(HOBGLD_DIR + "party_hobbit");
    }
    if (!present(gHobbit, TO))
    {
	gHobbit->move_living("void", TO, 1, 1);
	gHobbit->command("say Hullo there, how can I help you?");
	gHobbit->command("think");
	gHobbit->command("say You interested in ordering a party? If you are, " +
        "do:\n" +
        ">  \"order party\"");
    }
    else
    {
	gHobbit->command("say Yes yes, I am here already no need to "+
	  "ring that silly bell anymore!");
	gHobbit->command("peer suspiciously at "+TP->query_real_name());
    }
    if (!gAlarm)
	gAlarm = set_alarm(300.0, 30.0, remove_hobbit);
    return 1;
}

void
init()
{
    ::init();
    add_action(buy_party,     "buy");
    add_action(buy_party,     "order");
    add_action(add_hosts,     "host");
    add_action(add_hosts,     "hosts");
    add_action(set_for_who,   "for");
    add_action(set_reason,    "reason");
    add_action(set_guests,    "guests");
    add_action(set_guests,    "guest");
    add_action(set_food,      "food");
    add_action(set_costumes,  "costumes");
    add_action(pay_for_party, "accept");
    add_action(cancel_party,  "cancel");
    add_action(list_guilds,   "list");
    add_action(ring_bell,     "ring");
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob,to);
    if (ob == gBuyer)
	reset_buying(1);
}
