#include "guild_defs.h"

public varargs void
tweak(string who, int amt = 0)
{
    string file, *joins, *matches, match, trash;
    int t, day1, hour1, minute1, second1, day2, hour2, minute2, second2, secs1, secs2;
    string *words;

    setuid();
    seteuid(getuid());

    file = read_file("/d/Terel/cedric/guild/Log/join.log");
    joins = explode(file, "\n");

    matches = regexp(joins, "^" + capitalize(who) + " ");

    if (!sizeof(matches))
    {
        file = read_file("/d/Terel/cedric/guild/Log/members");
        joins = explode(file, "\n");

        matches = regexp(joins, "^:" + capitalize(who) + ":");

	if (!sizeof(matches))
	{
  	    write("No matches\n");
	    return;
	}
    }

    match = matches[sizeof(matches) - 1];

    words = explode(match, " ") - ({ "" });
    sscanf(words[4], "%d", day1);
    sscanf(words[5], "%d:%d:%d", hour1, minute1, second1);

    dump_array(({ day1, hour1, minute1, second1 }));

    secs1 = (24 * 60 * 60) - (hour1 * 60 * 60 + minute1 * 60 + second1);
    write(secs1 + "\n");

    write(match + "\n");

    t = MEMBER_MANAGER->query_start_time(who);

    secs2 = (t % (24 * 60 * 60));
    write(secs2 + "\n");
    write((secs1 - secs2) + "\n");

    if (amt)
    {
        t += amt;
	MEMBER_MANAGER->set_start_time(who, t);
        write(ctime(t) + "\n");
    }
}
