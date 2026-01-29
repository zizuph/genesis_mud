inherit "/d/Emerald/std/elf";

#include "../defs.h"
#include <language.h>
#include <cmdparse.h>

public string report_ship(string line);
public void add_shipline_ask(string line);

void
create_elf()
{
    set_name(({ "agent", "ticketing agent" }));
    set_adj("ticketing");

    set_short("ticketing agent");

    set_stats(({ 20, 20, 20, 70, 50, 50 }));

    add_shipline_ask(TELBERIN_LINE);
    add_shipline_ask(SPARKLE_LINE);
    add_shipline_ask(TEREL_LINE);
    add_shipline_ask(AVENIR_LINE);
    add_shipline_ask(GOLDEN_ISLAND_LINE);
    add_shipline_ask(FAERIE_LINE);

    setuid();
    seteuid(getuid());

    SHIP_MGR->register(this_object());
}

public void
add_shipline_ask(string line)
{
    string lcline = implode(map(explode(line, ""), lower_case), "");
    add_ask(({ lcline + " ship", "about " + lcline + " ship",
        "about the " + lcline + " ship", "faerie " + lcline,
        "about " + lcline + " line", "about the " + lcline + " line",
        "ship to " + lcline, "about ship to " + lcline,
        "about the ship to " + lcline, }), &report_ship(line));
}
    
public void
ship_docked(string line)
{
    if (line == GOLDEN_ISLAND_LINE)
    {
        // Not enough passengers to bother announcing this ship
	return;
    }

    command("emote announces: \"The " + line + " ship has just docked\".");
}

public void
ship_undocked(string line)
{
    if (line == GOLDEN_ISLAND_LINE)
    {
        // Not enough passengers to bother announcing this ship
	return;
    }

    command("emote announces: \"The " + line + " ship has just left the dock\".");
}

public string
report_ship(string line)
{
    int sstatus = SHIP_MGR->query_ship_status(line);

    if (sstatus == STATUS_DOCKED)
    {
        return "Docked\n";
    }
    
    if (sstatus == STATUS_UNDOCKED)
    {
        return "Undocked\n";
    }

    if (sstatus == STATUS_UNKNOWN)
    {
        return "Unknown\n";
    }

    return "blah";
}
        
public int
buy_tickets(string str)
{
    string what, line, from, pre, *lines;
    int num, i, price = -1;
    mixed *oblist;

    if (!strlen(str))
    {
        notify_fail("Buy what?\n");
        return 0;
    }

    if (sscanf(str, "%s for %s from %s", what, line, from) != 3)
    {
        if (sscanf(str, "%s from %s for %s", what, from, line) != 3)
        {
            if (sscanf(str, "%s for %s", what, line) != 2)
            {
                if (sscanf(str, "%s from %s", what, from) != 2)
                {
                    what = str;
                    from = line = "";
                }
                else
                {
                    line = "";
                }
            }
	    else
	    {
		from = "";
	    }
        }
    }               

    write(what + "\n");
    if (parse_command(what, ({}), "[ship] / [boat] / [ferry] 'ticket' / 'tickets'"))
    {
        num = 1;
    }
    else if (parse_command(what, ({}),
         "%w [ship] / [boat] / [ferry] 'ticket' / 'tickets'", pre))
    {
        if (pre == "a")
	{
	    num = 1;
	}
	else if (!sscanf(pre, "%d", num))
        {
	    if (pre == "a")
	    {
	        num = 1;
	    }
	    else
	    {
	        num = LANG_NUMW(pre);

		if (!num)
		{
		   notify_fail("Buy how many tickets?\n");
		   return 0;
		}
	    }
	}
	else if (num < 1)
	{
	    notify_fail("You have to buy more than one ticket!\n");
	    return 0;
	}
    }
    else
    {
        notify_fail("Buy what?\n");
	return 0;
    }

    if (strlen(from))
    {
	if (!parse_command(from,
            all_inventory(environment(this_object())), "[the] %i",
            oblist) ||
	    !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
	{
	    notify_fail("Buy tickets from whom?\n");
	    return 0;
	}

	if (sizeof(oblist) > 1)
	{
	    notify_fail("Please be more specific.  Buy tickets " +
                "from whom?\n");
	    return 0;
	}

	if (oblist[0] != this_object())
	{
	    notify_fail("Try buying tickets from the " + 
	        query_nonmet_name() + ".\n");
	    return 0;
	}
    }

    write(line + "\n");
    if (!strlen(line))
    {    
        notify_fail("Buy tickets for which line?\n");
	return 0;
    }

    sscanf(line, "the %s", line);
    sscanf(line, "%s line", line);
    sscanf(line, "%s shipline", line);
    write(line + "\n");

    line = lower_case(line);
    lines = SHIP_MGR->get_shiplines();
    for (i = 0; i < sizeof(lines); i++)
    {
	if (lower_case(lines[i]) == line)
	{
	    price = SHIP_MGR->get_price(lines[i]);
	    break;
	}
    }

    if (price == -1)
    {
	write("There is no \"" + capitalize(line) + "\" shipline.\n");
	return 1;
    }

    write(line + " " + price + "\n");
    return 1;
}

public void
init_living()
{
    ::init_living();
    add_action(buy_tickets, "buy");
}
