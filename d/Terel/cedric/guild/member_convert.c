#include "guild_defs.h"

public void start(string name)
{
    string file;
    string *joins;
    string *words;
    int year, month, day;
    int t;
    int i;
    string who;
    string *months = ({ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" });
    string *matches, match;

    setuid();
    seteuid(getuid());

    file = read_file("/d/Terel/cedric/guild/Log/members");
    joins = explode(file, "\n");

    matches = regexp(joins, "^:" + name + ":");

    if (!sizeof(matches))
    {
        write("No matches");
        return;
    }

    match = matches[sizeof(matches) - 1];

    words = explode(match, " ") - ({ "" });
    sscanf(words[6], "%d", year);
    t = (year - 1970) * (60 * 60 * 24 * 365) + (year - 1970) / 4 * (60 * 60 * 24);
    month = member_array(words[3], months);
    t += month * 60 * 60 * 24 * 30;

    sscanf(words[4], "%d", day);
    t += day * 60 * 60 * 24;
 
    sscanf(words[0], ":%s:", who);
    who = lower_case(who);

	if (!MEMBER_MANAGER->query_member(who))
	{
  	    MEMBER_MANAGER->add_member(who);
	}

	MEMBER_MANAGER->set_start_time(who, t);
}

