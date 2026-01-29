inherit "/std/room";
inherit "/d/Emerald/lib/coin_parser";

#include "../guild.h"
#include <money.h>

public int open = 0;

public void
create_landing_room()
{
}

nomask void
create_room()
{
    string sign, *dests, name;

    setuid();
    seteuid(getuid());

    name = EAGLE_MANAGER->query_destination_name(file_name(this_object()));

    set_short("Giant eagle landing" +
        (name ? " (" + capitalize(name) + ")" : ""));

    set_long("A large, wooden platform where giant eagles land " +
        "periodically to transport travellers to various points " +
        "around the lands of Emerald.  A horn is attached to a " +
        "large post with a small sign next to it.\n");

    create_landing_room();

    dests = (string *)EAGLE_MANAGER->query_open_destination_names() -  
            ({ name });

    if (!sizeof(dests))
    {
        sign = "The giant eagle transport has gone bankrupt and will " +
               "reopen as soon as sufficient funds are raised.\n";
    }
    else if (!name || !EAGLE_MANAGER->query_open_destination(name))
    {
        sign = "This landing is curently out of service.\n";
    }
    else
    {
        open = 1;
  	sign = "Transportation for Keepers of Telberin and guests of " +
    	       "the royal family only!\n\n" +
               sprintf("%|50s\n%-#50s\n\n", "Current destinations",
               implode(map(dests, capitalize), "\n"));
    }

#ifdef DONATIONS_REQUIRED
    sign += "Donations appreciated, simply \"donate <amount>\".\n";
#endif

    add_item(({ "sign", "small sign" }), sign);
    add_cmd_item(({ "sign", "small sign" }), "read", sign);

    clone_object(KOT_EAGLE_DIR + "horn")->move(this_object(), 1);
}

#ifdef DONATIONS_REQUIRED
public int
donate(string str)
{
    int *coins, amnt;

    if (!strlen(str) || !(coins = parse_coins(str, this_player())))
    {
        notify_fail(capitalize(query_verb()) + " how much?\n");
        return 0;
    }

    if (member_array(-1, coins) >= 0)
    {
        write("You don't have that much to donate!\n");
        return 1;
    }

    amnt = MONEY_MERGE(coins);

    MONEY_ADD(this_player(), -amnt);

    setuid();
    seteuid(getuid());
    EAGLE_MANAGER->add_donation(amnt);

    write("Thank you for your generous donation!\n");

    return 1;
}

void
init()
{
    ::init();
    add_action(donate, "donate");
}
#endif

public int
query_landing_open()
{
    return open;
}
