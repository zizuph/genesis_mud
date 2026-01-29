/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */

inherit "/std/object";
#include "/secure/std.h"
#include "/sys/filter_funs.h"

#define BS(str) break_string(str, 75)

public void test_mortals();
public int suitable_mortals(object ob);
public int spectators(object ob);

string *got_it;		/* These mortals have already got it */

public void
create_object()
{
    set_name("wizard promotion tester");
    got_it = ({});
    enable_reset();
}

public int
teleledningsanka()
{
    test_mortals();
    return 1;
}

public void
reset_object()
{
    remove_call_out("test_mortals");
    test_mortals();
}

public void
test_mortals()
{
    object *ok, *others, scroll;
    int i;

    call_out("test_mortals", 3600);

    setuid();
    seteuid(getuid());

    /*
     * Find ripe mortals.
     */
    ok = filter(users(), "suitable_mortals", this_object());

    for (i = 0 ; i < sizeof(ok) ; i++)
    {
	/* 
	 * The prospective wiz must alone in order to
	 * be presented with the scroll.
	 */
	others = filter(all_inventory(environment(ok[i])), "spectators", this_object());
	if (sizeof(others) > 1)
	{
	    tell_object(ok[i], BS("\nAll of a sudden, without any warning, you are filled with a sudden yearning to seek peace and meditate. Alone.\n\n"));
	    continue;
	}
	
	/*
	 * Remember that he has got it once today.
	 */
	log_file("wizquest_offer", sprintf("%-15s", capitalize(ok[i]->query_real_name())) + ctime(time()) + "\n");
	got_it += ({ ok[i]->query_real_name() });

/*
	tell_object(ok[i], BS("\n\n\n\n\n\n\n\nA dark shape materializes before you. With a sinking feeling you realize that it's DEATH who has decided to visit.\n\n") + BS("Death says: MORTAL, THE TIME HAS COME WHEN I MAY HAVE TO RELINQUISH MY POWER OVER YOU. I DON'T LIKE IT MUCH, BUT SUCH ARE THE RULES. I GUESS YOU HAD BETTER READ THIS.\n\n") + BS("Death takes something from within his dark cloak and hands it over to you. As you numbwittedly accept Death's gift, he turns and with a final look of contempt, dematerializes.\n"));
*/
	tell_object(ok[i], BS("\n\n\n\n\n\n\n\nA dark shape materializes before you. With a sinking feeling you realize that it's DEATH who has decided to visit.\n\n") + BS("Death says: MORTAL, THE TIME HAS COME FOR YOU TO RECONSIDER YOUR POSITION IN THE WORLD. IT MIGHT BE THAT I HAVE TO RELINQUISH MY POWER OVER YOU. I DON'T LIKE IT MUCH, BUT SUCH ARE THE RULES. I GUESS YOU HAD BETTER READ THIS.\n\n") + BS("Death takes something from within his dark cloak and hands it over to you. As you numbwittedly accept Death's gift, he turns and with a final look of contempt, dematerializes.\n"));
	scroll = clone_object("/d/Genesis/obj/wizquest/scroll.c");
	scroll->move(ok[i], 0);
    }
}

/*
 * return status.
 * Just if someone wants to know...
 */
public mixed
query_status()
{
    int retval;

    if (WIZ_TYPE(SECURITY->query_wiz_level(geteuid(previous_object()))) < WIZ_ARCH)
	return 0;

    if (remove_call_out("test_mortals") < 0)
	retval = 0;
    else
	retval = 1;
    test_mortals();
    return ({ retval, got_it });
}

/*
 * Filter to find ripe mortals.
 */
public int
suitable_mortals(object ob)
{
    int i;
    string name;

    if (strlen(name = ob->query_real_name()) > 2 && 
	    extract(name, strlen(name) - 2, strlen(name)) == "jr")
	return 0;

    if (SECURITY->query_wiz_level(ob->query_real_name()) != WIZLEV_MORTAL ||
	ob->query_average_stat() < 100)
	return 0;
    
    for (i = 0 ; i < sizeof(got_it) ; i++)
	if (got_it[i] == ob->query_real_name())
	    return 0;
    
    return 1;
}

/*
 * Filter to find other players in the room.
 */
public int
spectators(object ob)
{
    if (!living(ob) ||
	!query_ip_number(ob))
	return 0;
    
    return 1;
}
