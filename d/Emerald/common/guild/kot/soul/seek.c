#include <language.h>
#include <std.h>

mixed
get_title(object who)
{
    if (!who->query_kot_member())
    {
        return 0;
    }

    if (who->query_wiz_level())
    {
        return 0;
    }

    if (wildmatch("*jr", who->query_real_name()))
    {
        return 0;
    }

    return who->query_name() + " the " + who->query_guild_title_race();
}

int
seek(string str)
{
    string *titles;
  
    if (this_player()->query_attack())
    {
	notify_fail("You cannot concentrate on this while in "+
		    "combat!\n");
	return 0;
    }

    write("You bow your head in concentration, muttering the ancient\n"+
	  "elven words to summon powers granted you by Telan-Ri.\n\n");

    titles = map(users() - ({ this_player() }), get_title) - ({ 0 });

    write("You sense " + (sizeof(titles) ? LANG_WNUM(sizeof(titles)) : "no") +
        " other " + ((sizeof(titles) == 1) ? "Keeper" : "Keepers") + 
        ".\n");

    map(titles, write @ &sprintf("- %-=70s\n", ));

    write("\n");

    return 1;
}

