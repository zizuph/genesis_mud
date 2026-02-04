inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

string *names = ({ "Guincho", "Maureenanne", "Triss", "Adriel", "Blizzard",
                   "Nightingale", "Xashian", "Czucz", "Iliana", "Shiver" });
string *votes = ({});

public void
create_object()
{
    set_name("ballot");
    set_adj("voting");
    set_long("A voting ballot for the Minstrel Cycle.  You may vote for " +
	     "four members, any of\n\t" + implode(names, "\n\t") + "\n\n" +
             "Simply \"vote <name>\"\n");
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GET, 1);
}

public int
vote(string str)
{
    if (!strlen(str))
    {
        notify_fail("Vote for whom?\n");
	return 0;        
    }

    str = capitalize(str);

    sscanf(str, "for %s", str);

    if (member_array(str, names) == -1)
    {
        write("Please choose a valid member: " + implode(names, ", ") + "\n");
	return 1;
    }

    if (member_array(str, votes) >= 0)
    {
        write("You have already voted for " + str + ".\n");
	return 1;
    }

    setuid();
    seteuid(getuid());

    write_file("/d/Terel/cedric/guild/council_votes", this_player()->query_real_name() + " " + str + "\n");
    votes += ({ str });

    write("You have " + (sizeof(votes) == 4 ? "no" : 4 - sizeof(votes) + "") + " votes left.\n");

    if (sizeof(votes) == 4)
    {
        set_alarm(0.0, 0.0, &remove_object());
    }

    return 1;
}

public void
init()
{
    ::init();
    add_action(vote, "vote");
}

public string
query_auto_load()
{
    return MASTER + ":" + implode(votes, " ");
}

public void
init_arg(string args)
{
    votes = explode(args, " ");
}
