#include "guild_defs.h"

public void start()
{
    string file = read_file("/d/Terel/cedric/guild/Log/join.log");
    string *joins = explode(file, "\n\n");
    string *words;
    int year, month, day;
    int t;
    int i;
    string who;
    string *months = ({ "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" });

    setuid();
    seteuid(getuid());

    for (i = 0; i < sizeof(joins); i++)
    {
        words = explode(joins[i], " ") - ({ "" });
        sscanf(words[6], "%d", year);
        t = (year - 1970) * (60 * 60 * 24 * 365) + (year - 1970) / 4 * (60 * 60 * 24);
        month = member_array(words[3], months);
        t += month * 60 * 60 * 24 * 30;

        sscanf(words[4], "%d", day);
        t += day * 60 * 60 * 24;

        who = lower_case(words[0]);

	if (!MEMBER_MANAGER->query_member(who))
	{
  	    MEMBER_MANAGER->add_member(who);
	}

	MEMBER_MANAGER->set_start_time(who, t);
    }
}

public void
x()
{
    setuid();
	seteuid(getuid());
    start();
}
