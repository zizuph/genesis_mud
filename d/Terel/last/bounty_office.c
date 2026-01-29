/*
 * Bounty hunter's office - by Udana.
 *
 * Lucius - Jan 2021
 *   Cleanups
 * 
 *  Modifications
 *    Lilith Feb 2022: added ROOM_I_INSIDE prop
 */
#include "/d/Terel/include/Terel.h"

#include <macros.h>
#include <money.h>
#include <mail.h>

#define S_MASTER        ("/secure/master")
#define PKILL_CHECKER   (LAST_DIR + "obj/pkill_checker")
#define BOUNTY_LOG      ("/d/Terel/log/bounties")
#define BOUNTIES        ("/d/Terel/last/bounties")
#define LIMIT           50

/* How much copper one pc is worth. */
#define CVP             MONEY_VALUES[MONEY_PC_INDEX]

inherit STDROOM;
inherit "/lib/trade";

public string *bNames = ({}),
              *bHunters = ({});

public mapping bDates = ([]),
               bRewards = ([]);


public void
create_terel_room()
{
    set_short("Bounty hunters office");
    set_long("A small office room in Town of Last. The only piece of furniture here "+
      "is a large desk standing in the corner. An old clerk is sitting behind it, "+
      "leaning against a wall covered with wanted posters. A large sign is hanging "+
      "on the wall, over the desk.\n");

    add_item(({"posters", "wanted posters"}), "@@posters_desc");
    add_item("desk", "Massive wooden desk, covered with some old "+
      "documents.\n");
    add_item(({"sign", "large sign"}),
        "Large sign, hanging on the wall, you can read it.\n");
    add_item(({"clerk", "old clerk"}),
        "Old clerk is sitting by the massive desk, "+
        "you can't tell if he's awake or not.\n");

    add_prop(ROOM_S_MAP_FILE, "town_last.txt");
	add_prop(ROOM_I_INSIDE, 1);
    add_exit(LAST_DIR + "lroad6", "south", 0);
    add_object(LAST_DIR + "board");

    FIX_EUID;
    config_default_trade();

    if (file_size(BOUNTIES + ".o") != -1)
        restore_object(BOUNTIES);
}

public string *
get_bounties()
{
    return m_indices(bRewards);
}

public string *
get_hunters()
{
    return bHunters + ({});
}

public string
posters_desc()
{
    string res = "Whole south wall of the office is covered "+
        "with wanted posters ";

    if (!m_sizeof(bRewards))
    {
        return res + "unfortunately all of them are quite old, "+
            "which means you'll have to find a job elsewhere.\n";
    }

    res += "few most recent ones attract your attention: \n" +
        "  WANTED : Dead or alive (better dead)\n";

    foreach(string who: sort_array(m_indices(bRewards)))
    {
        int val = bRewards[who];
        res += CAP(who) + " for a fine reward of " +
            (val > 1 ? val +" platinum coins" :
                "one platinum coin") + ".\n";
    }
    return res;
}

public int
bann_name(string a)
{
    if (!TP->query_wiz_level())
    {
        notify_fail("What?\n");
        return 0;
    }

    notify_fail("syntax: ban <player_name>\n");
    if (!strlen(a))
        return 0;

    a = lower_case(a);
    if (!S_MASTER->exist_player(a))
        return 0;

    if (member_array(a, bNames) == -1)
    {
        write(CAP(a) + " banned from using bounties.\n");
        bNames += ({ a });
    }
    else
    {
        write("Bann on " + CAP(a) + " removed.\n");
        bNames -= ({ a });
    }

    save_object(BOUNTIES);
    return 1;
}

public int
clean(string a)
{
    if (!TP->query_wiz_level())
    {
        notify_fail("What?\n");
        return 0;
    }

    notify_fail("syntax: clean <name>\n");
    if (!strlen(a))
        return 0;

    a = lower_case(a);
    if (bRewards[a] == 0)
        return 0;

    m_delkey(bRewards, a);
    save_object(BOUNTIES);

    write("Done.\n");

    m_delkey(bDates, a);
    write_file(BOUNTY_LOG, TP->query_real_name() +
        " REMOVED: name: " + a + ", reward: " + bRewards[a] +
        " | " + ctime(time()) + "\n");

    return 1;
}

public int
ask_clerk(string a)
{
    if (!strlen(a))
        return 0;

    string *s = explode(a, " ");
    if (s[0] == "clerk")
    {
        tell_room(TO, "The clerk points at the large sign.\n");
        return 1;
    }
    return 0;
}

private string
prelong_line(string line)
{
    int length = 60;
    if (strlen(line) > length)
        return "error\n";

    while(strlen(line) < length)
        line += " ";

    return "|" + line + "|\n";
}

public int
read_sign(string a)
{
    notify_fail("Read what?\n");
    if (a != "sign")
        return 0;

    write(("_" * 62) +"\n" +
        prelong_line("") +
        prelong_line("  BOUNTY HUNTERS OFFICE OF GENESIS") +
        prelong_line("") +
        prelong_line("   Here you can place and claim bounty for other") +
        prelong_line("  adventurers. To use our service do one of the following: ") +
        prelong_line("") +
        prelong_line("   place <amount> on <name>  or") +
        prelong_line("   increase bounty on <name> by <amount>") +
        prelong_line("") +
        prelong_line("  WARNING: Once the bounty is placed, there is no ") +
        prelong_line("  way to call off the hunt. So mind your decision.") +
        prelong_line("") +
        prelong_line("   Also here you can: ") +
        prelong_line("   claim bounty for <name> ") +
        prelong_line("") +
        prelong_line("  (all rewards are counted in platinum coins)") +
        prelong_line("") +
        prelong_line("  NOTE:  Mind that rules still apply to those who ") +
        prelong_line("  participate in the hunt, and using bounties for ") +
        prelong_line("  harassing others will not go unpunished.") +
        "|" + ("_" * 60) + "|\n");

    if (TP->query_wiz_level())
    {
        write(prelong_line(" clean <name> - for removing bounty.") +
            prelong_line(" ban <name> - for banning/removing bann from player.") +
            "|" + ("_" * 60) + "|\n");
    }
    return 1;
}

public int
put_bounty(string a)
{
    string name, *args;
    int reward;
    object player;

    notify_fail("What? Read the sign for detailed information.\n");
    if (!strlen(a))
        return 0;

    args = explode(a, " ");
    if (sizeof(args) != 3)
        return 0;

    if (args[1] != "for" && args[1] != "on")
        return 0;

    sscanf(args[0], "%d", reward);
    if (!reward || MAXINT / CVP < reward)
        return 0;

    name = lower_case(args[2]);
    if (!S_MASTER->exist_player(name))
    {
        notify_fail("No such player in the Realms.\n");
        return 0;
    }

    player = find_player(name);
    if (!player)
        player = S_MASTER->finger_player(name);

    if (player->query_wiz_level())
    {
        notify_fail("Yeees.. Lars, Tintin, " + CAP(name) + ", who else?\n");
        return 0;
    }

    if (bRewards[name] != 0)
    {
        notify_fail("There is already bounty on that player. "+
            "You can increase it if you want.\n");
        return 0;
    }

    if (reward < LIMIT)
    {
        notify_fail("It's not a candy shop. We're dealing with "+
            "real money here. Start with at least 50 platinum coins.\n");
        return 0;
    }

    if (member_array(TP->query_real_name(), bNames) >= 0)
    {
        notify_fail("You're banned from using this offices service. "+
            "For more information you can contact one of the Terel wizards.\n");
        return 0;
    }

    if (sizeof(pay(CVP * reward, TP, "", 0, 0, "", 1)) == 1)
    {
        notify_fail("Bring the money first\n");
        return 0;
    }

    write("You place bounty of " + (reward > 1 ? reward +
            " platinum coins on" : "one platinum coin on") +
        (name == TP->query_real_name() ? " - oddly enough - yourself" :
            " " + CAP(name)) + ".\n");
    say(QCTNAME(TP) + " hands some money to the clerk.\n");

    bRewards += ([ name : reward ]);
    bDates += ([ name : ctime(time()) ]);
    save_object(BOUNTIES);

    write_file(BOUNTY_LOG, TP->query_real_name() +
        " PLACED: name: " + name + ", reward: " + bRewards[name] +
        " | " + ctime(time()) + "\n");

    CREATE_MAIL("Reward", "hunters", name, "",
        CAP(TP->query_real_name()) + " has sponsored a bounty for your head.\n"+
        "The hunt will now begin, consider yourself warned.\n");

    return 1;
}

public int
increase_bounty(string a)
{
    string name, *args;
    int reward;

    notify_fail("What? Read the sign for detailed information.\n");
    if (!strlen(a))
        return 0;

    args = explode(a, " ");
    if (sizeof(args) != 5)
        return 0;

    if (args[0] != "bounty" && args[0] != "reward")
        return 0;

    if (args[1] != "for" && args[1] != "on")
        return 0;

    if (args[3] != "by")
        return 0;

    sscanf(args[4], "%d", reward);
    if (!reward || MAXINT / CVP < reward)
        return 0;

    if (bRewards[args[2]] == 0)
    {
        notify_fail("No bounty for that name, you can place it yourself.\n");
        return 0;
    }

    name = lower_case(args[2]);
    if (member_array(TP->query_real_name(), bNames) >= 0)
    {
        notify_fail("You're banned from using this offices service. "+
            "For more information you can contact one of the Terel wizards.\n");
        return 0;
    }

    if (sizeof(pay(CVP * reward, TP, "", 0, 0, "", 1)) == 1)
    {
        notify_fail("Bring the money first.\n");
        return 0;
    }

    if (MAXINT - (reward * CVP)  < bRewards[name] * CVP)
        bRewards[name] = MAXINT;

    write("You increase bounty for " + CAP(name) + " by " +
        (reward > 1 ? reward + " platinum coins.\n" : "one platinum coin.\n"));
    say(QCTNAME(TP) + " hands some money to the clerk.\n");

    bRewards[name] += reward;
    save_object(BOUNTIES);

    write_file(BOUNTY_LOG, TP->query_real_name() + " INCREASED: name: " + name +
        ", by: " + reward + " | " + ctime(time()) + "\n");

    return 1;
}

public int
claim_bounty(string a)
{
    string name;

    notify_fail("What? Read the sign for detailed information.\n");
    if (!strlen(a))
        return 0;

    if (!parse_command(a, ({}), " [bounty] 'for' %w ", name))
        return 0;

    name = lower_case(name);

    notify_fail("No bounty on that one.\n");
    if (!S_MASTER->exist_player(name))
        return 0;

    if (!bRewards[name])
        return 0;

    object pkill_checker = clone_object(PKILL_CHECKER);
    if (!pkill_checker->check_kill(name, TP->query_real_name(), bDates[name]))
    {
        notify_fail("Maybe kill him first? We don't pay in advance.\n");
        return 0;
    }

    MONEY_MAKE_PC(bRewards[name])->move(TP);

    write("You get your payment.\n");
    say(QCTNAME(TP) + " collects some money from the clerk.\n");

    /* For future club/guild use */
    if (member_array(TP->query_real_name(), bHunters) == -1)
        bHunters += ({ TP->query_real_name() });

#if 0
    /* Bounty Hunters increase their rank here. */
    if (TP->query_guild_member("Bounty Hunters"))
    {
        if (TP->increase_hunter_rank())
            write("Congratulations Bounty Hunter!\n");
    }
#endif

    m_delkey(bDates, name);
    m_delkey(bRewards, name);
    save_object(BOUNTIES);

    write_file(BOUNTY_LOG, TP->query_real_name() +
        " CLAIMED: name: " + name + ", reward: " +
        bRewards[name] + " | " + ctime(time()) + "\n");

    return 1;
}

public void
init()
{
    ::init();
    add_action(read_sign,       "read");
    add_action(ask_clerk,       "ask");
    add_action(put_bounty,      "place");
    add_action(increase_bounty, "increase");
    add_action(claim_bounty,    "claim");
    add_action(clean,           "clean");
    add_action(bann_name,       "ban");
}

