#include "../guild.h"

int
promotions(string str)
{
    int stat;

    setuid();
    seteuid(getuid());

    if (str == "refuse")
    {
        stat = this_player()->query_kot_level();

        MANAGER->set_level_frozen(this_player(), stat);

	write("You have decided not to seek further advancement among the "+
	      "Keepers. You will continue to accumulate experience within "+
	      "the guild, though your rank will not change until you "+
	      "decide to seek advancement again.\n");
	return 1;
    }

    if (str == "accept")
    {
	if (MANAGER->query_level_frozen(this_player()) == -1)
	{
	    write("You are already seeking advancement within the Keepers.\n");
	    return 1;
	}
    
	write("You decide to seek further advancement within the Keepers " +
            "once more.\n");
    
	MANAGER->set_level_frozen(this_player(), -1);
    
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " accept / refuse.\n");
    return 0;
}

