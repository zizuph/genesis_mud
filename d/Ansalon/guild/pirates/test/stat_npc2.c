/*
   statistic monster base file by Milan
 */

inherit "/w/milan/std_oponent";

#include <macros.h>

int *aid = ({});
int max_aid = -1000, min_aid = 1000, count = 0;
int sum_sqr = 0, sum_aid = 0, avg_aid, max_count = 100;
object oponent;
string log_str = "Standard oponents results:\n";
object gShadow;

void
set_max_count(int i)
{
    max_count = i;
}

set_log_str(string str)
{
    log_str = str;
}

void
kill_command()
{
    command("kill "+OB_NAME(oponent));
}

nomask void
make_report()
{
    setuid();
    seteuid(getuid());
    log_file("combat_aid", log_str+"aid="+avg_aid+"% ("+count+" fights), (min "+min_aid+"%, max "+max_aid+"%, mean square err "+sum_sqr/count+")\n");
}

nomask private void
restart_fight(int flag = 0)
{
    int i;

    stop_fight(oponent);
    oponent->stop_fight(this_object());

    if (flag)
    {
	sum_aid += aid[count];
	max_aid = (aid[count] > max_aid ? aid[count] : max_aid);
	min_aid = (aid[count] < min_aid ? aid[count] : min_aid);
	count++;
	avg_aid = sum_aid / count;
	sum_sqr = 0;
	for (i=0; i<count; i++)
	    sum_sqr += (aid[i] - avg_aid) * (aid[i] - avg_aid);
	command("say Fight ended with "+aid[count-1]+"% aid");
	command("say average "+avg_aid+"% aid ("+count+" fights), "+
	"(min "+min_aid+"%, max "+max_aid+"%, mean square err "+sum_sqr/count+")");

	if (count >= max_count)
	{
	    make_report();
	    command("say Finished "+count+" fights, report written.");
	    return;
	}
    }

    oponent->refresh_living();
    oponent->add_panic(-oponent->query_panic());
    refresh_living();
    add_panic(-query_panic());

    command("say Starting new fight.");
    set_alarm(2.0, 0.0, kill_command);
}

public void
do_die(object killer)
{
    /* Did I die ? */
    if (query_hp() > 0)
        return;
    aid += ({ 100 - ((100 * query_max_hp()) / (query_max_hp() - killer->query_hp())) });
    restart_fight(1);
}

public void
notify_you_killed_me(object dead)
{
    aid += ({ ((100 * query_max_hp()) / (query_max_hp() - query_hp())) - 100 });
    restart_fight(1);
}

void
start_fight()
{
    setuid();
    seteuid(getuid());
    if (!objectp(oponent))
	oponent = clone_object("/w/milan/std_oponent");
    oponent->move(environment(), 1);
    restart_fight(0);
}

void
create_monster()
{
    ::create_monster();
    set_name("monster");
    set_adj("statistic");

    this_object()->set_intoxicated(1000);
}
