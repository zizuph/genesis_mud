inherit "/std/object";

#include "/secure/std.h"
int MINTIME;

void wiz_check(string *list);
string convtime(int time);

create_object()
{
    set_name(({"checker", "wiz checker"}));
}

init()
{
    if (WIZ_TYPE(this_player()->query_wiz_level()) < WIZ_MAGE)
	return;

    add_action("check", "check");
    add_action("stop", "stop");
    set_long("A wizard last login checker.\n" + 
	     "Usage: 'check <wiztype> [>days]' to check the idle time for all wizards of a\n" +
	     "   certain type and optionally over a certain idle time in days.\n" +
	     "Usage: 'stop check' to abort a check.\n");
}

int
check(string what)
{
    string *wizzes, *args;

    args = explode(what, " ");

    if (sizeof(args) == 0)
    {
	write("Usage: check <wiztype> [>days]\n");
    }
    if (sizeof(args) > 1)
    {
	sscanf(args[1], "%d", MINTIME);
	what = args[0];
    }
    else
	MINTIME = 0;

    switch (what)
    {

    case "keeper":
	wizzes = SECURITY->query_wiz_list(WIZ_KEEPER);
	break;

    case "arch":
	wizzes = SECURITY->query_wiz_list(WIZ_ARCH);
	break;

    case "lord":
	wizzes = SECURITY->query_wiz_list(WIZ_LORD);
	break;

    case "mage":
	wizzes = SECURITY->query_wiz_list(WIZ_MAGE);
	break;

    case "wizard":
	wizzes = SECURITY->query_wiz_list(WIZ_NORMAL);
	break;

    case "retired":
    wizzes = SECURITY->query_wiz_list(WIZ_RETIRED);
   break;

    case "pilgrim":
	wizzes = SECURITY->query_wiz_list(WIZ_PILGRIM);
	break;

    case "apprentice":
	wizzes = SECURITY->query_wiz_list(WIZ_APPRENTICE);
	break;

    default: 
	write("No such wizard type.\n");
	return 1;
    }

    write("Checking...\n");
    wiz_check(wizzes);
    return 1;
}

int
stop(string what)
{
    if (what != "check")
	return 0;

    remove_call_out("wiz_check");
    write("Stopped.\n");
    return 1;
}

void
wiz_check(string *list)
{
    string rest;
    int log_time;
    object player;
    string pad;

    pad = "                                                  ";

    player = find_player(list[0]);
    
    if (!objectp(player))
	player = SECURITY->finger_player(list[0]);

    if (!objectp(player))
	write(capitalize(list[0]) + ": " + extract(pad, 0, 12 - strlen(list[0])) + "ANOMALY, Does not have a player file.\n");
    else
    {
	if ((time() - player->query_login_time()) > (MINTIME * 86400))
	{
	    log_time = time() - player->query_login_time();

	    write(capitalize(list[0]) + ": " + extract(pad, 0, 12 - strlen(list[0])) + convtime(log_time) + "\n");
	}
    }

    if (sizeof(list) == 1)
	write("Done.\n");
    else
    {
	list -= ({ list[0] });
	if (sizeof(list) % 10 == 0)
	    call_out("wiz_check", 1, list);
	else 
	    wiz_check(list);
    }
}

string
convtime(int time)
{
    string res;
    int n;
    
    res = "";

    n = time / 86400;
    if (n > 0)
    {
	if (n == 1)
	    res = n + " days";
	else
	    res = n + " day";
	time -= n * 86400;
    }

    n = time / 3600;
    if (n > 0)
    {
	if (strlen(res) != 0)
	    res += " ";

	if (n == 1)
	    res += n + " hour";
	else 
	    res += n + " hours";
	time -= n * 3600;
    }

    n = time / 60;
    if (n > 0)
    {
	if (strlen(res) != 0)
	    res += " ";

	if (n == 1)
	    res += n + " minute";
	else
	    res += n + " minutes";
	time -= n * 60;
    }

    if (time)
    {
	if (strlen(res) != 0)
	    res += " ";

	if (time == 1)
	    res += time + " second";
	else
	    res += time + " seconds";
    }

    return res;
}

void 
leave_env(object old, object dest) 
{
    tell_object(old, "Autodestructing checker.\n");
destruct();
}
